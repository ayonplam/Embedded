#ifndef HAL_BUTTON_H
#define HAL_BUTTON_H
/*******************************************************************************
* Include
******************************************************************************/
#include <stdint.h>

/*******************************************************************************
 * Definition new data type
 ******************************************************************************/
/**
  * @enum Ports List
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
  * @enum Pull Mode
  */
typedef enum { PULL_DOWN = 0U, PULL_UP } PULL_MODE;

/**
  * @enum Pin State
  */
typedef enum { GPIO_PIN_RESET = 0, GPIO_PIN_SET } GPIO_PinState;

/*******************************************************************************
* Prototype
******************************************************************************/
/*!
 * @brief Button Enable
 *
 * This function set pin mux is GPIO and input
 *
 * @param PORTx
 * @param GPIO_Pin
 */
void HAL_BtnEnable (GPIO_Port PORTx, uint16_t GPIO_Pin);

/*!
 * @brief Button Pull Select
 *
 * This function set pin is pull up or pull down
 *
 * @param PORTx
 * @param GPIO_Pin
 * @param pull_mode
 */
void HAL_BtnPullSelect (GPIO_Port PORTx, uint16_t GPIO_Pin, PULL_MODE pull_mode);

/*!
 * @brief Read Button State
 *
 * This function read button state
 *
 * @param PORTx
 * @param GPIO_Pin
 */
GPIO_PinState HAL_readBtn(GPIO_Port PORTx, uint16_t GPIO_Pin);

#endif /* HAL_BUTTON_H */

