# Arduino IDE Examples
Example code for stm32 board in the Arduino IDE using the KISPE Board Manager

https://raw.githubusercontent.com/KISPE-Harvey/kispe-boardmanager/main/stm32/package_KISPE_index.json

## Serial
Example to use the serial port

For uploading to the Nucleo board it requires a few extra steps
- Upload code to Nucleo board using the eternal STM-LINK with the SWD method.

Using the standard Mass storage option makes the compter see the board as removable drive and does not enable the serial port when plugged in.

- Plug in the standard USBB to the nucleo board and select the COM port for the onboard ST-LINK. There should now be serial outputs. This can work with the external ST-LINK connected, just the correct COM port needs to be selected.
  
