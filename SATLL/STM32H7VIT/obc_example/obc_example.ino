

//OBC start
//i2c sensors
//calibrate thermistors



// Libraries
#include <SPI.h>
#define PL_en PE2

#include <Adafruit_NeoPixel.h>

#include <Adafruit_INA260.h>
Adafruit_INA260 ina260 = Adafruit_INA260();

#include "tcn75.h"
#define tcn75address 0x4F // with pins 5~7 set to GND, the device address is 0x48
tcn75 termometro(tcn75address);

#include <ArduCAM.h>
//SDA SCL
TwoWire Wire2(PB7,PB6);

#include <ACANFD_STM32.h>
#define CAN1_TX_PIN PD_1
#define CAN1_RX_PIN PD_0
static const uint32_t FDCAN1_MESSAGE_RAM_WORD_SIZE = 2560 ;
static const uint32_t FDCAN2_MESSAGE_RAM_WORD_SIZE = 0 ; // FDCAN2 not used
static ACANFD_STM32_FIFO gBuffer ;



//start spi/ create a void to enable spi
//KISPE library
//Thermistor.callibrate(OBC); //etc...
//Wire.begin for the OBc i2c and Payload i2c
// CAN/UART
//Serial.begin for the AOCS uart

//OBC Variables
#define OBC_THERM   PA3
//NeoPixel
#define PIN         PB12 
#define NUMPIXELS   1 
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

float T0;

struct obc {
  uint32_t count;
  float R0 = 10625.56;
  float R;
  float T0 = 298.15;
  float T;
  float TCN75_Temp;
  float bus_Voltage;
  float bus_Current;
  float bus_Power;
} obc;

struct aocs {

} aocs;

struct power {

} power;

struct comms{

} comms;

//Universal Variables
long int currentMillis;
long int previousMillis;
int sampleInterval = 1000; // Sample interval in ms 

long int currentMillis_temp;
long int previousMillis_temp;
int sampleInterval_temp = 200; // Sample interval in ms 


void setup() {
  Wire.begin();
  Wire2.begin();
  gBuffer.initWithSize(100);
  Serial.begin(9600);
  delay(2000);
  Serial.println();

  ACANFD_STM32_Settings settings (1000 * 1000, DataBitRateFactor::x4) ;
  settings.mModuleMode = ACANFD_STM32_Settings::NORMAL_FD; // Found in CANFDMessage.h lines 53 - 58


  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)

  pixels.clear();
  pixels.setPixelColor(0, pixels.Color(0, 0, 0)); // R G B
  pixels.show();

  Serial.println("Sensor Check");
  SensorCheck();

  Serial.println("Calibrating thermistors \t");
  analogReadResolution(16);
  
  // Want to get a T0 for OBC
  calibrateThermistor();
  

} // END of setup()

void loop() {

  // Will also include modes of operation



  currentMillis = millis();
  currentMillis_temp = currentMillis;
  

  // Takes a temperature reading every 200 ms
  if ( (currentMillis_temp - previousMillis_temp) > sampleInterval_temp ){
    temperature();
    previousMillis_temp = currentMillis_temp;

    //current temp is 200ms - may have all sensors in this
    OBC_Power();
    obc.TCN75_Temp = termometro.readTemperature();

  }
  

  // Display data every second - the real data is measured and saved faster, but only displays the data once a second
  //and dipalsy the latest value of the data at that time
  if ( (currentMillis - previousMillis) > sampleInterval ){
    Serial.print(obc.count);Serial.print(",");
    Serial.print(obc.T);Serial.print(",");
    Serial.print(obc.TCN75_Temp);Serial.print(",");
    Serial.print(obc.bus_Voltage);Serial.print(",");
    Serial.print(obc.bus_Current);Serial.print(",");
    Serial.print(obc.bus_Power);
    Serial.println();
    obc.count++;
    previousMillis = currentMillis;
  }


} // END of Loop()


void SensorCheck(){
  
  if (!ina260.begin()) {
    Serial.println("Couldn't find INA260 chip");
    pixels.clear();
    pixels.setPixelColor(0, pixels.Color(150, 0, 0)); // R G B
    pixels.show();
    while (1);
  }
  Serial.println("Found INA260 chip");
  pixels.clear();
  pixels.setPixelColor(0, pixels.Color(0, 150, 0)); // R G B
  pixels.show();
  delay(100);

  pixels.clear();
  pixels.setPixelColor(0, pixels.Color(0, 0, 0)); // R G B
  pixels.show();

  Serial.println();
  Serial.print("Current config = ");
  Serial.println(termometro.readConfig(), BIN);
  Serial.print("Current histeresys = ");
  Serial.println(termometro.readHisteresys());
  Serial.print("Current setpoint = ");
  Serial.println(termometro.readSetPoint());
  pixels.clear();
  pixels.setPixelColor(0, pixels.Color(0, 150, 0)); // R G B
  pixels.show();
  delay(100);

  pixels.clear();
  pixels.setPixelColor(0, pixels.Color(0, 0, 0)); // R G B
  pixels.show();



}





void calibrateThermistor(){

  //obc.T0 = 298.15;
  uint32_t R0_sum;
  uint32_t T0_sum;

  float T; // Temperature in Kelvin
  float BETA = 3430.0;

  for (int j = 0; j < 10; j++){
    Serial.print(".");
    int adc = analogRead(OBC_THERM);
    obc.R = 10000 * ((65536/float(adc)) - 1);
    obc.T = (BETA * obc.T0) / (BETA + (obc.T0 * log(obc.R0 / obc.R)) ); // Is R0/R as the thermistor R voltage divider is in reverse

  delay(10);
  }
  Serial.println(" Done");
  T0 = obc.T;

} // END of calibrateThermistor()

void temperature(){
  float BETA = 3430.0;
  float tKelvin;

  //Read all of the Thermistor values
  int OBC = analogRead(OBC_THERM);    // read the ADC value
  obc.R = 10000 * ((65536/float(OBC)) - 1);
  
  tKelvin = (BETA * obc.T0) / (BETA + (obc.T0 * log(obc.R0/ obc.R )));
  obc.T = tKelvin - 273.15;

  // /2 reactive to 0.5 oC, /10 reactive to 0.5 oC
  //float rounded_tCelcius = (round(obc.T * 10)) ;/// 10;
  float rounded_tCelcius = (round(obc.T * 2)) /2 ;/// 10;
  //float rounded_T0 = (round((T0 - 273.15) * 10));// / 10;
  float rounded_T0 = (round((T0 - 273.15) * 2)) / 2;// / 10;
  short int deltaT = rounded_tCelcius - rounded_T0;

  if (deltaT > 0){
    //RED 
    pixels.clear();
    pixels.setPixelColor(0, pixels.Color(150, 0, 0)); // R G B
    pixels.show();

  } else if(deltaT < 0) {
    //BLUE 
    pixels.clear();
    pixels.setPixelColor(0, pixels.Color(0, 0, 150)); // R G B
    pixels.show();

  } else {
    //GREEN
    pixels.clear();
    pixels.setPixelColor(0, pixels.Color(0, 150, 0)); // R G B
    pixels.show();    

  }

} // END of temperature()

void OBC_Power(){
  obc.bus_Voltage = ina260.readBusVoltage();  // mV
  obc.bus_Current = ina260.readCurrent();     // mA
  obc.bus_Power = ina260.readPower();         //mW

}
