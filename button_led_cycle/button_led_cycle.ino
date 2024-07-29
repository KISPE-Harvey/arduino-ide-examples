
int state = 0;
bool button_state = false;
bool previous_button_state = true;

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
  pinMode(PB0,OUTPUT);
  pinMode(PE1,OUTPUT);
  pinMode(PB14,OUTPUT);
}

void loop() {
  button_state = digitalRead(USER_BTN);
  Serial.println(state);
if(previous_button_state != button_state){
  
  if (button_state == true){
    state = state + 1;
  } 
  if (state == 1){    
    digitalWrite(PB14, LOW);
    digitalWrite(PE1, LOW);
    digitalWrite(PB0, HIGH);
  }
  if (state == 2){
    digitalWrite(PB0, LOW);
    digitalWrite(PB14, LOW);
    digitalWrite(PE1, HIGH);
  }
  if (state == 3){
    digitalWrite(PB7, LOW);
    digitalWrite(PE1, LOW);    
    digitalWrite(PB14, HIGH);
  }
  if (state == 4){
    digitalWrite(PB0, HIGH);
    digitalWrite(PE1, HIGH);
    digitalWrite(PB14, HIGH);
  }
  if (state == 5){
    digitalWrite(PB0, LOW);
    digitalWrite(PE1, LOW);
    digitalWrite(PB14, LOW);
    state = 0;
  }
  previous_button_state = button_state;
}


  delay(1);
}
