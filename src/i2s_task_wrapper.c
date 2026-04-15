#include <xcore/port.h>
#include <platform.h>
#include "xua_conf.h"

static uint32_t mclk_bclk_ratio = (MCLK_48/(DEFAULT_FREQ*2*32));

// void update_bclk_divider() {
//     xclock_t bclk_cb = XS1_CLKBLK_1;
//     clock_set_divide(bclk_cb, mclk_bclk_ratio >> 1);
// }

// void setup_bclk() {
//     xclock_t bclk_cb = XS1_CLKBLK_1;
//     port_t p_mclk = PORT_MCLK_IN;

//     clock_enable(bclk_cb);
//     clock_set_source_port(bclk_cb, p_mclk);
//     update_bclk_divider();
//     clock_start(bclk_cb);
// }

// void update_i2s_freq(uint32_t mclk_freq, uint32_t samp_freq) {
//     // default 32-bit I2S
//     const uint32_t data_bits = 32;
//     mclk_bclk_ratio = (mclk_freq/(samp_freq*2*data_bits));
// }

extern int i2s_task(
    port_t p_mclk,
    port_t p_bclk,
    port_t p_lrclk,
    port_t p_dout[],
    xclock_t bclk
);

void i2s_task_wrapper() {
    // Hacks to prevent resources par usage
    port_t p_dout[NUM_USB_CHAN_OUT/2] = {PORT_I2S_DAC0};
    port_t p_mclk = PORT_MCLK_IN;
    port_t p_bclk = PORT_I2S_BCLK;
    port_t p_lrclk = PORT_I2S_LRCLK;
    xclock_t bclk = XS1_CLKBLK_3;   // Check lib_xua\lib_xua\src\core\uac_hwresources.h

    for (int i = 0; i < NUM_USB_CHAN_OUT/2; ++i) {
        port_start_buffered(p_dout[i], 32);
    }
    i2s_task(p_mclk, p_bclk, p_lrclk, p_dout, bclk);
}