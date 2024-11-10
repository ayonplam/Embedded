#ifndef DRIVER_BUTTON_H
#define DRIVER_BUTTON_H

/*******************************************************************************
* Definition new Data Type
******************************************************************************/
typedef enum { isPressed = 0, notPressed } Btn_state ;

/*******************************************************************************
* Prototype
******************************************************************************/
/*!
 * @brief Initialize Button
 *
 * This function initialize button
 */
void initBtn_SW3 (void);

/*!
 * @brief Read Button
 *
 * This function read button
 */
Btn_state readBtn_SW3 (void);

#endif /* DRIVER_BUTTON_H */