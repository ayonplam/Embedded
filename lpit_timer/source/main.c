#include "driver_lpit.h"

/*******************************************************************************
 * Code
 ******************************************************************************/
int main(void)
{
    initLedRGB ();

    LPIT_initClockSource ();

    initLPIT0 ();

    while (1)
    {
    }
}

