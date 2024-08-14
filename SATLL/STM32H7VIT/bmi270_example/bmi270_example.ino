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
/* Example pinmap for STM32H753VIT 

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
#include "SparkFun_BMI270_Arduino_Library.h"

// Create a new sensor object
BMI270 imu;

// I2C address selection
uint8_t i2cAddress = BMI2_I2C_PRIM_ADDR; // 0x68
//uint8_t i2cAddress = BMI2_I2C_SEC_ADDR; // 0x69

void setup()
{
    // Start serial
    Serial.begin(9600);
    // Initialize the I2C library
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
  Serial.println("BMI270 Example for STM32H753VIT");
  Serial.println();
  delay(2000);

    // Check if sensor is connected and initialize
    // Address is optional (defaults to 0x68)
    while(imu.beginI2C(i2cAddress) != BMI2_OK)
    {
        // Not connected, inform user
        Serial.println("Error: BMI270 not connected, check wiring and I2C address!");

        // Wait a bit to see if connection is established
        delay(1000);
    }

    Serial.println("BMI270 connected!");
}

void loop()
{
    // Get measurements from the sensor. This must be called before accessing
    // the sensor data, otherwise it will never update
    imu.getSensorData();

    // Print acceleration data
    Serial.print("Acceleration in g's");
    Serial.print("\t");
    Serial.print("X: ");
    Serial.print(imu.data.accelX, 3);
    Serial.print("\t");
    Serial.print("Y: ");
    Serial.print(imu.data.accelY, 3);
    Serial.print("\t");
    Serial.print("Z: ");
    Serial.print(imu.data.accelZ, 3);

    Serial.print("\t");

    // Print rotation data
    Serial.print("Rotation in deg/sec");
    Serial.print("\t");
    Serial.print("X: ");
    Serial.print(imu.data.gyroX, 3);
    Serial.print("\t");
    Serial.print("Y: ");
    Serial.print(imu.data.gyroY, 3);
    Serial.print("\t");
    Serial.print("Z: ");
    Serial.println(imu.data.gyroZ, 3);

    // Print 50x per second
    delay(20);
}