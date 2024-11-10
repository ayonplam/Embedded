#ifndef HAL_LPIT_H
#define HAL_LPIT_H

#include "MKE16Z4.h"

typedef enum GPIO_PinState { GPIO_PIN_RESET = 0, GPIO_PIN_SET } GPIO_PinState;

void Port_ClockEnable (uint32_t offset);

void Port_SetPinMux (PORT_Type * PORTx, uint16_t GPIO_Pin, uint8_t mode);

void Port_SetPinPull_Up (PORT_Type * PORTx, uint16_t GPIO_Pin);

void PORT_SetPinInterruptConfig (PORT_Type * PORTx, uint16_t GPIO_Pin, uint8_t config);

void GPIO_SetPinOutput (FGPIO_Type * FGPIOx, uint16_t FGPIO_Pin);

void GPIO_SetPinState (FGPIO_Type * FGPIOx, uint16_t FGPIO_Pin, GPIO_PinState s);

void GPIO_TogglePinOutput (FGPIO_Type * FGPIOx, uint16_t FGPIO_Pin);



#endif /* HAL_LPIT_H */