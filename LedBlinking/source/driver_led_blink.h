#ifndef DRIVER_LED_BLINK_H
#define DRIVER_LED_BLINK_H

#include "hal_led_blink.h"
#include <stdbool.h>

#define PIN_RED   5     /* RED LED PIN */
#define PIN_GREEN 4     /* GREEN LED PIN */
#define PIN_BLUE  1     /* BLUE LED PIN */
#define SW3_PIN   2     /* BUTTON SW3 PIN */
#define T         1020U /* frequency about 1kHz -> T = 1020 us */

extern volatile uint32_t g_sysTickCounter;
extern volatile bool g_btnIsPressed;
/* LED RGB follow 8bit */
typedef struct RGB_codes
{
    uint8_t red_code;
    uint8_t green_code;
    uint8_t blue_code;
} RGB_codes;

void initLedRGB (void);

void initBtn_SW3 (void);

void ShowLed(RGB_codes * RGBcodes);

void turnOffLed(RGB_codes * RGBcodes);

void DelayLed(RGB_codes * RGBcodes);

GPIO_PinState readBtn (void);

#endif /* DRIVER_LED_BLINK_H */