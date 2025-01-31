/*******************************************************************************
* Definitions
******************************************************************************/
#ifndef CLOCK_CONFIG_H
#define CLOCK_CONFIG_H

/*******************************************************************************
* Includes
******************************************************************************/
#include "MKE16Z4.h"

/*******************************************************************************
* MACRO
******************************************************************************/
/**
  * Peripheral Clock Source Select
  */
#define PCS_FIRC_SOURCE 3U
#define PCS_SIRC_SOURCE 2U

/**
  * Clock divider 2 for the Fast IRC
  */
#define FIRC_DIV2_0  0   /* Output disabled */
#define FIRC_DIV2_1  1U  /* Divide by 1 */
#define FIRC_DIV2_2  2U  /* Divide by 2 */
#define FIRC_DIV2_4  3U  /* Divide by 4 */
#define FIRC_DIV2_8  4U  /* Divide by 8 */
#define FIRC_DIV2_16 5U  /* Divide by 16 */
#define FIRC_DIV2_32 6U  /* Divide by 32 */
#define FIRC_DIV2_64 7U  /* Divide by 64 */

/**
  * SIRC config
  */
#define SIRC_HIGH_RANGE 1U  /* 8MHz */
#define SIRC_LOW_RANGE  0   /* 4MHz */
#define SIRC_ENABLE     1U
#define SIRC_DISABLE    0

/*!
 * @brief Port Clock Enable.
 * @param PORTx PORT base offset.
 */
void PCC_ClockEnable (uint32_t offset);

/*!
 * @brief Set FIRC's Devider 2.
 * @param config Value of devider.
 */
void FIRC_DividerConfig (uint8_t config);

/*!
 * @brief Set SIRC's Devider 2.
 * @param config Value of devider.
 */
void SIRC_DividerConfig (uint8_t config);

/*!
 * @brief Peripheral Clock Source Select
 * @param index PCC peripheral base pointers
 * @param config Peripheral Clock Source Select
 */
void PCC_PCSConfig (uint32_t index, uint8_t config);

/*!
 * @brief Config SIRC's range
 * @param config High: 8MHz or Low: 4MHz
 */
void SIRC_RangeConfig (uint8_t config);

/*!
 * @brief Enable or Disable SIRC
 * @param config Enable or Disable
 */
void SIRC_Enable (uint8_t config);

#endif /* CLOCK_CONFIG_H */