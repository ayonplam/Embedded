#include "driver_led_blink.h"
#include <stdbool.h>

void SysTick_Handler(void); /* SysTick interrupt Handler. */
void SysTick_DelayTicks(uint32_t n); /* Delay Ticks */

volatile uint32_t g_sysTickCounter; /* Variable to store millisecond ticks */
volatile uint32_t mode; /* Variable to store mode LED */
volatile bool g_btnIsPressed = 0; /*  */

/* Variable to store RGB code */
RGB_codes myRGB;
/*******************************************************************************
 * Code
 ******************************************************************************/
int main(void)
{
    /* Init LED RGB */
    initLedRGB ();
    /* Init Button */
    initBtn_SW3 ();
    /* Enable interrupt for button in NVIC */
    NVIC_EnableIRQ(PORTBCD_IRQn);

    if (SysTick_Config(SystemCoreClock / 1000000U)) /* Configure SysTick to generate an interrupt every microsecond */
    {
        while (1)
        {

        }
    }

    mode = 3;
    while (1)
    {
        g_btnIsPressed = 0;
        if(mode % 3 == 0)
        {
            myRGB.red_code = 0xFF;
            myRGB.green_code = 0x00;
            myRGB.blue_code = 0x00;
            DelayLed(&myRGB);
            turnOffLed(&myRGB);

            myRGB.red_code = 0x00;
            myRGB.green_code = 0xFF;
            DelayLed(&myRGB);
            turnOffLed(&myRGB);

            myRGB.green_code = 0x00;
            myRGB.blue_code = 0xFF;
            DelayLed(&myRGB);
            turnOffLed(&myRGB);
        }
        else if (mode % 3 == 1)
        {
            myRGB.red_code = 0xFF;
            myRGB.green_code = 0xFF;
            myRGB.blue_code = 0x00;
            DelayLed(&myRGB);
            turnOffLed(&myRGB);

            myRGB.red_code = 0x00;
            myRGB.green_code = 0xFF;
            myRGB.blue_code = 0xFF;
            DelayLed(&myRGB);
            turnOffLed(&myRGB);

            myRGB.red_code = 0xFF;
            myRGB.green_code = 0x00;
            myRGB.blue_code = 0xFF;
            DelayLed(&myRGB);
            turnOffLed(&myRGB);
        }
        else
        {
            myRGB.red_code = 0x8F;
            myRGB.green_code = 0x00;
            myRGB.blue_code = 0xFF;
            DelayLed(&myRGB);
            turnOffLed(&myRGB);

            myRGB.red_code = 0xE1;
            myRGB.green_code = 0x1B;
            myRGB.blue_code = 0x8D;
            DelayLed(&myRGB);
            turnOffLed(&myRGB);

            myRGB.red_code = 0x9A;
            myRGB.green_code = 0x7B;
            myRGB.blue_code = 0x4F;
            DelayLed(&myRGB);
            turnOffLed(&myRGB);
        }
    }
}

/* SysTick interrupt Handler. */
void SysTick_Handler(void)
{
    if (g_sysTickCounter != 0u)
    {
        g_sysTickCounter--;
    }
}

/* Delay Ticks */
void SysTick_DelayTicks(uint32_t n)
{
    g_sysTickCounter = n;

    while (g_sysTickCounter != 0u)
    {
    }
}

/* PORTBCD_IRQ Handler for Button SW3 interrupt */
void PORTBCD_IRQHandler(void)
{
    NVIC_ClearPendingIRQ(PORTBCD_IRQn); /* clear bit pending */
    mode++;
    g_btnIsPressed = 1;
    PORTD->PCR[2] |= PORT_PCR_ISF_MASK; /* set interrupt state flag */
}

