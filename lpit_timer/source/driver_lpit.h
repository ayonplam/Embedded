#ifndef DRIVER_LPIT_H
#define DRIVER_LPIT_H

#include "hal_lpit.h"
#include "clock_config.h"

#define ONE_SECOND_VALUE 4000000U /* value for period channel 0: 1ms */
#define CHAINED_COUNT    10U      /* value for period channel 1: 10 */

void initLedRGB (void);

void LPIT_initClockSource (void);

void initLPIT0 (void);

void LPIT0_IRQHandler(void);

#endif /* DRIVER_LPIT_H */