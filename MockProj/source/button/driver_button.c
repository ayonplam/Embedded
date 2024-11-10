/*******************************************************************************
* Includes
******************************************************************************/
#include "driver_button.h"
#include "clock_config.h"
#include "hal_button.h"

/*******************************************************************************
* MACRO
******************************************************************************/
#define SW3_PIN   2     /* BUTTON SW3 PIN */

/*******************************************************************************
* Definitions
******************************************************************************/
/*!
 * @brief Initialize Button
 *
 * This function initialize button
 */
void initBtn_SW3 (void)
{
    /* Enable clock port D */
    PCC_ClockEnable (PORTD_INDEX);
    /* Set pin pull up */
    HAL_BtnPullSelect (GPIO_PORT_D, SW3_PIN, PULL_UP);
    /* Enable button */
    HAL_BtnEnable (GPIO_PORT_D, SW3_PIN);
}

/*!
 * @brief Read Button
 *
 * This function read button
 */
Btn_state readBtn_SW3 (void)
{
    return (Btn_state)(HAL_readBtn (GPIO_PORT_D, SW3_PIN));
}