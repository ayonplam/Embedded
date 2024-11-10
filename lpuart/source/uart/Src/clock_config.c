#include "clock_config.h"

void PCC_ClockEnable (uint32_t offset)
{
    PCC->CLKCFG[offset] |= PCC_CLKCFG_CGC(1);
}

void PCC_PCSConfig (uint32_t index, uint8_t config)
{
    /* Disable Gate Clock before config PCS */
    PCC->CLKCFG[index] |= PCC_CLKCFG_CGC(0);

    PCC->CLKCFG[index] |= PCC_CLKCFG_PCS(config);

    PCC->CLKCFG[index] |= PCC_CLKCFG_CGC(1);
}

void FIRC_DividerConfig (uint8_t config)
{
    SCG->FIRCDIV |= SCG_FIRCDIV_FIRCDIV2(config);
}

void SIRC_DividerConfig (uint8_t config)
{
    SCG->SIRCDIV = SCG_SIRCDIV_SIRCDIV2(config);
}

void SIRC_RangeConfig (uint8_t config)
{
    SCG->SIRCCFG = SCG_SIRCCFG_RANGE(config);
}

void SIRC_Enable (uint8_t config)
{
    SCG->SIRCCSR = SCG_SIRCCSR_SIRCEN_MASK | config;
}