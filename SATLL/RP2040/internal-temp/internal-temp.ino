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

  Development and test code for the RP2040 uC
  
  Last updated 15/08/2024 Harvey Nixon

*/
/*********
  Rui Santos & Sara Santos - Random Nerd Tutorials
  Complete project details at https://RandomNerdTutorials.com/raspberry-pi-pico-internal-temperature-arduino/
*********/

float tempC;
float tempF;

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
  Serial.println();
  Serial.println("Internal Temperature sensor Example for RP2040");
  Serial.println();
  delay(2000);

}

void loop() {
  tempC = analogReadTemp(); // Get internal temperature
  tempF = tempC * 9.0 / 5.0 + 32.0; // Fahrenheit conversion
  Serial.print("Temperature Celsius (ºC): ");
  Serial.println(tempC);
  Serial.print("Temperature Fahrenheit (ºF): ");
  Serial.println(tempF);
  delay(1000);
}