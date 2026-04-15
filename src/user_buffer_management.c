#include <platform.h>
#include <xs1.h>
#include <stdio.h>
#include <xscope.h>
#include <stdint.h>
#include <xua.h>

extern void set_i2s_freq(uint32_t mclk_freq, uint32_t samp_rate);
extern int fill_i2s_out(int32_t data[]);

static int init_done = 0;

void UserBufferManagementInit(unsigned sampFreq) {
    printf("sample rate %d\n", sampFreq);
    set_i2s_freq(MCLK_48, sampFreq);
    init_done = 1;
}

void UserBufferManagement(unsigned sampsFromUsbToAudio[], unsigned sampsFromAudioToUsb[]) {
    // printf("b\n");
    // xscope_int(TEST, sampsFromUsbToAudio[0]);
    // if (init_done == 0)
        // delay_ticks(100);
    while (fill_i2s_out(sampsFromUsbToAudio) != 0) {
        delay_ticks(1);
    }
}