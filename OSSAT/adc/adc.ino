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

  Development and test code for the STM32H753ZIT uC


  STM32H7 line has a 16-bit ADC
  The STM32 has 3.3v logic level so the max input to the ADC is 3.3v
  This mean that it will map voltages between 0v and 3.3v 
  with readings showing between 0 and 65,535 or 2^16

  Pinname  - STM32 Pin - ADC
  A0 - PA3      -    ADC1/2
  A1 - PC0      -    ADC1/2/3
  A2 - PC_3      -    ADC1/2
  A3 - PB1      -    ADC1/2
  A4 - PC_2/PB9  -    ADC1/2/3
  A5 - PF10/PB8 -    ADC3
  A6 - PF4      -    ADC3
  A7 - PF5      -    ADC3
  A8 - PF6      -    ADC3

  Last updated 13/08/2024 Harvey Nixon
*/

void setup() {
  Serial.begin(9600);
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

  // For the STM32H7, A6 is the ADC pin and refrerred to as PF4 on the pinout of the STM
  // INPUT means the STM wil measure the volatge of the pin coming in

  pinMode(PF11, INPUT); // AV0
  pinMode(PA6, INPUT); // AV1 
  pinMode(PB1, INPUT); // AV2 
  pinMode(PC5, INPUT); // AV3
  pinMode(PC_2, INPUT); // AV4
  pinMode(PC_3, INPUT); // AV5
  pinMode(PC0, INPUT); // AV6
  pinMode(PC1, INPUT); // AV7

  // Using the analogueRead() function the defult resolution is 10-bits meaning a resolution of 1024 steps
  // The STM32 ADC has a resolution of 16-bits meaning 65,536 steps.

  // Documentation on analogueRead() here:
  // https://www.arduino.cc/reference/en/language/functions/analog-io/analogread/
  analogReadResolution(16);

}

void loop() {
  
  // The value will be an integer between 0 and 65,356 for the 16 bits
  int AV0 = analogRead(PF11);   // read the ADC value 
  int AV1 = analogRead(PA6);    // read the ADC value
  int AV2 = analogRead(PB1);    // read the ADC value
  int AV3 = analogRead(PC5);    // read the ADC value
  int AV4 = analogRead(PC_2);    // read the ADC value
  int AV5 = analogRead(PC_3);    // read the ADC value
  int AV6 = analogRead(PC0);    // read the ADC value
  int AV7 = analogRead(PC1);    // read the ADC value

  Serial.println("----------------------------------------");
// --------------------------------------------------------------------------------------------//
  Serial.print("AV0 | ");
  Serial.print(AV0);Serial.print(" | ");
  // Printing the value for checking 
  float voltageAV0 = (float(AV0)/65536) * 3.3; //formulae to convert the ADC value to voltage
  //MEASURED VOLTAGE = (ADC Value / ADC Resolution) * Reference Voltage
  Serial.print(voltageAV0);Serial.print(" V |");Serial.println();
// --------------------------------------------------------------------------------------------//
  Serial.print("AV1 | ");
  Serial.print(AV1);Serial.print(" | ");
  // Printing the value for checking 
  float voltageAV1 = (float(AV1)/65536) * 3.3; //formulae to convert the ADC value to voltage
  //MEASURED VOLTAGE = (ADC Value / ADC Resolution) * Reference Voltage
  Serial.print(voltageAV1);Serial.print(" V |");Serial.println();
// --------------------------------------------------------------------------------------------//
  Serial.print("AV2 | ");
  Serial.print(AV2);Serial.print(" | ");
  // Printing the value for checking 
  float voltageAV2 = (float(AV2)/65536) * 3.3; //formulae to convert the ADC value to voltage
  //MEASURED VOLTAGE = (ADC Value / ADC Resolution) * Reference Voltage
  Serial.print(voltageAV2);Serial.print(" V |");Serial.println();
// --------------------------------------------------------------------------------------------//
  Serial.print("AV3 | ");
  Serial.print(AV3);Serial.print(" | ");
  // Printing the value for checking 
  float voltageAV3 = (float(AV3)/65536) * 3.3; //formulae to convert the ADC value to voltage
  //MEASURED VOLTAGE = (ADC Value / ADC Resolution) * Reference Voltage
  Serial.print(voltageAV3);Serial.print(" V |");Serial.println();
// --------------------------------------------------------------------------------------------//
  Serial.print("AV4 | ");
  Serial.print(AV4);Serial.print(" | ");
  // Printing the value for checking 
  float voltageAV4 = (float(AV4)/65536) * 3.3; //formulae to convert the ADC value to voltage
  //MEASURED VOLTAGE = (ADC Value / ADC Resolution) * Reference Voltage
  Serial.print(voltageAV4);Serial.print(" V |");Serial.println();
// --------------------------------------------------------------------------------------------//
  Serial.print("AV5 | ");
  Serial.print(AV5);Serial.print(" | ");
  // Printing the value for checking 
  float voltageAV5 = (float(AV5)/65536) * 3.3; //formulae to convert the ADC value to voltage
  //MEASURED VOLTAGE = (ADC Value / ADC Resolution) * Reference Voltage
  Serial.print(voltageAV5);Serial.print(" V |");Serial.println();
// --------------------------------------------------------------------------------------------//
  Serial.print("AV6 | ");
  Serial.print(AV6);Serial.print(" | ");
  // Printing the value for checking 
  float voltageAV6 = (float(AV6)/65536) * 3.3; //formulae to convert the ADC value to voltage
  //MEASURED VOLTAGE = (ADC Value / ADC Resolution) * Reference Voltage
  Serial.print(voltageAV6);Serial.print(" V |");Serial.println();
// --------------------------------------------------------------------------------------------//
  Serial.print("AV7 | ");
  Serial.print(AV7);Serial.print(" | ");
  // Printing the value for checking 
  float voltageAV7 = (float(AV7)/65536) * 3.3; //formulae to convert the ADC value to voltage
  //MEASURED VOLTAGE = (ADC Value / ADC Resolution) * Reference Voltage
  Serial.print(voltageAV7);Serial.print(" V |");Serial.println();
// --------------------------------------------------------------------------------------------//

  Serial.println("----------------------------------------");
  delay(5000);
}
