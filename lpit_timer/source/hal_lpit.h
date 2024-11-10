#ifndef HAL_LPIT_H
#define HAL_LPIT_H

#include "MKE16Z4.h"

#define RED_LED_PIN   5U /* Port B pin 5 */
#define GREEN_LED_PIN 4U /* Port B pin 4 */

#define CHANNEL0 0U /* module LPIT Channel 0 */
#define CHANNEL1 1U /* module LPIT Channel 1 */

#define TIMER_MODE0 0U /* module LPIT timer 32-bit Periodic Counter */

#define CHAIN_ENABLE 1U
#define CHAIN_DISABLE 0U

typedef enum GPIO_PinState { GPIO_PIN_RESET = 0, GPIO_PIN_SET } GPIO_PinState;

void Port_SetPinMux (PORT_Type * PORTx, uint16_t GPIO_Pin, uint8_t mode);

void Port_SetPinPull_Up (PORT_Type * PORTx, uint16_t GPIO_Pin);

void PORT_SetPinInterruptConfig (PORT_Type * PORTx, uint16_t GPIO_Pin, uint8_t config);

void GPIO_SetPinOutput (FGPIO_Type * FGPIOx, uint16_t FGPIO_Pin);

void GPIO_SetPinState (FGPIO_Type * FGPIOx, uint16_t FGPIO_Pin, GPIO_PinState s);

void GPIO_TogglePinOutput (FGPIO_Type * FGPIOx, uint16_t FGPIO_Pin);

void LPIT_Reset(LPIT_Type * LPIT_Base);

void LPIT_SetOperation (LPIT_Type * LPIT_Base);

void LPIT_SetChannelChain (LPIT_Type * LPIT_Base, uint8_t channel, uint8_t config);

void LPIT_SetTimerMode (LPIT_Type * LPIT_Base, uint8_t channel, uint8_t config);

void LPIT_SetTimerPeriod (LPIT_Type * LPIT_Base, uint8_t channel, uint32_t tick);

void LPIT_EnableInterrupts (LPIT_Type * LPIT_Base, uint8_t channel);

void LPIT_DisableInterrupts (LPIT_Type * LPIT_Base, uint8_t channel);

void LPIT_StartTimer (LPIT_Type * LPIT_Base, uint8_t channel);

void LPIT_ClearInterruptFlag (LPIT_Type * LPIT_Base, uint8_t channel);

#endif /* HAL_LPIT_H */