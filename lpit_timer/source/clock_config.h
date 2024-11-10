#ifndef CLOCK_CONFIG_H
#define CLOCK_CONFIG_H

#include "MKE16Z4.h"

#define PCS_FIRC_SOURCE 0b011
#define PCS_SIRC_SOURCE 0b010
#define SIRC_DIV2 0b010
#define SIRC_HIGH_RANGE 0x1U
#define SIRC_ENABLE 0x1U
#define SIRC_DISABLE 0x0U

void Port_ClockEnable (uint32_t offset);

void FIRC_DividerConfig (uint8_t config);

void PCC_PCSConfig (uint32_t index, uint8_t config);

void SIRC_DividerConfig (uint8_t config);

void SIRC_RangeConfig (uint8_t config);

void SIRC_Enable (uint8_t config);

#endif /* CLOCK_CONFIG_H */