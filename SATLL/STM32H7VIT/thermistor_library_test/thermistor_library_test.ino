#include "thermistors.h"

#define MTR_THERM PA0
#define OBC_THERM PA3
#define PWR_THERM PA6
#define BCK_THERM PB0
#define BP_THERM PB1
#define SP_THERM PC4
#define COMMS_THERM PC3_C
#define AOCS_THERM PC1

void setup() {
  Serial.begin(115200);
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
  delay(2000);

  // pinMode(MTR_THERM, INPUT);
  pinMode(OBC_THERM, INPUT);
  // pinMode(PWR_THERM, INPUT);
  // pinMode(BCK_THERM, INPUT);
  // pinMode(BP_THERM, INPUT);
  // pinMode(SP_THERM, INPUT);
  // pinMode(COMMS_THERM, INPUT);
  // pinMode(AOCS_THERM, INPUT);



  analogReadResolution(16);
 // obcWarmup(OBC_THERM);
  // want to warmup and callibrate each sensor
  // so we will do Thermistor.begin(all);, have it so you cn put in the ones you want
  //Thermistor.warmup();

}

void loop() {
  // put your main code here, to run repeatedly:

}
