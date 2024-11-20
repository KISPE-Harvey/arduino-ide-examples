#include "tcn75.h"
#define tcn75address 0x4F // with pins 5~7 set to GND, the device address is 0x48

tcn75 termometro(tcn75address);

void setup()
{
  Serial.begin(9600);
  Wire.begin();
 // while (!Serial);
  
  /*
  termometro.writeSetPoint(20.5);
  termometro.writeHisteresys(5.5);
  termometro.writeCmptrInt(false);
  termometro.writePolarity(false);
  termometro.writeShutdown(false);
  termometro.writeFault(0);
  */
  
  Serial.println();
  Serial.print("Current config = ");
  Serial.println(termometro.readConfig(), BIN);
  Serial.print("Current histeresys = ");
  Serial.println(termometro.readHisteresys());
  Serial.print("Current setpoint = ");
  Serial.println(termometro.readSetPoint());
}

void loop()
{
  Serial.print("Current temperature = ");
  Serial.println(termometro.readTemperature());
  
  delay(1000);
}
