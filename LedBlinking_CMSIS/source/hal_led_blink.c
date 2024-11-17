#include "hal_led_blink.h"

void Port_ClockEnable (uint32_t offset)
{
    PCC->CLKCFG[offset] |= PCC_CLKCFG_CGC(1);
}

void Port_SetPinMux (PORT_Type * PORTx, uint16_t GPIO_Pin, uint8_t mode)
{
    PORTx->PCR[GPIO_Pin] |= PORT_PCR_MUX(mode);
}

void Port_SetPinPull_Up(PORT_Type * PORTx, uint16_t GPIO_Pin)
{
    PORTx->PCR[GPIO_Pin] |= PORT_PCR_PE(1);
    PORTx->PCR[GPIO_Pin] |= PORT_PCR_PS(1);

}

void GPIO_SetPinOutput (FGPIO_Type * FGPIOx, uint16_t FGPIO_Pin)
{
    FGPIOx->PDDR |= (1 << FGPIO_Pin);
}

void GPIO_SetPinInput (FGPIO_Type * FGPIOx, uint16_t FGPIO_Pin)
{
    FGPIOx->PDDR &= ~(1 << FGPIO_Pin);
}

void GPIO_SetPinDefault (FGPIO_Type * FGPIOx, uint16_t FGPIO_Pin, GPIO_PinState s)
{
    if (s)
    {
        FGPIOx->PDOR |= (1 << FGPIO_Pin);
    }
    else
    {
        FGPIOx->PDOR &= ~(1 << FGPIO_Pin);
    }
}

void GPIO_TogglePinOutput (FGPIO_Type * FGPIOx, uint16_t FGPIO_Pin)
{
    FGPIOx->PTOR |= (1 << FGPIO_Pin);
}

GPIO_PinState readPin(GPIO_Type * GPIOx, uint16_t GPIO_Pin)
{
    GPIO_PinState bitstatus;

    if ((GPIOx->PDIR & (1 << GPIO_Pin)) != (uint32_t)GPIO_PIN_RESET)
    {
       bitstatus = GPIO_PIN_SET;
    }
    else
    {
       bitstatus = GPIO_PIN_RESET;
    }

    return bitstatus;
}