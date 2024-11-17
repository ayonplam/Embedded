#include "driver_led_blink.h"

void SysTick_Handler(void); /* SysTick interrupt Handler. */
void SysTick_DelayTicks(uint32_t n); /* Delay Ticks */

volatile uint32_t g_sysTickCounter; /* Variable to store millisecond ticks */

/*******************************************************************************
 * Code
 ******************************************************************************/

int main(void)
{
    initLedRGB ();

    initBtn_SW3 ();

    if (SysTick_Config(SystemCoreClock / 1000U)) /* Configure SysTick to generate an interrupt every millisecond */
    {
        while (1)
        {

        }
    }

    while (1)
    {
        if (readPin(GPIOD, 2) == 0)
        {
            SysTick_DelayTicks(150U);
            if (readBtn() == 0)
            {
                /* Toggle 2 LEDs */
                toggleLedRGB();
            }
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
