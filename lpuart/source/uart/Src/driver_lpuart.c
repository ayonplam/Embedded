#include "driver_lpuart.h"

/*******************************************************************************
* Variables
******************************************************************************/


/*******************************************************************************
* Prototypes
******************************************************************************/
void LPUART0_InitPin (void);

/**
 ****************************************************************************************
 * @brief Config Clock Source
 *
 * This function set clock for module LPUART0
 *
 * @param none
 ****************************************************************************************
 */
void LPUART0_ConfigClockSource (void)
{
    /* Config FIRC Divider: Divide by 2 */
    FIRC_DividerConfig (FIRC_DIV2_2);

    /* Config PCC_PCS: use FIRC 48MHz */
    PCC_PCSConfig (PCC_LPUART0_INDEX, PCS_FIRC_SOURCE);
}

/**
 ****************************************************************************************
 * @brief Initialize LPUART0
 *
 * This function Initialize LPUART0
 *
 * @param myOSR_SBR pointer to a object osr_sbr
 ****************************************************************************************
 */
void LPUART0_Init (osr_sbr * myOSR_SBR)
{
    /* Init pin UART */
    LPUART0_InitPin ();

    /* Enable clock module LPUART0 */
    PCC_ClockEnable (PCC_LPUART0_INDEX);

    /* Disable RX TX before config */
    LPUART_DisableRXTX (LPUART0);

    /* Set OSR, SBR */
    LPUART_SetBaudrate (LPUART0, myOSR_SBR->osr, myOSR_SBR->sbr);

    /* Set parity bit disable */
    LPUART_SetParity (LPUART0, PARITY_DISABLE, EVEN_PARITY);

    /* Set first bit is LSB */
    LPUART_SetFirstBit (LPUART0, LSB);

    /* Set 2 stop bit */
    LPUART_SetStopBit (LPUART0, ONE_STOP_BIT);

    /* TX not inverse */
    LPUART_SetInverseTX (LPUART0, INV_DIS);

    /* 8 bit mode */
    LPUART_Set8BitMode (LPUART0);

    /* Enable receiver interrupt*/
    LPUART_EnableReceiverInterrupt (LPUART0);

    /* Enable RX TX after config */
    LPUART_EnableRXTX(LPUART0);

    /* Enable interrupt in NVIC */
    NVIC_EnableIRQ(LPUART0_IRQn);
}

/**
 ****************************************************************************************
 * @brief Caculate value of OSR and SBR
 *
 * @param clk_src Module LPUART clock frequency
 * @param baudrate Value of baudrate want to set
 * @param myOSR_SBR pointer to a object osr_sbr
 ****************************************************************************************
 */
void Caculate_OSR_SBR (uint32_t clk_src, uint32_t baudrate, osr_sbr * myOSR_SBR)
{
    osr_sbr tempOSR_SBR;
    uint32_t tempDiff, calculatedBaud, baudDiff;

    for (tempOSR_SBR.osr = 4U; tempOSR_SBR.osr <= 32U; tempOSR_SBR.osr++)
    {
        /* calculate the temporary sbr value   */
        tempOSR_SBR.sbr = (uint16_t)((clk_src * 10U / (baudrate * (uint32_t)tempOSR_SBR.osr) + 5U) / 10U);
        /*set sbrTemp to 1 if the sourceClockInHz can not satisfy the desired baud rate*/
        if (tempOSR_SBR.sbr == 0U)
        {
            tempOSR_SBR.sbr = 1U;
        }
        /* Calculate the baud rate based on the temporary OSR and SBR values */
        calculatedBaud = (clk_src / ((uint32_t)tempOSR_SBR.osr * (uint32_t)tempOSR_SBR.sbr));
        tempDiff       = calculatedBaud > baudrate ? (calculatedBaud - baudrate) :
                                                           (baudrate - calculatedBaud);

        if (tempDiff <= baudDiff)
        {
            baudDiff = tempDiff;
            myOSR_SBR->osr = tempOSR_SBR.osr; /* update and store the best OSR value calculated */
            myOSR_SBR->sbr = tempOSR_SBR.sbr; /* update store the best SBR value calculated */
        }
    }
}

/**
 ****************************************************************************************
 * @brief LPUART Transmiter Send Data
 *
 * @param data
 * @param length
 ****************************************************************************************
 */
void LPUART0_Write (const uint8_t *data, size_t length)
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

/**
 ****************************************************************************************
 * @brief LPUART Receiver Read Data
 *
 * @param data
 ****************************************************************************************
 */
void LPUART0_Read (uint8_t * data)
{
    *data = (uint8_t)LPUART0->DATA;
}

/**
 ****************************************************************************************
 * @brief Init pin for LPUART0
 *
 * @param none
 ****************************************************************************************
 */
void LPUART0_InitPin (void)
{
    /* Clock Gate Control: Clock enabled */
    PCC_ClockEnable (PCC_PORTB_INDEX);

    /* Set pin mux to configure for LPUART0 */
    Port_SetPinMux (PORTB, LPUART0_RX_PIN, MUX_ALT2);
    Port_SetPinMux (PORTB, LPUART0_TX_PIN, MUX_ALT2);
}