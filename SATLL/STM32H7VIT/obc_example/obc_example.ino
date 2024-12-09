

//OBC start
//i2c sensors
//calibrate thermistors



// Libraries
#include <Adafruit_NeoPixel.h>
long int currentMillis;
long int previousMillis;
int sampleInterval = 1000; // Sample interval in ms 

long int currentMillis_temp;
long int previousMillis_temp;
int sampleInterval_temp = 200; // Sample interval in ms 



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
  float Thermistor_Temp;
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




void setup() {
  Serial.begin(9600);
  delay(2000);


  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)

  pixels.clear();
  pixels.setPixelColor(0, pixels.Color(0, 0, 0)); // R G B
  pixels.show();

  Serial.println();
  Serial.println("Calibrating thermistors \t");
  analogReadResolution(16);
  
  // Want to get a T0 for OBC
  calibrateThermistor();
  


} // END of setup()

void loop() {
  currentMillis = millis();
  currentMillis_temp = currentMillis;
  

  // Takes a temperature reading every 200 ms
  if ( (currentMillis_temp - previousMillis_temp) > sampleInterval_temp ){
    temperature();
  }
  

  // Display data every second - the real data is measured and saved faster, but only displays the data once a second
  //and dipalsy the latest value of the data at that time
  if ( (currentMillis - previousMillis) > sampleInterval ){
  Serial.print(obc.T0);Serial.print("\t");Serial.println(obc.T);

  }


} // END of Loop()

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
  Serial.println(obc.T);
  
  // /2 reactive to 0.5 oC, /10 reactive to 0.5 oC
  //float rounded_tCelcius = (round(obc.T * 10)) ;/// 10;
  float rounded_tCelcius = (round(obc.T * 2)) /2 ;/// 10;
  //float rounded_T0 = (round((T0 - 273.15) * 10));// / 10;
  float rounded_T0 = (round((T0 - 273.15) * 2)) / 2;// / 10;


  Serial.println();
  Serial.println(rounded_tCelcius);
  Serial.println(rounded_T0);
  Serial.println();
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
