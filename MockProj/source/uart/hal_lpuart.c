/*******************************************************************************
* Includes
******************************************************************************/
#include "hal_lpuart.h"
#include "MKE16Z4.h"

/*******************************************************************************
* MACRO
******************************************************************************/
#define MUX_ALT2 2U  /* Alternative 2 */

/*******************************************************************************
* Definiton
******************************************************************************/
/*!
 * @brief Set Pin Mux.
 * @param PORTx PORT base address.
 * @param LPUART_Pin Pin number.
 */
void HAL_SetPinUART (GPIO_Port PORTx, uint16_t LPUART_Pin)
{
    switch(PORTx)
    {
        case GPIO_PORT_A:
            PORTA->PCR[LPUART_Pin] |= PORT_PCR_MUX(MUX_ALT2);
            break;

        case GPIO_PORT_B:
            PORTB->PCR[LPUART_Pin] |= PORT_PCR_MUX(MUX_ALT2);
            break;

        case GPIO_PORT_C:
            PORTC->PCR[LPUART_Pin] |= PORT_PCR_MUX(MUX_ALT2);
            break;

        case GPIO_PORT_D:
            PORTD->PCR[LPUART_Pin] |= PORT_PCR_MUX(MUX_ALT2);
            break;

        case GPIO_PORT_E:
            PORTE->PCR[LPUART_Pin] |= PORT_PCR_MUX(MUX_ALT2);
            break;
    }
}

/*!
 * @brief Disable RX and TX.
 * @param LPUARTx LPUART Type
 */
void LPUART_DisableRXTX (LPUART_number LPUARTx)
{
    switch(LPUARTx)
    {
        case LPUART_0:
            LPUART0->CTRL &= ~(LPUART_CTRL_TE_MASK | LPUART_CTRL_RE_MASK);
            break;
        case LPUART_1:
            LPUART1->CTRL &= ~(LPUART_CTRL_TE_MASK | LPUART_CTRL_RE_MASK);
            break;
        case LPUART_2:
            LPUART2->CTRL &= ~(LPUART_CTRL_TE_MASK | LPUART_CTRL_RE_MASK);
            break;
    }
}

/*!
 * @brief Enable RX and TX.
 * @param LPUARTx LPUART Type
 */
void LPUART_EnableRXTX (LPUART_number LPUARTx)
{
    switch(LPUARTx)
    {
        case LPUART_0:
            LPUART0->CTRL |= (LPUART_CTRL_TE_MASK | LPUART_CTRL_RE_MASK);
            break;
        case LPUART_1:
            LPUART1->CTRL |= (LPUART_CTRL_TE_MASK | LPUART_CTRL_RE_MASK);
            break;
        case LPUART_2:
            LPUART2->CTRL |= (LPUART_CTRL_TE_MASK | LPUART_CTRL_RE_MASK);
            break;
    }
}

/*!
 * @brief Set Baudrate.
 * @param LPUARTx LPUART Type
 * @param osr Value of OSR will be set
 * @param sbr Value of SBR will be set
 */
void LPUART_SetBaudrate (LPUART_number LPUARTx, uint16_t osr, uint8_t sbr)
{
    uint32_t temp;

    switch(LPUARTx)
    {
        case LPUART_0:
            temp = LPUART0->BAUD;
            break;
        case LPUART_1:
            temp = LPUART1->BAUD;
            break;
        case LPUART_2:
            temp = LPUART2->BAUD;
            break;
    }

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

    switch(LPUARTx)
    {
        case LPUART_0:
            LPUART0->BAUD = temp | LPUART_BAUD_SBR(sbr);
            break;
        case LPUART_1:
            LPUART1->BAUD = temp | LPUART_BAUD_SBR(sbr);
            break;
        case LPUART_2:
            LPUART2->BAUD = temp | LPUART_BAUD_SBR(sbr);
            break;
    }
}

/*!
 * @brief Set Parity Bit.
 * @param LPUARTx LPUART Type
 * @param parity_enable
 * @param parity_type
 */
void LPUART_SetParity (LPUART_number LPUARTx, uint8_t parity_enable, uint8_t parity_type)
{
    uint32_t temp;

    switch(LPUARTx)
    {
        case LPUART_0:
            temp = LPUART0->CTRL & ~(LPUART_CTRL_PE_MASK | LPUART_CTRL_PT_MASK);
            break;
        case LPUART_1:
            temp = LPUART1->CTRL & ~(LPUART_CTRL_PE_MASK | LPUART_CTRL_PT_MASK);
            break;
        case LPUART_2:
            temp = LPUART2->CTRL & ~(LPUART_CTRL_PE_MASK | LPUART_CTRL_PT_MASK);
            break;
    }

    /* Enable or Disable parity bit */
    temp |= LPUART_CTRL_PE (parity_enable);
    /* Config parity type */
    temp |= LPUART_CTRL_PT (parity_type);

    switch(LPUARTx)
    {
        case LPUART_0:
            LPUART0->CTRL = temp;
            break;
        case LPUART_1:
            LPUART1->CTRL = temp;
            break;
        case LPUART_2:
            LPUART2->CTRL = temp;
            break;
    }
}

/*!
 * @brief Transmit Data Inversion.
 * @param LPUARTx LPUART Type
 * @param config Enable or Disable
 */
void LPUART_SetInverseTX (LPUART_number LPUARTx, uint8_t config)
{
    switch(LPUARTx)
    {
        case LPUART_0:
            LPUART0->CTRL |= LPUART_CTRL_TXINV(config);
            break;
        case LPUART_1:
            LPUART1->CTRL |= LPUART_CTRL_TXINV(config);
            break;
        case LPUART_2:
            LPUART2->CTRL |= LPUART_CTRL_TXINV(config);
            break;
    }

}

