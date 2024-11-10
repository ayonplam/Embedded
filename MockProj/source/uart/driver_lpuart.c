/*******************************************************************************
* Includes
******************************************************************************/
#include "driver_lpuart.h"
#include "clock_config.h"
#include "hal_lpuart.h"

/*******************************************************************************
* MACRO
******************************************************************************/
/**
  * LPUART0 Pin
  */
#define LPUART0_RX_PIN 0
#define LPUART0_TX_PIN 1U

/*******************************************************************************
* Variables
******************************************************************************/
static circ_bbuf_t * g_buffer_ptr;

static CallBack_ptr g_callback_ptr;

static osr_sbr myOSR_SBR; /* Variable to store value of OSR and SBR */

/*******************************************************************************
* Definition
******************************************************************************/
void LPUART0_InitPin (void);

/**
 ****************************************************************************************
 * @brief Config Clock Source
 *
 * This function set clock for module LPUART0 24MHz
 *
 * @param none
 ****************************************************************************************
 */
void LPUART0_ConfigClockSource (void)
{
    /* Config FIRC Divider: Divide by 2 */
    FIRC_DividerConfig (FIRC_DIV2_2);

    /* Config PCC_PCS: use FIRC 48MHz */
    PCC_PCSConfig (LPUART0_INDEX, PCS_FIRC_SOURCE);
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
void LPUART0_Init (void)
{
    /* Init pin UART */
    LPUART0_InitPin ();

    /* Enable clock module LPUART0 */
    PCC_ClockEnable (LPUART0_INDEX);

    /* Disable RX TX before config */
    LPUART_DisableRXTX (LPUART_0);

    /* Set OSR, SBR */
    LPUART_SetBaudrate (LPUART_0, myOSR_SBR.osr, myOSR_SBR.sbr);

    /* Set parity bit disable */
    LPUART_SetParity (LPUART_0, PARITY_DISABLE, EVEN_PARITY);

    /* Set first bit is LSB */
    LPUART_SetFirstBit (LPUART_0, LSB);

    /* Set 2 stop bit */
    LPUART_SetStopBit (LPUART_0, TWO_STOP_BIT);

    /* TX not inverse */
    LPUART_SetInverseTX (LPUART_0, INV_DIS);

    /* 8 bit mode */
    LPUART_Set8BitMode (LPUART_0);

    /* Enable receiver interrupt*/
    LPUART_EnableReceiverInterrupt (LPUART_0);

    /* Enable interrupt in NVIC */
    LPUART_enable_inNVIC(LPUART_0);

    /* Enable RX TX after config */
    LPUART_EnableRXTX(LPUART_0);
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
void Caculate_OSR_SBR (uint32_t clk_src, uint32_t baudrate)
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
            myOSR_SBR.osr = tempOSR_SBR.osr; /* update and store the best OSR value calculated */
            myOSR_SBR.sbr = tempOSR_SBR.sbr; /* update store the best SBR value calculated */
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
    LPUART_PushData (LPUART_0, data, length);
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
    LPUART_GetData (LPUART_0, data);
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
    PCC_ClockEnable (PORTB_INDEX);

    /* Set pin mux to configure for LPUART0 */
    HAL_SetPinUART (GPIO_PORT_B, LPUART0_RX_PIN);
    HAL_SetPinUART (GPIO_PORT_B, LPUART0_TX_PIN);
}

/**
 ****************************************************************************************
 * @brief Register call back ring_buff_push in queue.c
 *
 * @param
 ****************************************************************************************
 */
void RegisterCallback (CallBack_ptr ptr1)
{
    g_callback_ptr = ptr1;
}

/**
 ****************************************************************************************
 * @brief Register call back circ_bbuf_t g_myRingBuffer in manager.c
 *
 * @param
 ****************************************************************************************
 */
void RegisterCallVariable (circ_bbuf_t * ptr1)
{
    g_buffer_ptr = ptr1;
}

/**
 ****************************************************************************************
 * @brief Enable LPUART0 interrupt in NVIC
 *
 * @param
 ****************************************************************************************
 */
void Enable_LPUART0irq (void)
{
    LPUART_enable_inNVIC(LPUART_0);
}

/**
 ****************************************************************************************
 * @brief Disable LPUART0 interrupt in NVIC
 *
 * @param
 ****************************************************************************************
 */
void Disable_LPUART0irq (void)
{
    LPUART_disable_inNVIC(LPUART_0);
}

/* Interrupt when  Receive data buffer full */
void LPUART0_IRQHandler (void)
{
    if (0U == g_buffer_ptr->isFull) /* Queue not full */
        g_callback_ptr(g_buffer_ptr); /* Push to queue */
}