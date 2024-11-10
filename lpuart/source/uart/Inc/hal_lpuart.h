/*******************************************************************************
* Definitions
******************************************************************************/
#ifndef HAL_LPUART_H
#define HAL_LPUART_H

/*******************************************************************************
* Includes
******************************************************************************/
#include "MKE16Z4.h"

/*******************************************************************************
* MACRO
******************************************************************************/
/**
  * Pin Mux Control
  */
#define MUX_GPIO 1U  /* Alternative 1 (GPIO)*/
#define MUX_ALT2 2U  /* alternative 2 */

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
 * @param GPIO_Pin Pin number.
 * @param mode Mode Mux control.
 */
void Port_SetPinMux (PORT_Type * PORTx, uint16_t GPIO_Pin, uint8_t mode);

/*!
 * @brief Enable RX and TX.
 * @param LPUARTx LPUART peripheral base address
 */
void LPUART_EnableRXTX (LPUART_Type * LPUARTx);

/*!
 * @brief Disable RX and TX.
 * @param LPUARTx LPUART peripheral base address
 */
void LPUART_DisableRXTX (LPUART_Type * LPUARTx);

/*!
 * @brief Set Baudrate.
 * @param LPUARTx LPUART peripheral base address
 * @param osr Value of OSR will be set
 * @param sbr Value of SBR will be set
 */
void LPUART_SetBaudrate (LPUART_Type * LPUARTx, uint16_t osr, uint8_t sbr);

/*!
 * @brief Set Parity Bit.
 * @param LPUARTx LPUART peripheral base address
 * @param parity_enable
 * @param parity_type
 */
void LPUART_SetParity (LPUART_Type * LPUARTx, uint8_t parity_enable, uint8_t parity_type);

/*!
 * @brief Transmit Data Inversion.
 * @param LPUARTx LPUART peripheral base address
 * @param config Enable or Disable
 */
void LPUART_SetInverseTX (LPUART_Type * LPUARTx, uint8_t config);

/*!
 * @brief Set First Bit
 * @param LPUARTx LPUART peripheral base address
 * @param config LSB or MSB
 */
void LPUART_SetFirstBit (LPUART_Type * LPUARTx, uint8_t config);

/*!
 * @brief Set Stop Bit
 * @param LPUARTx LPUART peripheral base address
 * @param config 1 or 2 stop bit
 */
void LPUART_SetStopBit (LPUART_Type * LPUARTx, uint8_t config);

/*!
 * @brief Set 8 Bit Data mode
 * @param LPUARTx LPUART peripheral base address
 */
void LPUART_Set8BitMode (LPUART_Type * LPUARTx);

/*!
 * @brief Enable Receiver Interrupt
 * @param LPUARTx LPUART peripheral base address
 */
void LPUART_EnableReceiverInterrupt (LPUART_Type * LPUARTx);

#endif /* HAL_LPUART_H */

