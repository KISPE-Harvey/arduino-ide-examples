#ifndef tcn75_h
#define tcn75_h 1

#if defined(ARDUINO) && ARDUINO >= 100
    #include "Arduino.h"
#else
    #include "WProgram.h"
#endif

#include <Wire.h>

#define TEMPERATURE_REGISTER 0
#define CONFIG_REGISTER 1
#define HISTERESYS_REGISTER 2
#define SETPONT_REGISTER 3


class tcn75 {
  public:
    tcn75(int myaddress);
    float readTemperature();
    float readHisteresys();
    float readSetPoint();
    void writeSetPoint(float temperatura);
    void writeHisteresys(float temperatura);
    byte readConfig();
    void writeCmptrInt(bool cmptrint);
    void writeShutdown(bool powermode);
    void writePolarity(bool polarity);
    void writeFault(byte fault);
  protected:
    int address;
    float readFloat(byte registro);
    void writeFloat(byte registro, float number);
    float convertTemp(byte aa, byte bb);
    void writeConfig(byte fault);
};

#endif
