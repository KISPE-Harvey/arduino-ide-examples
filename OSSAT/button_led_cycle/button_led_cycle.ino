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

  Last updated 13/08/2024 Harvey Nixon
*/
int state1 = 0;
bool button1_state = false;
bool previous_button1_state = true;
int state2 = 0;
bool button2_state = false;
bool previous_button2_state = true;

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

  pinMode(USER_BTN1, INPUT);
  // USER_BTN1 is pin PC6

  pinMode(USER_BTN2, INPUT);
  // USER_BTN is pin PC4

  // The LED pins get set out outputs so we can toggle them on or off
  pinMode(LED1,OUTPUT);  // LED1 is pin PG6
  pinMode(LED2,OUTPUT);  // LED2 is pin PG7
  pinMode(LED3,OUTPUT);  // LED3 is pin PG8
}

void loop() {

  button1_state = digitalRead(USER_BTN1);
  button2_state = digitalRead(USER_BTN2);
  // button_state is true or false, true if being pressed down, false if not

  Serial.println(state1);
  //Serial.println(state2);
  // Just to keep track of the state 

if(previous_button1_state != button1_state){ 
  // This line makes sure not to chnage the state unless the state has chnaged
  // This stopped the issue of holding down the button and having he state increase
  
  if (button_state1 == true){
    // if button pressed, increase the state number by 1

    state1 = state1 + 1;
  } 
  if (state1 == 1){    
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, LOW);
    digitalWrite(LED1, HIGH);
    // Turns on LED1, turns off all others
  }
  if (state1 == 2){
    digitalWrite(LED1, LOW);
    digitalWrite(LED3, LOW);
    digitalWrite(LED2, HIGH);
    // Turns on LED2, turns off all others
  }
  if (state1 == 3){
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);    
    digitalWrite(LED3, HIGH);
    // Turns on LED3, turns off all others
  }
  if (state1 == 4){
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, HIGH);
    digitalWrite(LED3, HIGH);
    // Turns on all LEDs
  }
  if (state1 == 5){
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, LOW);
    // Turns off all LEDs
    state1 = 0;
    // Resets the state value once the counter has gotten too high
  }
  previous_button1_state = button1_state;
  // Is used to check if the state has changed from before
}

  delay(1);
}
