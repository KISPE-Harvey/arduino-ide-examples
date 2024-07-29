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

  Development and test code for the STM32h753ZIT uC


  STM32H7 line has a 16-bit ADC
  The STM32 has 3.3v logic level so the max input to the ADC is 3.3v
  This mean that it will map voltages between 0v and 3.3v 
  with readings showing between 0 and 65,535 or 2^16

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
  pinMode(PF4, INPUT);

  // Using the analogueRead() function the defult resolution is 10-bits meaning a resolution of 1024 steps
  // The STM32 ADC has a resolution of 16-bits meaning 65,536 steps.

  // Documentation on analogueRead() here:
  // https://www.arduino.cc/reference/en/language/functions/analog-io/analogread/
  analogReadResolution(16);

}

void loop() {
  int val = analogRead(PF4);    // read the ADC value from pin A6 or PF4
  // The value will be an integer between 0 and 65,356 for the 16 bits

  Serial.print(val);Serial.print(" ");
  // Printing the value for checking 

  float voltage = (float(val)/65536) * 3.3; //formulae to convert the ADC value to voltage
  //MEASURED VOLTAGE = (ADC Value / ADC Resolution) * Reference Voltage
  
  Serial.println(voltage);
}
