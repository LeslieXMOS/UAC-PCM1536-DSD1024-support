// Copyright 2025-2026 XMOS LIMITED.
// This Software is subject to the terms of the XMOS Public Licence: Version 1.

#include "stdint.h"
#include "sw_pll.h"
#include "xcore/clock.h"
#include "xcore/port.h"
#include "platform.h"

void mclk_98m_debug(void)
{
    // sw_pll_fixed_clock(512*48000);
    // return;
    // python .\sandbox\lib_sw_pll\python\sw_pll\pll_calc.py -i 24 -t 90.3168 -a -e 1 -m 10
    /**
     * Found solution: IN 24.000MHz, OUT 98.304094MHz, VCO 1179.65MHz, RD 19, FD  933, FRAC 0.889 (m =   8, n =   9), OD  3, FOD    1, ERR 0.952ppm
     * APP_PLL_CTL_REG 0x0903A412
     * APP_PLL_DIV_REG 0x80000000
     * APP_PLL_FRAC_REG 0x80000708
     */
    // #define APP_PLL_CTL_REG 0x0903A412
    // #define APP_PLL_DIV_REG 0x80000000
    // #define APP_PLL_FRAC_REG 0x80000708
    // sw_pll_app_pll_init(get_local_tile_id(), APP_PLL_CTL_REG, APP_PLL_DIV_REG, (uint16_t)APP_PLL_FRAC_REG);

    /**
     * Found solution: IN 24.000MHz, OUT 90.316770MHz, VCO  722.53MHz, RD 23, FD  692, FRAC 0.429 (m =   3, n =   7), OD  2, FOD    1, ERR -0.33ppm
     * APP_PLL_CTL_REG 0x0882B316
     * APP_PLL_DIV_REG 0x80000000
     * APP_PLL_FRAC_REG 0x80000206
     */
    #define APP_PLL_CTL_REG 0x0882B316
    #define APP_PLL_DIV_REG 0x80000000
    #define APP_PLL_FRAC_REG 0x80000206
    sw_pll_app_pll_init(get_local_tile_id(), APP_PLL_CTL_REG, APP_PLL_DIV_REG, (uint16_t)APP_PLL_FRAC_REG);
}