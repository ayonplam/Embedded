#ifndef DRIVER_LED_BLINK_H
#define DRIVER_LED_BLINK_H

#include "hal_led_blink.h"

#define PIN_RED 5
#define PIN_GREEN 4
#define PIN_BLUE 1
#define SW3_PIN 2

void initLedRGB (void);

void initBtn_SW3 (void);

void toggleLedRGB (void);

GPIO_PinState readBtn (void);

#endif /* DRIVER_LED_BLINK_H */