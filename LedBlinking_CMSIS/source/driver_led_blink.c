#include "driver_led_blink.h"

void initLedRGB (void)
{
    /* Enable clock */
    Port_ClockEnable (PCC_PORTB_INDEX);
    Port_ClockEnable (PCC_PORTD_INDEX);

    /* Set pin GPIO */
    Port_SetPinMux (PORTB, PIN_RED, 1);
    Port_SetPinMux (PORTB, PIN_GREEN, 1);
    Port_SetPinMux (PORTD, PIN_BLUE, 1);

    /* Set pin output */
    GPIO_SetPinOutput (FGPIOB, PIN_RED);
    GPIO_SetPinOutput (FGPIOB, PIN_GREEN);
    GPIO_SetPinOutput (FGPIOD, PIN_BLUE);

    /* Set pin value */
    GPIO_SetPinDefault (FGPIOB, PIN_RED, GPIO_PIN_SET);
    GPIO_SetPinDefault (FGPIOB, PIN_GREEN, GPIO_PIN_SET);
    GPIO_SetPinDefault (FGPIOD, PIN_BLUE, GPIO_PIN_RESET);

}

void initBtn_SW3 (void)
{
    /* Enable clock */
    Port_ClockEnable (PCC_PORTD_INDEX);

    /* Set pin GPIO */
    Port_SetPinMux (PORTD, SW3_PIN, 1);

    /* Set pin pull up */
    Port_SetPinPull_Up(PORTD, SW3_PIN);

    /* Set pin input */
    GPIO_SetPinInput(FGPIOD, SW3_PIN);
}

void toggleLedRGB (void)
{
    GPIO_TogglePinOutput(FGPIOD, PIN_BLUE);
    GPIO_TogglePinOutput(FGPIOB, PIN_GREEN);
}

GPIO_PinState readBtn (void)
{
    return readPin(GPIOD, SW3_PIN);
}