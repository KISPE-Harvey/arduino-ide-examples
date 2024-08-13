#ifndef STM32_FDCAN_H
#define STM32_FDCAN_H

#include "stm32h7xx_hal.h"
#include "stm32h7xx_hal_fdcan.h"

class STM32_FDCAN {
public:
    STM32_FDCAN(FDCAN_GlobalTypeDef *instance, uint32_t rxPin, uint32_t txPin);
    void begin();
    void write(FDCAN_TxHeaderTypeDef &header, uint8_t *data);
    bool available();
    void read(FDCAN_RxHeaderTypeDef &header, uint8_t *data);

private:
    FDCAN_HandleTypeDef hfdcan;
    FDCAN_FilterTypeDef sFilterConfig;
};

#endif // STM32_FDCAN_H
