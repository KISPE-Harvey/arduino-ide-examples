
int number = 0;

void setup() {
  
  Serial.begin(9600);
  delay(2000);

  Serial.println("------------------------------------------------"); 
  Serial.println();
  Serial.println("  _  _______  _____ _____  ______ ");
  Serial.println(" | |/ /_   _|/ ____|  __ \|  ____|");
  Serial.println(" | ' /  | | | (___ | |__) | |__   ");
  Serial.println(" |  <   | |  \___ \|  ___/|  __|  ");
  Serial.println(" | . \ _| |_ ____) | |    | |____ ");
  Serial.println(" |_|\_\_____|_____/|_|    |______|");
  Serial.println();
  Serial.println("------------------------------------------------");

}

void loop() {
  Serial.print("Hello World ");Serial.println(number);
  number = number + 1;

  delay(1000);
}
