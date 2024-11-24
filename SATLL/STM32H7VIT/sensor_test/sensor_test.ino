/*
  _  _______  _____ _____  ______ 
 | |/ /_   _|/ ____|  __ \|  ____|
 | ' /  | | | (___ | |__) | |__   
 |  <   | |  \___ \|  ___/|  __|  
 | . \ _| |_ ____) | |    | |____ 
 |_|\_\_____|_____/|_|    |______|                                 
   _____ _____        _____ ______ 
  / ____|  __ \ /\   / ____|  ____|
 | (___ | |__) /  \ | |    | |__   
  \___ \|  ___/ /\ \| |    |  __|  
  ____) | |  / ____ \ |____| |____ 
 |_____/|_| /_/    \_\_____|______|                         

  Development and test code for the SATLL STM32H753ZIT uC

*/

// INA260 Power Measurement Chip
#include <Adafruit_INA260.h>
Adafruit_INA260 ina260 = Adafruit_INA260();

// TCN75 Temperature Sensor
#include "tcn75.h"
#define tcn75address 0x4F // with pins 5~7 set to GND, the device address is 0x48
tcn75 termometro(tcn75address);

//NeoPixel
#include <Adafruit_NeoPixel.h>
#define PIN        PB12 
#define NUMPIXELS 1 // How many NeoPixels are attached?
Adafruit_NeoPixel LED(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);


#define MTR_THERM PA0
#define OBC_THERM PA3
#define PWR_THERM PA6
#define BCK_THERM PB0
#define BP_THERM PB1
#define SP_THERM PC4
#define COMMS_THERM PC3_C
#define AOCS_THERM PC1


struct KISPEdata {
  int recordNumber;
  float current;
  float voltage;
  float power;
  float temperature;
  float MTR_T;
  float OBC_T;
  float PWR_T;
  float BCK_T;
  float BP_T;
  float SP_T;
  float COMMS_T;
  float AOCS_T;

} data;

uint32_t Time1;
uint32_t Time2;
float OBC_R0;
float T0_sum;
  

int warmup_flag; // flag used to print out warmup data or not

void setup() {
  Serial.begin(9600);
  Serial.flush();
  Wire.begin();
  delay(2000);
  Serial.println("------------------------------------------------"); 
  Serial.println();
  Serial.println("  _  _______  _____ _____  ______ ");
  Serial.println(" | |/ /_   _|/ ____|  __ \\|  ____|");
  Serial.println(" | ' /  | | | (___ | |__) | |__   ");
  Serial.println(" |  <   | |  \\___ \\|  ___/|  __|  ");
  Serial.println(" | . \\ _| |_ ____) | |    | |____ ");
  Serial.println(" |_|\\_\\_____|_____/|_|    |______|");
  Serial.println();
  Serial.println("------------------------------------------------");
  Serial.println();
  Serial.println("SATLL OBC test script");
  Serial.println();
  delay(4000); 

  pinMode(PIN, OUTPUT);
  //Flash neo pixel
  LED.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  //LED.clear();            // Turn OFF all pixels ASAP
  LED.setBrightness(10); // Set BRIGHTNESS to about 1/5 (max = 255) 
    LED.setPixelColor(1, LED.Color(0, 0, 0));// sets LED to Green
  //LED.show();   // Send the updated pixel colors to the hardware.
  delay(1000);

  LED.setPixelColor(1, LED.Color(0, 0, 150));// sets LED to Blue
 // LED.show();   // Send the updated pixel colors to the hardware.
  delay(1000);
  LED.setPixelColor(1, LED.Color(0, 0, 0));// sets LED to Green
  //LED.show();   // Send the updated pixel colors to the hardware.
  delay(1000);
  //LED.clear();            // Turn OFF all pixels ASAP
  //delay(500);

  startup();
  delay(4000);
  warmup();
      LED.setPixelColor(1, LED.Color(0, 0, 0));// sets LED to Green
    LED.show();   // Send the updated pixel colors to the hardware.
    delay(100);
  LED.setPixelColor(1, LED.Color(0, 0, 150));// sets LED to Blue
  LED.show();   // Send the updated pixel colors to the hardware.
  delay(100);
  LED.clear();            // Turn OFF all pixels ASAP
  delay(100);


} // END of startup()

void loop() {

  // every second print the data - but dont stop from measuring - think of the themristor


  
} // END of loop()


