
bool state = false;

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

  pinMode(USER_BTN, INPUT);
  // USER_BTN is pin PC13


}

void loop() {
  state = digitalRead(USER_BTN);

  if (state == false){

    Serial.println("NOT PRESSED");

  } else if (state == true){

    Serial.println("PRESSED");

  }

  delay(1);
}
