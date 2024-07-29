# Arduino IDE Examples
Example code for stm32 board in the Arduino IDE using the KISPE Board Manager

https://raw.githubusercontent.com/KISPE-Harvey/kispe-boardmanager/main/stm32/package_KISPE_index.json

## ADC
Example of how to use the analgueRead() functionality with STM32 chips.

## Button LED Cycle
Cycles through the different LED colurs based upon user input from the onboard button.
  
## Button Press
Takes the inout from the user button on the Nucleo Board and states if pressed or not, can be assigned to any pin and external button.

## i2c_scanner
Scans the i2c ports for sensors on the bus and reports which ones found, if any. Also has examples on how to enable additional i2c buses and alternative pins for the STM32H753ZITX microcontroller.

## Libraries 
Collection of libraries required for these examples to work.

## LIS3MDL Magnetometer example
Example code for the Adafruit LIS3MDL Magnetometer sensor and outputs values to the serial plotter in uTesla (micro Tesla).

## Serial
Example to use the serial port

For uploading to the Nucleo board it requires a few extra steps
- Upload code to Nucleo board using the eternal STM-LINK with the SWD method.

Using the standard Mass storage option makes the compter see the board as removable drive and does not enable the serial port when plugged in.

- Plug in the standard USB to the nucleo board and select the COM port for the onboard ST-LINK. There should now be serial outputs. This can work with the external ST-LINK connected, just the correct COM port needs to be selected.

## KISPE Logo
```
 _  _______  _____ _____  ______ 
| |/ /_   _|/ ____|  __ \|  ____|
| ' /  | | | (___ | |__) | |__
|  <   | |  \___ \|  ___/|  __|  
| . \ _| |_ ____) | |    | |____ 
|_|\_\_____|_____/|_|    |______| 
```
code to print in Arduino IDE - as // will print just /
```
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
```
