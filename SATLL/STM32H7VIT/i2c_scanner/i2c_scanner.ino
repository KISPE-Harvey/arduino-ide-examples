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

*/

// i2c_scanner
//
// This sketch tests the standard 7-bit addresses
// Devices with higher bit address might not be seen properly.
//

/* Example pinmap for STM32H753ZIT 

 I2C-1 standard pins: PB7(sda) PB6(scl)

 Use it by "Wire" without pin declaration
Wire.begin();

 I2C-1 alternative pins: PB9(sda) PB8(scl)
 Remap the first I2C before call begin()
  Wire.setSDA(PB9);
  Wire.setSCL(PB8);
  Wire.begin();

 I2C-2: PF0(sda) PF1(scl)
 Remap the second I2C before call begin()
  Wire.setSDA(PF0);
  Wire.setSCL(PF1);
  Wire.begin();

 I2C-2 alternative pins: PB11(sda) PB10(scl)
 Remap the first I2C before call begin()
  Wire.setSDA(PB11);
  Wire.setSCL(PB8);
  Wire.begin();

 I2C-3: PC9(sda) PA8(scl)
 I2C-3 - disables USART1,  SDMMC1 and SWPMI1
 Remap the second I2C before call begin()
  Wire.setSDA(PC9);
  Wire.setSCL(PA8);
  Wire.begin();

 I2C-4: PF14(sda) PF15(scl)
 Remap the second I2C before call begin()
  Wire.setSDA(PF14);
  Wire.setSCL(PF15);
  Wire.begin();


 If you want to use the two I2Cs simultaneously, create a new instance for the second I2C
  TwoWire Wire2(PB11,PB10);
  Wire2.begin();

  TwoWire Wire3(PC9,PA8);
  Wire3.begin();

  TwoWire Wire4(PF14,PF15);
  Wire4.begin();

  Last updated 14/08/2024 Harvey Nixon
*/


#include <Wire.h>

void setup() {

  Serial.begin(9600);
  Wire.begin();
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
  Serial.println("I2C Scanner for STM32H753ZIT");
  Serial.println();
  delay(2000);

  pinMode(LED2, OUTPUT);
  digitalWrite(LED2, HIGH);

}


void loop() {
  byte error, address;
  int nDevices;

  Serial.println("Scanning...");

  nDevices = 0;
  for(address = 1; address < 127; address++) {
    // The i2c_scanner uses the return value of
    // the Write.endTransmisstion to see if
    // a device did acknowledge to the address.

    Wire.beginTransmission(address);
    error = Wire.endTransmission();

    if (error == 0) {
      Serial.print("I2C device found at address 0x");
      if (address < 16)
        Serial.print("0");
      Serial.println(address, HEX);

      nDevices++;
    }
    else if (error == 4) {
      Serial.print("Unknown error at address 0x");
      if (address < 16)
        Serial.print("0");
      Serial.println(address, HEX);
    }
  }
  if (nDevices == 0)
    Serial.println("No I2C devices found");
  else
    Serial.println("done");

  delay(5000);           // wait 5 seconds for next scan
}