#include <stdio.h>
#include <string.h>
#include <xs1.h>
#include <platform.h>
#include <xcore/parallel.h>
#include <xcore/select.h>
#include <xcore/channel.h>
#include <xcore/port.h>
#include <xcore/port_protocol.h>
#include <xcore/clock.h>
#include <xcore/triggerable.h>
#include <xcore/interrupt_wrappers.h>
#include <xcore/interrupt.h>
#include <xcore/hwtimer.h>
#include <xclib.h>
#include <xscope.h>
#include "stdint.h"
#include "sw_pll.h"
#include "xcore/clock.h"
#include "xcore/port.h"
#include "platform.h"

void mclk_98m(void)
{
    // sw_pll_fixed_clock(512*48000);
    // return;
    /**
     * Found solution: IN 24.000MHz, OUT 98.304094MHz, VCO 1179.65MHz, RD 19, FD  933, FRAC 0.889 (m =   8, n =   9), OD  3, FOD    1, ERR 0.952ppm
     * APP_PLL_CTL_REG 0x0903A412
     * APP_PLL_DIV_REG 0x80000000
     * APP_PLL_FRAC_REG 0x80000708
     */
    #define APP_PLL_CTL_REG 0x0903A412
    #define APP_PLL_DIV_REG 0x80000000
    #define APP_PLL_FRAC_REG 0x80000708
    sw_pll_app_pll_init(get_local_tile_id(), APP_PLL_CTL_REG, APP_PLL_DIV_REG, (uint16_t)APP_PLL_FRAC_REG);
}

void main_tile0(chanend_t c_tile1, unsigned tile1_id)
{
    (void) c_tile1;
    (void) tile1_id;
}

void main_tile1(chanend_t c_tile0, unsigned tile0_id)
{
    (void) c_tile0;
    (void) tile0_id;

    port_t p_mclk = PORT_MCLK_IN;
    port_t p_bclk = PORT_I2S_BCLK;
    xclock_t bclk_cb = XS1_CLKBLK_1;

    mclk_98m();

    // Setup BCLK and its clock block
    port_enable(p_mclk);
    port_enable(p_bclk);
    clock_enable(bclk_cb);

    clock_set_source_port(bclk_cb, p_mclk);
    clock_set_divide(bclk_cb, 0);
    // clock_set_source_clk_xcore(bclk_cb);
    // clock_set_divide(bclk_cb, 3);
    // clock_set_source_clk_ref(bclk_cb);
    // clock_set_divide(bclk_cb, 1);
    clock_start(bclk_cb);

    port_set_clock(p_bclk, bclk_cb);
    port_set_out_clock(p_bclk);

    while (1) {
        delay_milliseconds(1000);
    }
}