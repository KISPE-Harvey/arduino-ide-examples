#include <Adafruit_NeoPixel.h>
#define OBC_THERM PA3
bool RT = false;
float Room_Temp;
float rounded_tCelcius;
// Which pin on the Arduino is connected to the NeoPixels?
#define PIN        PB12 // On Trinket or Gemma, suggest changing this to 1

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS 1 // Popular NeoPixel ring size
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

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

  pinMode(OBC_THERM, INPUT);
  analogReadResolution(16);

//init the sensor






pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)
pixels.clear(); // Set all pixel colors to 'off'

}

void loop() {
  int OBC = analogRead(OBC_THERM);    // read the ADC value 

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

    if (!RT){
    Room_Temp = (round(tCelcius*10)) / 10;
    RT = true;
  }

 rounded_tCelcius = (round(tCelcius*10)) / 10;

  // LEDs 
    //Round to 1 dp?
  if( (rounded_tCelcius - Room_Temp) > 0){
    //RED 
    pixels.setPixelColor(0, pixels.Color(150, 0, 0));
    //pixels.clear();
    pixels.show();   // Send the updated pixel colors to the hardware.

  } else if ( (rounded_tCelcius - Room_Temp) < 0){
    //Blue
    pixels.setPixelColor(0, pixels.Color(0, 0, 150));
    //pixels.clear();
    pixels.show();   // Send the updated pixel colors to the hardware.

  } else {
    //Green LED
    //pixels.clear();
    pixels.setPixelColor(0, pixels.Color(0, 150, 0));
    //pixels.clear();
    pixels.show();   // Send the updated pixel colors to the hardware.
  }


  
  Serial.print(Room_Temp);Serial.print("\t");
  Serial.println(tCelcius);
  
  
  
  
  delay(500);

}
