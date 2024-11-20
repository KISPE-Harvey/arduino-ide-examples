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
  A2 - PC3      -    ADC1/2
  A3 - PB1      -    ADC1/2
  A4 - PC2/PB9  -    ADC1/2/3
  A5 - PF10/PB8 -    ADC3
  A6 - PF4      -    ADC3
  A7 - PF5      -    ADC3
  A8 - PF6      -    ADC3

  Last updated 20/11/2024 Harvey Nixon
*/
#define MTR_THERM PA0
#define OBC_THERM PA3
#define PWR_THERM PA6
#define BCK_THERM PB0
#define BP_THERM PB1
#define SP_THERM PC4
#define COMMS_THERM PC3_C
#define AOCS_THERM PC1

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
  pinMode(MTR_THERM, INPUT);
  pinMode(OBC_THERM, INPUT);
  pinMode(PWR_THERM, INPUT);
  pinMode(BCK_THERM, INPUT);
  pinMode(BP_THERM, INPUT);
  pinMode(SP_THERM, INPUT);
  pinMode(COMMS_THERM, INPUT);
  pinMode(AOCS_THERM, INPUT);

  // Using the analogueRead() function the defult resolution is 10-bits meaning a resolution of 1024 steps
  // The STM32 ADC has a resolution of 16-bits meaning 65,536 steps.

  // Documentation on analogueRead() here:
  // https://www.arduino.cc/reference/en/language/functions/analog-io/analogread/
  analogReadResolution(16);

}

void loop() {
  int MTR = analogRead(MTR_THERM);    // read the ADC value 
  int OBC = analogRead(OBC_THERM);    // read the ADC value 
  int POW = analogRead(PWR_THERM);    // read the ADC value 
  int BCK = analogRead(BCK_THERM);    // read the ADC value 
  int BP = analogRead(BP_THERM);    // read the ADC value 
  int SP = analogRead(SP_THERM);    // read the ADC value 
  int COMMS = analogRead(COMMS_THERM);    // read the ADC value 
  int AOCS = analogRead(AOCS_THERM);    // read the ADC value 
  
  
  // The value will be an integer between 0 and 65,356 for the 16 bits

  //Serial.print(val);Serial.print(" ");
  // Printing the value for checking 

  //float voltage = (float(OBC))/65536) * 3.3; //formulae to convert the ADC value to voltage
  float resistance = 10000 * ((65536/float(OBC)) - 1);
  //MEASURED VOLTAGE = (ADC Value / ADC Resolution) * Reference Voltage

 // https://www.digikey.co.uk/en/maker/projects/how-to-measure-temperature-with-an-ntc-thermistor/4a4b326095f144029df7f2eca589ca54?msockid=3026511655ea6c65105345a654b26de5
  float RESISTOR_ROOM_TEMP = 10625.56;
  float ROOM_TEMP = 298.15;
  float BETA = 3430.0;
  float tKelvin;
  // tKelvin = (BETA * ROOM_TEMP) / 
  //          (BETA + (ROOM_TEMP * log(resistance / RESISTOR_ROOM_TEMP)));
    tKelvin = (BETA * ROOM_TEMP) / 
           (BETA + (ROOM_TEMP * log(RESISTOR_ROOM_TEMP/ resistance )));
  
  float tCelcius = tKelvin - 273.15;
  Serial.println(tCelcius);
  delay(500);
}
