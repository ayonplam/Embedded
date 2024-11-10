/*******************************************************************************
* Definitions
******************************************************************************/
#ifndef DRIVER_LPUART_H
#define DRIVER_LPUART_H

/*******************************************************************************
* Includes
******************************************************************************/
#include <stdint.h>
#include <stddef.h>
#include "common.h"

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

/**
  * @
  */
typedef void (*CallBack_ptr) (circ_bbuf_t *);
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
void LPUART0_Init (void);

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
 ****************************************************************************************
 */
void Caculate_OSR_SBR (uint32_t clk_src, uint32_t baudrate);

/**
 ****************************************************************************************
 * @brief Register call back ring_buff_push in queue.c
 *
 * @param
 ****************************************************************************************
 */
void RegisterCallback (CallBack_ptr ptr1);

/**
 ****************************************************************************************
 * @brief Register call back circ_bbuf_t g_myRingBuffer in manager.c
 *
 * @param
 ****************************************************************************************
 */
void RegisterCallVariable (circ_bbuf_t * ptr1);

/**
 ****************************************************************************************
 * @brief Enable interrupt LPUART in NVIC
 *
 * @param
 ****************************************************************************************
 */
void Enable_LPUART0irq (void);

/**
 ****************************************************************************************
 * @brief Disable interrupt LPUART in NVIC
 *
 * @param
 ****************************************************************************************
 */
void Disable_LPUART0irq (void);

#endif /* DRIVER_LPUART_H */