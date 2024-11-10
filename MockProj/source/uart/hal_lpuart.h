#ifndef HAL_LPUART_H
#define HAL_LPUART_H

/*******************************************************************************
* Includes
******************************************************************************/
#include <stdint.h>
#include <stddef.h>
/*******************************************************************************
* MACRO
******************************************************************************/
/**
  * @enum Ports list
  */
typedef enum
{
    GPIO_PORT_A = 0u,
    GPIO_PORT_B,
    GPIO_PORT_C,
    GPIO_PORT_D,
    GPIO_PORT_E,
} GPIO_Port;

/**
  * @enum LPUART Type
  */
typedef enum
{
    LPUART_0 = 0u,
    LPUART_1,
    LPUART_2,
} LPUART_number;

/**
  * Parity Enable
  */
#define PARITY_DISABLE 0   /* No hardware parity generation or checking */
#define PARITY_ENABLE  1U  /* Parity enabled */

/**
  * Parity Type
  */
#define EVEN_PARITY    0   /* Even parity */
#define ODD_PARITY     1U  /* Odd parity */

/**
  * Transmit Data Inversion
  */
#define INV_DIS 0   /* Transmit data not inverted. */
#define INV_EN  1U  /* Transmit data inverted. */

/**
  * First Bit
  */
#define LSB 0   /* LSB (bit0) is the first bit that is transmitted following the start bit */
#define MSB 1U  /* MSB is the first bit that is transmitted following the start bit */

/**
  * Stop Bit Number Select
  */
#define ONE_STOP_BIT 0   /* One Stop Bit */
#define TWO_STOP_BIT 1U  /* Two Stop Bit */

/*******************************************************************************
* Prototypes
******************************************************************************/
/*!
 * @brief Set Pin Mux.
 * @param PORTx PORT base address.
 * @param LPUART_Pin Pin number.
 */
void HAL_SetPinUART (GPIO_Port PORTx, uint16_t LPUART_Pin);

/*!
 * @brief Enable RX and TX.
 * @param LPUARTx LPUART Type
 */
void LPUART_EnableRXTX (LPUART_number LPUARTx);

/*!
 * @brief Disable RX and TX.
 * @param LPUARTx LPUART Type
 */
void LPUART_DisableRXTX (LPUART_number LPUARTx);

/*!
 * @brief Set Baudrate.
 * @param LPUARTx LPUART Type
 * @param osr Value of OSR will be set
 * @param sbr Value of SBR will be set
 */
void LPUART_SetBaudrate (LPUART_number LPUARTx, uint16_t osr, uint8_t sbr);

/*!
 * @brief Set Parity Bit.
 * @param LPUARTx LPUART Type
 * @param parity_enable
 * @param parity_type
 */
void LPUART_SetParity (LPUART_number LPUARTx, uint8_t parity_enable, uint8_t parity_type);

/*!
 * @brief Transmit Data Inversion.
 * @param LPUARTx LPUART Type
 * @param config Enable or Disable
 */
void LPUART_SetInverseTX (LPUART_number LPUARTx, uint8_t config);

/*!
 * @brief Set First Bit
 * @param LPUARTx LPUART Type
 * @param config LSB or MSB
 */
void LPUART_SetFirstBit (LPUART_number LPUARTx, uint8_t config);

/*!
 * @brief Set Stop Bit
 * @param LPUARTx LPUART Type
 * @param config 1 or 2 stop bit
 */
void LPUART_SetStopBit (LPUART_number LPUARTx, uint8_t config);

/*!
 * @brief Set 8 Bit Data mode
 * @param LPUARTx LPUART Type
 */
void LPUART_Set8BitMode (LPUART_number LPUARTx);

/*!
 * @brief Enable Receiver Interrupt
 * @param LPUARTx LPUART Type
 */
void LPUART_EnableReceiverInterrupt (LPUART_number LPUARTx);

/*!
 * @brief Transfer Data
 * @param LPUARTx LPUART Type
 * @param data pointer data
 * @param length size of data
 */
void LPUART_PushData (LPUART_number LPUARTx, const uint8_t *data, size_t length);

/*!
 * @brief Receive Data
 * @param LPUARTx LPUART Type
 * @param data pointer data
 */
void LPUART_GetData (LPUART_number LPUARTx, uint8_t *data);

/*!
 * @brief Enable LLPUART in NVIC
 * @param LPUARTx LPUART Type
 * @param data pointer data
 * @param length size of data
 */
void LPUART_enable_inNVIC (LPUART_number LPUARTx);

/*!
 * @brief Disable LPUART in NVIC
 * @param LPUARTx LPUART Type
 * @param data pointer data
 * @param length size of data
 */
void LPUART_disable_inNVIC (LPUART_number LPUARTx);

#endif /* HAL_LPUART_H */

