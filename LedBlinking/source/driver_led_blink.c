#include "driver_led_blink.h"

/* Init LED RGB */
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
}

/* Init Button SW3 on board */
void initBtn_SW3 (void)
{
    /* Enable clock */
    Port_ClockEnable (PCC_PORTD_INDEX);

    /* Set pin GPIO */
    Port_SetPinMux (PORTD, SW3_PIN, 1);

    /* Set pin pull up */
    Port_SetPinPull_Up(PORTD, SW3_PIN);

    /* Set Pin Interrupt Config */
    PORT_SetPinInterruptConfig(PORTD, SW3_PIN, PORT_InterruptFallingEdge);

    /* Set pin input */
    GPIO_SetPinInput(FGPIOD, SW3_PIN);
}

/* Show LED in 1ms */
void ShowLed(RGB_codes * RGBcodes)
{
    g_sysTickCounter = T;

    while (g_sysTickCounter != 0u && !g_btnIsPressed)
    {
        if (RGBcodes->red_code == 0)
        {
            GPIO_SetPin(FGPIOB, PIN_RED, GPIO_PIN_SET); /* turn off red */
        }
        else if (g_sysTickCounter < RGBcodes->red_code * 4)
        {
            GPIO_SetPin(FGPIOB, PIN_RED, GPIO_PIN_RESET); /* turn on red */
        }
        else
        {
            GPIO_SetPin(FGPIOB, PIN_RED, GPIO_PIN_SET); /* turn off red */
        }

        if (RGBcodes->green_code == 0)
        {
            GPIO_SetPin(FGPIOB, PIN_GREEN, GPIO_PIN_SET); /* turn off green */
        }
        else if (g_sysTickCounter < RGBcodes->green_code * 4)
        {
            GPIO_SetPin(FGPIOB, PIN_GREEN, GPIO_PIN_RESET); /* turn on green */
        }
        else
        {
            GPIO_SetPin(FGPIOB, PIN_GREEN, GPIO_PIN_SET); /* turn off green */
        }

        if (RGBcodes->blue_code == 0)
        {
            GPIO_SetPin(FGPIOD, PIN_BLUE, GPIO_PIN_SET); /* turn off blue */
        }
        else if (g_sysTickCounter < RGBcodes->blue_code * 4)
        {
            GPIO_SetPin(FGPIOD, PIN_BLUE, GPIO_PIN_RESET); /* turn on blue */
        }
        else
        {
            GPIO_SetPin(FGPIOD, PIN_BLUE, GPIO_PIN_SET); /* turn off blue */
        }
    }
}

/* Turn off LED RGB*/
void turnOffLed(RGB_codes * RGBcodes)
{
    uint16_t i = 0;
    for (i = 0; i < 1000; i++)
    {
        if (RGBcodes->red_code)
        {
            RGBcodes->red_code--;
        }

        if (RGBcodes->green_code)
        {
            RGBcodes->green_code--;
        }

        if (RGBcodes->blue_code)
        {
            RGBcodes->blue_code--;
        }

        ShowLed(RGBcodes);
        ShowLed(RGBcodes);
        ShowLed(RGBcodes);
    }
}

/* Delay led RGB in 1s */
void DelayLed(RGB_codes * RGBcodes)
{
    uint16_t i = 0;
    for (i = 0; i < 1000; i++)
    {
        ShowLed(RGBcodes); /* Show LED in 1ms */
    }
}