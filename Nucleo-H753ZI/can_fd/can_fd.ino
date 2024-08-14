#include "stm32h7xx_hal.h"
#include "stm32h7xx_hal_fdcan.h"
#include "STM32_FDCAN.h"

STM32_FDCAN fdcan1(FDCAN1, PA11, PA12);

void setup() {
    fdcan1.begin();
}

void loop() {
    // Transmit a CAN FD message
    FDCAN_TxHeaderTypeDef txHeader;
    txHeader.Identifier = 0x123;
    txHeader.DataLength = FDCAN_DLC_BYTES_8;
    uint8_t txData[8] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08};
    fdcan1.write(txHeader, txData);

    // Receive a CAN FD message
    if (fdcan1.available()) {
        FDCAN_RxHeaderTypeDef rxHeader;
        uint8_t rxData[8];
        fdcan1.read(rxHeader, rxData);
        // Process the received message
    }
}
