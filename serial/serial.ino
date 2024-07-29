
int number = 0;

void setup() {
  
  Serial.begin(9600);
  delay(2000);

}

void loop() {
  Serial.print("Hello World ");Serial.println(number);
  number = number + 1;

  delay(1000);
}
