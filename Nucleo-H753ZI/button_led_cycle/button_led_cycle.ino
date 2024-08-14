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

  Last updated 29/07/2024 Harvey Nixon
*/
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

  // The LED pins get set out outputs so we can toggle them on or off
  pinMode(PB0,OUTPUT);  // Green LED
  pinMode(PE1,OUTPUT);  // Orange LED
  pinMode(PB14,OUTPUT); // Red LED
}

void loop() {

  button_state = digitalRead(USER_BTN);
  // button_state is true or false, true if being pressed down, false if not

  Serial.println(state);
  // Just to keep track of the state 

if(previous_button_state != button_state){ 
  // This line makes sure not to chnage the state unless the state has chnaged
  // This stopped the issue of holding down the button and having he state increase
  
  if (button_state == true){
    // if button pressed, increase the state number by 1

    state = state + 1;
  } 
  if (state == 1){    
    digitalWrite(PB14, LOW);
    digitalWrite(PE1, LOW);
    digitalWrite(PB0, HIGH);
    // Turns on Green LED, turns off all others
  }
  if (state == 2){
    digitalWrite(PB0, LOW);
    digitalWrite(PB14, LOW);
    digitalWrite(PE1, HIGH);
    // Turns on Orange LED, turns off all others
  }
  if (state == 3){
    digitalWrite(PB7, LOW);
    digitalWrite(PE1, LOW);    
    digitalWrite(PB14, HIGH);
    // Turns on Red LED, turns off all others
  }
  if (state == 4){
    digitalWrite(PB0, HIGH);
    digitalWrite(PE1, HIGH);
    digitalWrite(PB14, HIGH);
    // Turns on all LEDs
  }
  if (state == 5){
    digitalWrite(PB0, LOW);
    digitalWrite(PE1, LOW);
    digitalWrite(PB14, LOW);
    // Turns off all LEDs
    state = 0;
    // Resets the state value once the counter has gotten too high
  }
  previous_button_state = button_state;
  // Is used to check if the state has changed from before
}

  delay(1);
}
