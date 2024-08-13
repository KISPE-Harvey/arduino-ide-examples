#include "STM32_FDCAN.h"

STM32_FDCAN::STM32_FDCAN(FDCAN_GlobalTypeDef *instance, uint32_t rxPin, uint32_t txPin) {
    hfdcan.Instance = instance;
    // Configure the pins and other initialization code
}

void STM32_FDCAN::begin() {
    // Initialize the FDCAN peripheral
    HAL_FDCAN_Init(&hfdcan);
}

void STM32_FDCAN::write(FDCAN_TxHeaderTypeDef &header, uint8_t *data) {
    HAL_FDCAN_AddMessageToTxFifoQ(&hfdcan, &header, data);
}

bool STM32_FDCAN::available() {
    return HAL_FDCAN_GetRxFifoFillLevel(&hfdcan, FDCAN_RX_FIFO0) > 0;
}

void STM32_FDCAN::read(FDCAN_RxHeaderTypeDef &header, uint8_t *data) {
    HAL_FDCAN_GetRxMessage(&hfdcan, FDCAN_RX_FIFO0, &header, data);
}
