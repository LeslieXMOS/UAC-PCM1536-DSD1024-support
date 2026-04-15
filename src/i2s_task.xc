#include <stdint.h>
#include <platform.h>
#include <xs1.h>
#include "i2s.h"
#include "xua_conf.h"

// extern "C" {
//     void setup_bclk();
//     void update_bclk_divider();
// }
#define I2S_BUF_SIZE    (16)

static uint8_t i2s_state = 0;   // 0: no restart; 1: need restart; 2: dsd mode
static uint32_t mclk_bclk_ratio = (MCLK_48/(DEFAULT_FREQ*2*32));
static int32_t i2s_out_buf[I2S_BUF_SIZE][NUM_USB_CHAN_OUT];
static uint32_t i2s_out_buf_wr_idx = 1;    // Prefill 1
static uint32_t i2s_out_buf_rd_idx = 0;

void set_i2s_freq(uint32_t mclk_freq, uint32_t samp_rate) {
    mclk_bclk_ratio = (mclk_freq / (samp_rate * 2 * 32));
    i2s_state = 1;
}

int fill_i2s_out(int32_t data[NUM_USB_CHAN_OUT]) {
    if (i2s_out_buf_wr_idx == i2s_out_buf_rd_idx) {
        return -1;
    }
    #pragma loop unroll
    for (int i = 0; i < NUM_USB_CHAN_OUT; ++i) {
        i2s_out_buf[i2s_out_buf_wr_idx][i] = data[i];
    }
    ++i2s_out_buf_wr_idx;
    i2s_out_buf_wr_idx %= I2S_BUF_SIZE;
    return 0;
}

[[distributable]]
void i2s_application(server i2s_frame_callback_if i_i2s) {
  while (1) {
    select {
      case i_i2s.init(i2s_config_t &?i2s_config, tdm_config_t &?tdm_config):
        i2s_config.mode = I2S_MODE_LEFT_JUSTIFIED;
        i2s_config.mclk_bclk_ratio = mclk_bclk_ratio;
        i2s_out_buf_wr_idx = 1;    // Prefill 1
        i2s_out_buf_rd_idx = 0;
        break;
      case i_i2s.restart_check() -> i2s_restart_t restart:
        if (i2s_state == 0) {
            restart = I2S_NO_RESTART;
        } else if (i2s_state == 1) {
            i2s_state = 0;
            restart = I2S_RESTART;
        } else {
            restart = I2S_SHUTDOWN;
        }
        break;
      case i_i2s.receive(size_t num_in, int32_t samples[num_in]):
        // Handle a received sample
        break;
      case i_i2s.send(size_t num_out, int32_t samples[num_out]):
        // Provide a sample to send
        #pragma loop unroll
        for (int i = 0; i < NUM_USB_CHAN_OUT; ++i) {
            samples[i] = i2s_out_buf[i2s_out_buf_rd_idx][i];
        }
        ++i2s_out_buf_rd_idx;
        i2s_out_buf_rd_idx %= I2S_BUF_SIZE;
        break;
    }
  }
}

int i2s_task(
    in port p_mclk,
    out port p_bclk,
    out buffered port:32 p_lrclk,
    out buffered port:32 (&?p_dout)[NUM_USB_CHAN_OUT/2],
    clock bclk
) {
    i2s_frame_callback_if i_i2s;

    par {
        i2s_frame_master(i_i2s, p_dout, NUM_USB_CHAN_OUT/2, null, 0, 32, p_bclk, p_lrclk, p_mclk, bclk);
        i2s_application(i_i2s);
    }
    return 0; 
}