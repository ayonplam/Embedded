#include "hal_lpit.h"

void Port_SetPinMux (PORT_Type * PORTx, uint16_t GPIO_Pin, uint8_t mode)
{
    PORTx->PCR[GPIO_Pin] |= PORT_PCR_MUX(mode);
}

void Port_SetPinPull_Up(PORT_Type * PORTx, uint16_t GPIO_Pin)
{
    PORTx->PCR[GPIO_Pin] |= PORT_PCR_PE(1);
    PORTx->PCR[GPIO_Pin] |= PORT_PCR_PS(1);
}

void PORT_SetPinInterruptConfig (PORT_Type * PORTx, uint16_t GPIO_Pin, uint8_t config)
{
    PORTx->PCR[GPIO_Pin] |= PORT_PCR_IRQC(config);
}

void GPIO_SetPinOutput (FGPIO_Type * FGPIOx, uint16_t FGPIO_Pin)
{
    FGPIOx->PDDR |= (1 << FGPIO_Pin);
}

void GPIO_SetPinState (FGPIO_Type * FGPIOx, uint16_t FGPIO_Pin, GPIO_PinState s)
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

void LPIT_Reset (LPIT_Type * LPIT_Base)
{
    LPIT_Base->MCR |= LPIT_MCR_SW_RST_MASK;
    LPIT_Base->MCR &= ~LPIT_MCR_SW_RST_MASK;
}

void LPIT_SetOperation (LPIT_Type * LPIT_Base)
{
    /* Setup timer operation in debug and doze modes and enable the module */
    LPIT_Base->MCR |= (LPIT_MCR_DBG_EN(1) | LPIT_MCR_DOZE_EN(1) | LPIT_MCR_M_CEN_MASK);
}

void LPIT_SetChannelChain (LPIT_Type * LPIT_Base, uint8_t channel, uint8_t config)
{
    LPIT_Base->CHANNEL[channel].TCTRL |= LPIT_TCTRL_CHAIN(config);
}

void LPIT_SetTimerMode (LPIT_Type * LPIT_Base, uint8_t channel, uint8_t config)
{
    LPIT_Base->CHANNEL[channel].TCTRL |= LPIT_TCTRL_MODE(config);
}

void LPIT_SetTimerPeriod (LPIT_Type * LPIT_Base, uint8_t channel, uint32_t tick)
{
    LPIT_Base->CHANNEL[channel].TVAL = tick;
}

void LPIT_EnableInterrupts (LPIT_Type * LPIT_Base, uint8_t channel)
{
    if (channel)
    {
        LPIT0->MIER |= LPIT_MIER_TIE1_MASK;
    }
    else
    {
        LPIT0->MIER |= LPIT_MIER_TIE0_MASK;
    }
}

void LPIT_DisableInterrupts (LPIT_Type * LPIT_Base, uint8_t channel)
{
    if (channel)
    {
        LPIT0->MIER &= ~LPIT_MIER_TIE1_MASK;
    }
    else
    {
        LPIT0->MIER &= ~LPIT_MIER_TIE0_MASK;
    }
}

void LPIT_StartTimer (LPIT_Type * LPIT_Base, uint8_t channel)
{
    uint32_t shift = LPIT_SETTEN_SET_T_EN_0_MASK;

    LPIT_Base->SETTEN |= shift << ((uint32_t)channel);
}

void LPIT_ClearInterruptFlag (LPIT_Type * LPIT_Base, uint8_t channel)
{
    if (channel)
    {
        LPIT0->MSR |= LPIT_MSR_TIF1(1);
    }
    else
    {
        LPIT0->MSR |= LPIT_MSR_TIF0(1);
    }

}