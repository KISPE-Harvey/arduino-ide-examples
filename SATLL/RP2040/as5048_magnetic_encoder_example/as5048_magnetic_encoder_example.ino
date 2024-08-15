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

  Development and test code for the RP2040 uC
  
  Last updated 15/08/2024 Harvey Nixon 

*/

#include <SimpleFOC.h>
#include <SPI.h>
// MagneticSensorSPI(MagneticSensorSPIConfig_s config, int cs)
//  config  - SPI config
//  cs      - SPI chip select pin 
// magnetic sensor instance - SPI
//MagneticSensorSPI sensor = MagneticSensorSPI(AS5048_SPI, 10);
// alternative constructor (chipselsect, bit_resolution, angle_read_register, )

MagneticSensorSPI sensor = MagneticSensorSPI(AS5147_SPI, 17); //change to SPI CS for encoder 

void setup() {
  // monitoring port
  SPI.begin();
  Serial.begin(115200);
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
  Serial.println("AS5048 Magnetic Encoder Example for RP2040");
  Serial.println();
  delay(2000);
  // initialise magnetic sensor hardware
  sensor.init();

  Serial.println("Sensor ready");
  _delay(1000);
}

void loop() {
  // iterative function updating the sensor internal variables
  // it is usually called in motor.loopFOC()
  // this function reads the sensor hardware and 
  // has to be called before getAngle nad getVelocity
  delayMicroseconds(10);
  sensor.update();
  delayMicroseconds(10);
  // display the angle and the angular velocity to the terminal
  Serial.print(sensor.getAngle());
  Serial.print("\t");
  Serial.println(sensor.getVelocity());
  delay(500);
}
