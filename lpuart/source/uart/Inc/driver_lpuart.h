/*******************************************************************************
* Definitions
******************************************************************************/
#ifndef DRIVER_LPUART_H
#define DRIVER_LPUART_H

/*******************************************************************************
* Includes
******************************************************************************/
#include "hal_lpuart.h"
#include "clock_config.h"
#include <stddef.h>

/*******************************************************************************
* MACRO
******************************************************************************/
/**
  * LPUART0 Pin
  */
#define LPUART0_RX_PIN 0
#define LPUART0_TX_PIN 1U

/**
  * CLOCK SOURCE (HZ)
  */
#define CLOCK_HZ  24000000U

/**
  * LPUART0 BAUDRATE
  */
#define BAUD_RATE 115200U

/*******************************************************************************
* Definitions new Data Type
******************************************************************************/
/**
  * @struct OSR_SBR
  */
typedef struct osr_sbr
{
    uint16_t osr;  /* Variable store value of osr */
    uint8_t sbr;   /* Variable store value of sbr */
} osr_sbr;

/*******************************************************************************
* Prototypes
******************************************************************************/
/**
 ****************************************************************************************
 * @brief Config Clock Source
 *
 * This function set clock for module LPUART0
 *
 * @param none
 ****************************************************************************************
 */
void LPUART0_ConfigClockSource (void);

/**
 ****************************************************************************************
 * @brief Initialize LPUART0
 *
 * This function Initialize LPUART0
 *
 * @param myOSR_SBR pointer to a object osr_sbr
 ****************************************************************************************
 */
void LPUART0_Init (osr_sbr * myOSR_SBR);

/**
 ****************************************************************************************
 * @brief LPUART Transmiter Send Data
 *
 * @param data
 * @param length
 ****************************************************************************************
 */
void LPUART0_Write(const uint8_t *data, size_t length);

/**
 ****************************************************************************************
 * @brief LPUART Receiver Read Data
 *
 * @param data
 ****************************************************************************************
 */
void LPUART0_Read (uint8_t * data);

/**
 ****************************************************************************************
 * @brief Caculate value of OSR and SBR
 *
 * @param clk_src Module LPUART clock frequency
 * @param baudrate Value of baudrate want to set
 * @param myOSR_SBR pointer to a object osr_sbr
 ****************************************************************************************
 */
void Caculate_OSR_SBR (uint32_t clk_src, uint32_t baudrate, osr_sbr * myOSR_SBR);

#endif /* DRIVER_LPUART_H */