#include "thermistors.h"

struct therm {
  float OBC_R0;
  float OBC_T0;
};

struct therm obcWarmup((uint32_t) OBC_THERM){
  struct therm obc;
  int T0 = 298.15;
  float R; // the measure Resistance of the resistor
  float R0; // Resistance of the thermistor at room temperature
  uint32_t R0_sum;
  uint32_t T0_sum;

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
    // switch (warmup_flag){
    //   case 1:
    //     Serial.print(j);Serial.print("\t"); 
    //     Serial.print(T);Serial.println(" C");
    //     break;
    // }

  }

  R0_sum = R0_sum / 100; // Averages the resistance at room temp
  R0_sum = R0_sum / 100; // This is as we multiplied by 100 at first
  T0_sum = T0_sum / (100*100);
  //T0 = T0_sum;
  
  //Can only return one thing at a time

  // return OBC_R0;
  // return T0; // these values will be used for future readings
  
  obc.OBC_R0 = R0_sum;
  obc.OBC_T0 = T0_sum;
  return obc;
}



// float obcWarmup(int OBC_THERM){
//   int T0 = 298.15;
//   float R; // the measure Resistance of the resistor
//   float R0; // Resistance of the thermistor at room temperature
//   uint32_t R0_sum;

//   float T; // Temperature in Kelvin
//   float BETA = 3430.0;

//   for (int j = 0; j < 100; j++){
//     int adc = analogRead(OBC_THERM);
//     R = 10000 * ((65536/float(adc)) - 1);
//     R0_sum = R0_sum + (R*100); // This make R an integer and removes an rounding errors
//     R0 = R;
//     T = (BETA * T0) / (BETA + (T0 * log(R0 / R))); // Is R0/R as the thermistor R voltage divider is in reverse
//     T0 = T;
//     T = T - 273.5;
//     T0_sum = T0_sum + (T * 100);
//     switch (warmup_flag){
//       case 1:
//         Serial.print(j);Serial.print("\t"); 
//         Serial.print(T);Serial.println(" C");
//         break;
//     }

//   }

//   R0_sum = R0_sum / 100; // Averages the resistance at room temp
//   OBC_R0 = R0_sum / 100; // This is as we multiplied by 100 at first
//   T0_sum = T0_sum / (100*100);
//   T0 = T0_sum;
  
//   //Can only return one thing at a time

//   return OBC_R0;
//   return T0; // these values will be used for future readings
// }// END of Warmup







  


