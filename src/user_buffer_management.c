#include <platform.h>
#include <xs1.h>
#include <stdio.h>
#include <xscope.h>

void UserBufferManagementInit(unsigned sampFreq) {
    printf("sample rate %d\n", sampFreq);
}

void UserBufferManagement(unsigned sampsFromUsbToAudio[], unsigned sampsFromAudioToUsb[]) {
    // printf("b\n");
    xscope_int(TEST, sampsFromUsbToAudio[0]);
}