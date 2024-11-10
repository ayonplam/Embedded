#include "driver_lpit.h"

/* Init LED RGB: red on, green off */
void initLedRGB (void)
{
    /* Enable clock */
    Port_ClockEnable (PCC_PORTB_INDEX);

    /* Set pin GPIO */
    Port_SetPinMux (PORTB, RED_LED_PIN, 1);
    Port_SetPinMux (PORTB, GREEN_LED_PIN, 1);

    /* Set pin output */
    GPIO_SetPinOutput (FGPIOB, RED_LED_PIN);
    GPIO_SetPinOutput (FGPIOB, GREEN_LED_PIN);

    /* Set pin state default */
    GPIO_SetPinState(FGPIOB, RED_LED_PIN, GPIO_PIN_SET);
    GPIO_SetPinState(FGPIOB, GREEN_LED_PIN, GPIO_PIN_RESET);
}

/* Init Clock source SIRC 8Mhz, div = 2 */
void LPIT_initClockSource (void)
{
    /* Config Divider */
    SIRC_DividerConfig (SIRC_DIV2);

    /* Config range */
    SIRC_RangeConfig (SIRC_HIGH_RANGE);

    /* Enable SIRC */
    SIRC_Enable (SIRC_ENABLE);

    /* Wait for clock is valid */
    while (0UL == (SCG->SIRCCSR & SCG_SIRCCSR_SIRCVLD_MASK))
    {
    }

    /* Config PCC_PCS */
    PCC_PCSConfig (PCC_LPIT0_INDEX, PCS_SIRC_SOURCE);
}

/* Init LPIT0 chain channel 1 & channel 0 */
void initLPIT0 (void)
{
    /* Set Operation mode */
    LPIT_SetOperation (LPIT0);

    /* Set Timer mode */
    LPIT_SetTimerMode (LPIT0, CHANNEL0, TIMER_MODE0);
    LPIT_SetTimerMode (LPIT0, CHANNEL1, TIMER_MODE0);

    /* Set chain channel */
    LPIT_SetChannelChain (LPIT0, CHANNEL1, CHAIN_ENABLE);

    /* Set timer period channel */
    LPIT_SetTimerPeriod (LPIT0, CHANNEL0, ONE_SECOND_VALUE);
    LPIT_SetTimerPeriod (LPIT0, CHANNEL1, CHAINED_COUNT);

    /* Enable interrupt channel 1*/
    LPIT_DisableInterrupts(LPIT0, CHANNEL0);
    LPIT_EnableInterrupts(LPIT0, CHANNEL1);

    /* Enable NVIC interrupt */
    NVIC_EnableIRQ(LPIT0_IRQn);

    /* Start timer */
    LPIT_StartTimer (LPIT0, CHANNEL0);
    LPIT_StartTimer (LPIT0, CHANNEL1);
}

void LPIT0_IRQHandler(void)
{
    /* CLer Interrupt Flag channel 1 */
    LPIT_ClearInterruptFlag (LPIT0, CHANNEL1);

    /* Toggle red led and grren led */
    GPIO_TogglePinOutput (FGPIOB, RED_LED_PIN);
    GPIO_TogglePinOutput (FGPIOB, GREEN_LED_PIN);
}

