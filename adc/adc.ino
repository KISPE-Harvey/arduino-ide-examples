

 //STM32H7 line has a 16-bit ADC
 //The STM32 has 3.3v logic level so the max input to the ADC is 3.3v
 // This mean that it will map voltages between 0v and 3.3v 
 //with readings showing between 0 and 65,535 or 2^16

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

  pinMode(PF4, INPUT);
  analogReadResolution(16);

//INPUT VOLTAGE = (ADC Value / ADC Resolution) * Reference Voltage


}

void loop() {
  int val = analogRead(PF4);    // read the ADC value from pin A6 or PF4
  Serial.print(val);Serial.print(" ");
  float voltage = (float(val)/65536) * 3.3; //formulae to convert the ADC value to voltage

  Serial.println(voltage);

}
