#include "hal_lpuart.h"

void Port_SetPinMux (PORT_Type * PORTx, uint16_t GPIO_Pin, uint8_t mode)
{
    PORTx->PCR[GPIO_Pin] |= PORT_PCR_MUX(mode);
}

void LPUART_DisableRXTX (LPUART_Type * LPUARTx)
{
    LPUARTx->CTRL &= ~(LPUART_CTRL_TE_MASK | LPUART_CTRL_RE_MASK);
}

void LPUART_EnableRXTX (LPUART_Type * LPUARTx)
{
    LPUARTx->CTRL |= (LPUART_CTRL_TE_MASK | LPUART_CTRL_RE_MASK);
}

void LPUART_SetBaudrate (LPUART_Type * LPUARTx, uint16_t osr, uint8_t sbr)
{
    uint32_t temp;
    temp = LPUARTx->BAUD;

    /* Check if OSR is between 4x and 7x oversampling.
     * If so, then "BOTHEDGE" sampling must be turned on */
    if ((osr > 3U) && (osr < 8U))
    {
        temp |= LPUART_BAUD_BOTHEDGE_MASK;
    }

    /* Write the osr value to the BAUD registers */
    temp &= ~LPUART_BAUD_OSR_MASK;
    temp |= LPUART_BAUD_OSR((uint32_t)osr - 1UL);

    /* Write the sbr value to the BAUD registers */
    temp &= ~LPUART_BAUD_SBR_MASK;
    LPUARTx->BAUD = temp | LPUART_BAUD_SBR(sbr);
}

void LPUART_SetParity (LPUART_Type * LPUARTx, uint8_t parity_enable, uint8_t parity_type)
{
    uint32_t temp;
    temp = LPUARTx->CTRL & ~(LPUART_CTRL_PE_MASK | LPUART_CTRL_PT_MASK);

    /* Enable or Disable parity bit */
    temp |= LPUART_CTRL_PE (parity_enable);
    /* Config parity type */
    temp |= LPUART_CTRL_PT (parity_type);

    LPUARTx->CTRL = temp;
}

void LPUART_SetInverseTX (LPUART_Type * LPUARTx, uint8_t config)
{

    LPUARTx->CTRL |= LPUART_CTRL_TXINV(config);
}

void LPUART_SetFirstBit (LPUART_Type * LPUARTx, uint8_t config)
{
    LPUARTx->STAT |= LPUART_STAT_MSBF(config);
}

void LPUART_SetStopBit (LPUART_Type * LPUARTx, uint8_t config)
{
    LPUARTx->BAUD |= LPUART_BAUD_SBNS(config);
}

void LPUART_Set8BitMode (LPUART_Type * LPUARTx)
{
    /* Disable 10 bit mode */
    LPUARTx->BAUD &= ~LPUART_BAUD_M10_MASK;
    /* Enable 8 bit mode */
    LPUARTx->CTRL &= ~LPUART_CTRL_M_MASK;
}

void LPUART_EnableReceiverInterrupt (LPUART_Type * LPUARTx)
{
    LPUARTx->CTRL |= LPUART_CTRL_RIE_MASK;
}