void startup(){

  pinMode(MTR_THERM, INPUT);
  pinMode(OBC_THERM, INPUT);
  pinMode(PWR_THERM, INPUT);
  pinMode(BCK_THERM, INPUT);
  pinMode(BP_THERM, INPUT);
  pinMode(SP_THERM, INPUT);
  pinMode(COMMS_THERM, INPUT);
  pinMode(AOCS_THERM, INPUT);
  analogReadResolution(16);


  Serial.println("--------------------------------------------");
  Serial.println("Sensor Checklist");
// INA260
  Serial.print("- Power chip");

  if (!ina260.begin()) {
    Serial.println("- ERROR");
    LED.setPixelColor(1, LED.Color(150, 0, 0));// sets LED to RED
    LED.show();   // Send the updated pixel colors to the hardware.
    delay(100);
    LED.clear();            // Turn OFF all pixels ASAP
    delay(100);
  } else {
  Serial.println("- Success");
  LED.setPixelColor(1, LED.Color(0, 0, 0));// sets LED to Green
  LED.show();   // Send the updated pixel colors to the hardware.
  delay(100);
  LED.setPixelColor(1, LED.Color(0, 150, 0));// sets LED to Green
  LED.show();   // Send the updated pixel colors to the hardware.
  delay(100);
  LED.clear();            // Turn OFF all pixels ASAP
  delay(100);
  }


// TCN75
  Serial.print("- Temperature Sensor");
  
  // Checking if the TCN75 replies 
  Wire.beginTransmission(tcn75address);
  int error = Wire.endTransmission();
  termometro.readConfig();
  termometro.readHisteresys();
  termometro.readSetPoint();
  if (error == 0) {
    Serial.println("- Success");
    LED.setPixelColor(1, LED.Color(0, 0, 0));// sets LED to Green
    LED.show();   // Send the updated pixel colors to the hardware.
    delay(100);
    LED.setPixelColor(1, LED.Color(0, 150, 0));// sets LED to Green
    LED.show();   // Send the updated pixel colors to the hardware.
    delay(100);
    LED.clear();            // Turn OFF all pixels ASAP
    delay(100);
  } else {
    Serial.println("- ERROR");
    LED.setPixelColor(1, LED.Color(150, 0, 0));// sets LED to Green
    LED.show();   // Send the updated pixel colors to the hardware.
    delay(100);
    LED.clear();            // Turn OFF all pixels ASAP
    delay(100);
  }
  Serial.print("- CAN");
  Serial.println(" - NOT CONFIGURED"); 
  Serial.println("--------------------------------------------");
} // END of startup()


void warmup(){
  LED.setPixelColor(1, LED.Color(0, 0, 150));// sets LED to Green
  LED.show();   // Send the updated pixel colors to the hardware.
  Serial.println("Warming Sensors");
  // Uncomment to see the data output
  warmup_flag = 1;


  // // taking 50 readings with the tcn75 to stabilise the readings
  for (int j = 0; j < 50; j++){
    termometro.readTemperature();
    switch (warmup_flag){
      case 1:
        Serial.print(j);Serial.print("\t"); 
        Serial.print(termometro.readTemperature());Serial.println(" C");
        break;
    }
  }
  // taking 50 thermistor OBC readings to warm up, then taking 100 to get an estimate for the room temp
    for (int j = 0; j < 50; j++){
    // adc input used for thermistor readings
    int  adc = analogRead(OBC_THERM); 
    switch (warmup_flag){
      case 1:
        Serial.print(j);Serial.print("\t"); 
        Serial.print("ADC:");Serial.println(adc);
        break;
    }
  }
  int T0 = 298.15;
  float R; // the measure Resistance of the resistor
  float R0; // Resistance of the thermistor at room temperature
  uint32_t R0_sum;
  
  float T; // Temperature in Kelvin
  float BETA = 3430.0;
  for (int j = 0; j < 100; j++){
    int adc = analogRead(OBC_THERM);
    R = 10000 * ((65536/float(adc)) - 1);
    R0_sum = R0_sum + (R*100); // This make R an integer and removes an rounding errors
    R0 = R;
    T = (BETA * T0) / (BETA + (T0 * log(R0 / R))); // Is R0/R as the thermistor R voltage divider is in reverse
    T0 = T;
    T = T - 273.5;
    T0_sum = T0_sum + (T * 100);
    switch (warmup_flag){
      case 1:
        Serial.print(j);Serial.print("\t"); 
        Serial.print(T);Serial.println(" C");
        break;
    }

  }
  R0_sum = R0_sum / 100; // Averages the resistance at room temp
  OBC_R0 = R0_sum / 100; // This is as we multiplied by 100 at first
  T0_sum = T0_sum / (100*100);
  

  //print average
    switch (warmup_flag){
      case 1:
        Serial.print("Average R0");Serial.print("\t"); 
        Serial.print(OBC_R0);Serial.println(" Ohm");
        Serial.print("Average T0");Serial.print("\t");
        Serial.print(T0_sum);Serial.println(" C");
        break;
    }
  Serial.println("--------------------------------------------");
  LED.clear();            // Turn OFF all pixels ASAP
  delay(100);
} //END of warmup
