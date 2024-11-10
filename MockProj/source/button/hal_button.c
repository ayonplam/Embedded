/*******************************************************************************
* Include
******************************************************************************/
#include "hal_button.h"
#include "MKE16Z4.h"

/*******************************************************************************
* MACRO
******************************************************************************/
#define MUX_GPIO 1U  /* Alternative 1 (GPIO)*/

/*******************************************************************************
* Definitions
******************************************************************************/
/*!
 * @brief Button Enable
 *
 * This function set pin mux is GPIO and input
 *
 * @param PORTx
 * @param GPIO_Pin
 */
void HAL_BtnEnable (GPIO_Port PORTx, uint16_t GPIO_Pin)
{
    switch(PORTx)
    {
        case GPIO_PORT_A:
            PORTA->PCR[GPIO_Pin] |= PORT_PCR_MUX(MUX_GPIO);
            GPIOA->PDDR &= ~(1 << GPIO_Pin);
            break;

        case GPIO_PORT_B:
            PORTB->PCR[GPIO_Pin] |= PORT_PCR_MUX(MUX_GPIO);
            GPIOB->PDDR &= ~(1 << GPIO_Pin);
            break;

        case GPIO_PORT_C:
            PORTC->PCR[GPIO_Pin] |= PORT_PCR_MUX(MUX_GPIO);
            GPIOC->PDDR &= ~(1 << GPIO_Pin);
            break;

        case GPIO_PORT_D:
            PORTD->PCR[GPIO_Pin] |= PORT_PCR_MUX(MUX_GPIO);
            GPIOD->PDDR &= ~(1 << GPIO_Pin);
            break;

        case GPIO_PORT_E:
            PORTE->PCR[GPIO_Pin] |= PORT_PCR_MUX(MUX_GPIO);
            GPIOE->PDDR &= ~(1 << GPIO_Pin);
            break;

        default:
            break;
    }
}

/*!
 * @brief Button Pull Select
 *
 * This function set pin is pull up or pull down
 *
 * @param PORTx
 * @param GPIO_Pin
 * @param pull_mode
 */
void HAL_BtnPullSelect (GPIO_Port PORTx, uint16_t GPIO_Pin, PULL_MODE pull_mode)
{
    switch(PORTx)
    {
        case GPIO_PORT_A:
            PORTA->PCR[GPIO_Pin] |= PORT_PCR_PE(1);
            PORTA->PCR[GPIO_Pin] |= PORT_PCR_PS(pull_mode);
            break;

        case GPIO_PORT_B:
            PORTB->PCR[GPIO_Pin] |= PORT_PCR_PE(1);
            PORTB->PCR[GPIO_Pin] |= PORT_PCR_PS(pull_mode);
            break;

        case GPIO_PORT_C:
            PORTC->PCR[GPIO_Pin] |= PORT_PCR_PE(1);
            PORTC->PCR[GPIO_Pin] |= PORT_PCR_PS(pull_mode);
            break;

        case GPIO_PORT_D:
            PORTD->PCR[GPIO_Pin] |= PORT_PCR_PE(1);
            PORTD->PCR[GPIO_Pin] |= PORT_PCR_PS(pull_mode);
            break;

        case GPIO_PORT_E:
            PORTE->PCR[GPIO_Pin] |= PORT_PCR_PE(1);
            PORTE->PCR[GPIO_Pin] |= PORT_PCR_PS(pull_mode);
            break;

        default:
            break;
    }
}

/*!
 * @brief Read Button State
 *
 * This function read button state
 *
 * @param PORTx
 * @param GPIO_Pin
 */
GPIO_PinState HAL_readBtn(GPIO_Port PORTx, uint16_t GPIO_Pin)
{
    GPIO_PinState bitstatus;

    switch(PORTx)
    {
        case GPIO_PORT_A:
            bitstatus = (GPIO_PinState)(GPIOA->PDIR & (1 << GPIO_Pin));
            break;

        case GPIO_PORT_B:
            bitstatus = (GPIO_PinState)(GPIOB->PDIR & (1 << GPIO_Pin));
            break;

        case GPIO_PORT_C:
            bitstatus = (GPIO_PinState)(GPIOC->PDIR & (1 << GPIO_Pin));
            break;

        case GPIO_PORT_D:
            bitstatus = (GPIO_PinState)(GPIOD->PDIR & (1 << GPIO_Pin));
            break;

        case GPIO_PORT_E:
            bitstatus = (GPIO_PinState)(GPIOE->PDIR & (1 << GPIO_Pin));
            break;

        default:
            break;
    }

    return bitstatus;
}