/*!
 * @brief Set First Bit
 * @param LPUARTx LPUART Type
 * @param config LSB or MSB
 */
void LPUART_SetFirstBit (LPUART_number LPUARTx, uint8_t config)
{
    switch(LPUARTx)
    {
        case LPUART_0:
            LPUART0->STAT |= LPUART_STAT_MSBF(config);
            break;
        case LPUART_1:
            LPUART1->STAT |= LPUART_STAT_MSBF(config);
            break;
        case LPUART_2:
            LPUART2->STAT |= LPUART_STAT_MSBF(config);
            break;
    }
}

/*!
 * @brief Set Stop Bit
 * @param LPUARTx LPUART Type
 * @param config 1 or 2 stop bit
 */
void LPUART_SetStopBit (LPUART_number LPUARTx, uint8_t config)
{
    switch(LPUARTx)
    {
        case LPUART_0:
            LPUART0->BAUD |= LPUART_BAUD_SBNS(config);
            break;
        case LPUART_1:
            LPUART1->BAUD |= LPUART_BAUD_SBNS(config);
            break;
        case LPUART_2:
            LPUART2->BAUD |= LPUART_BAUD_SBNS(config);
            break;
    }
}

/*!
 * @brief Set 8 Bit Data mode
 * @param LPUARTx LPUART Type
 */
void LPUART_Set8BitMode (LPUART_number LPUARTx)
{
    switch(LPUARTx)
    {
        case LPUART_0:
            /* Disable 10 bit mode */
            LPUART0->BAUD &= ~LPUART_BAUD_M10_MASK;
            /* Enable 8 bit mode */
            LPUART0->CTRL &= ~LPUART_CTRL_M_MASK;
            break;
        case LPUART_1:
            /* Disable 10 bit mode */
            LPUART1->BAUD &= ~LPUART_BAUD_M10_MASK;
            /* Enable 8 bit mode */
            LPUART1->CTRL &= ~LPUART_CTRL_M_MASK;
            break;
        case LPUART_2:
            /* Disable 10 bit mode */
            LPUART2->BAUD &= ~LPUART_BAUD_M10_MASK;
            /* Enable 8 bit mode */
            LPUART2->CTRL &= ~LPUART_CTRL_M_MASK;
            break;
    }
}

/*!
 * @brief Enable Receiver Interrupt
 * @param LPUARTx LPUART Type
 */
void LPUART_EnableReceiverInterrupt (LPUART_number LPUARTx)
{
    switch(LPUARTx)
    {
        case LPUART_0:
            LPUART0->CTRL |= LPUART_CTRL_RIE_MASK;
            break;
        case LPUART_1:
            LPUART1->CTRL |= LPUART_CTRL_RIE_MASK;
            break;
        case LPUART_2:
            LPUART2->CTRL |= LPUART_CTRL_RIE_MASK;
            break;
    }
}

/*!
 * @brief Enable LLPUART in NVIC
 * @param LPUARTx LPUART Type
 * @param data pointer data
 * @param length size of data
 */
void LPUART_enable_inNVIC (LPUART_number LPUARTx)
{
    switch(LPUARTx)
    {
        case LPUART_0:
            NVIC_EnableIRQ(LPUART0_IRQn);
            break;
        case LPUART_1:
            NVIC_EnableIRQ(LPUART1_IRQn);
            break;
        case LPUART_2:
            NVIC_EnableIRQ(LPUART2_IRQn);
            break;
    }
}

/*!
 * @brief Disable LPUART in NVIC
 * @param LPUARTx LPUART Type
 * @param data pointer data
 * @param length size of data
 */
void LPUART_disable_inNVIC (LPUART_number LPUARTx)
{
    switch(LPUARTx)
    {
        case LPUART_0:
            NVIC_DisableIRQ(LPUART0_IRQn);
            break;
        case LPUART_1:
            NVIC_DisableIRQ(LPUART1_IRQn);
            break;
        case LPUART_2:
            NVIC_DisableIRQ(LPUART2_IRQn);
            break;
    }
}

/*!
 * @brief Transfer Data
 * @param LPUARTx LPUART Type
 * @param data pointer data
 * @param length size of data
 */
void LPUART_PushData (LPUART_number LPUARTx, const uint8_t *data, size_t length)
{
    const uint8_t *dataAddress = data;
    size_t transferSize        = length;

    while (0U != transferSize)
    {
        /* Wait for Transmit data buffer empty */
        while (0U == (LPUART0->STAT & LPUART_STAT_TDRE_MASK))
        {
        }

        LPUART0->DATA = *(dataAddress); /* data buffer start get data */
        dataAddress++;
        transferSize--;
    }
    /* Ensure all the data in the transmit buffer are sent out to bus. */
    while (0U == (LPUART0->STAT & LPUART_STAT_TC_MASK))
    {
    }
}

/*!
 * @brief Receive Data
 * @param LPUARTx LPUART Type
 * @param data pointer data
 */
void LPUART_GetData (LPUART_number LPUARTx, uint8_t *data)
{
    switch(LPUARTx)
    {
        case LPUART_0:
            *data = (uint8_t)LPUART0->DATA;
            break;
        case LPUART_1:
            *data = (uint8_t)LPUART1->DATA;
            break;
        case LPUART_2:
            *data = (uint8_t)LPUART2->DATA;
            break;
    }
}

