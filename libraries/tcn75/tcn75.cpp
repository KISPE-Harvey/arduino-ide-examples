#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif

#include "tcn75.h"

tcn75::tcn75 ( int myaddress ){
	address=myaddress;
  Wire.begin(); 
}

byte tcn75::readConfig()
{
    byte config;
    Wire.beginTransmission(address);
    Wire.write((byte)CONFIG_REGISTER);
    Wire.endTransmission();
    Wire.requestFrom(address, 1);
    config = Wire.read(); 
    return(config);
}

float tcn75::readHisteresys()
{
  return(readFloat(HISTERESYS_REGISTER ));
}

float tcn75::readTemperature()
{
  return(readFloat(TEMPERATURE_REGISTER));
}

float tcn75::readSetPoint()
{
  return(readFloat(SETPONT_REGISTER));
}

void tcn75::writeSetPoint(float temperatura){
  // Serial.print("Writing temperature: ");
  writeFloat(SETPONT_REGISTER, temperatura);
}

void tcn75::writeHisteresys(float temperatura){
  // Serial.print("Writing histeresys: ");
  writeFloat(HISTERESYS_REGISTER, temperatura);
}

void tcn75::writeCmptrInt(bool cmptrint) {
  byte readvalue = readConfig();
  byte newvalue;
  if (cmptrint) {
      newvalue = readvalue | B10;
  } else {
    newvalue = readvalue & B11101;
  }
  writeConfig(newvalue);
}

void tcn75::writeFault(byte fault) {
  fault &= B11;
  fault <<= 3;
  fault |= B111;
  byte readvalue = readConfig();
  readvalue |= 11000;
  byte newvalue = fault & readvalue;
  writeConfig(newvalue);
}

void tcn75::writeShutdown(bool powermode) {
  byte readvalue = readConfig();
  byte newvalue;
  if (powermode) {
      newvalue = readvalue | B1;
  } else {
    newvalue = readvalue & B11110;
  }
  writeConfig(newvalue);
}

void tcn75::writePolarity(bool polarity) {
  byte readvalue = readConfig();
  byte newvalue;
  if (polarity) {
      newvalue = readvalue | B100;
  } else {
    newvalue = readvalue & B11011;
  }
  writeConfig(newvalue);
}


void tcn75::writeConfig(byte config){
  config = config & B11111;
  Wire.beginTransmission(address);// Start transmission
  Wire.write((byte)CONFIG_REGISTER);
  Wire.write(config);
  Wire.endTransmission();
}

float tcn75::readFloat(byte registro)
{
  byte a, b;
  float temp=.0;
  Wire.beginTransmission(address);  // Start transmission
  Wire.write((byte)registro);              // move your register pointer back to 00h
  Wire.endTransmission();           // Stop transmission
  Wire.requestFrom(address, 2);     // Send me the contents of your first two bytes
  a = Wire.read();                  // first received byte stored here
  b = Wire.read();                  // second received byte stored here
  /*
  #ifdef DEBUG
    Serial.println();
    Serial.print("A:");
    Serial.println(a, BIN);
    Serial.print("B:");
    Serial.println(b, BIN);
  #endif
  */
  temp=convertTemp(a, b);     // convert received bytes into float value
  return(temp);
}

float tcn75::convertTemp(byte aa, byte bb)
{
  float temp;
  if (aa>127)            // check for below zero degrees
  {
    aa=~aa;
    temp=(aa+1)*-1;
    if (bb==128)         // check for 0.5 fraction
    {
      temp-=0.5;
    }
  }
  else                   // it must be above zero degrees
  {
    temp=aa;
    if (bb==128)         // check for 0.5 fraction
    {
      temp+=0.5;
    }
  }
  return(temp);
}

void tcn75::writeFloat(byte registro, float number) {
  // Serial.println(number);
  byte a = int(number);
  /*
  #ifdef DEBUG
    Serial.print("A:");
    Serial.println(a, BIN);
  #endif
  */
  byte b;
  if ( abs(number-(int(number))) > 0 ) {
    b = B10000000;
  } else {
    b = 0;
  }
  /*
  #ifdef DEBUG
    Serial.print("B:");
    Serial.println(b, BIN);
  #endif
  */
  Wire.beginTransmission(address);// Start transmission
  Wire.write((byte)registro);
  Wire.write(a);
  Wire.write(b);
  Wire.endTransmission();
}
