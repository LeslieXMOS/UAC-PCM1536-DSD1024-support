// Copyright 2022-2025 XMOS LIMITED.
// This Software is subject to the terms of the XMOS Public Licence: Version 1.
#include "xua.h"
#include <string.h>
#include <stdio.h>

/* Configures the external audio hardware at startup */
void AudioHwInit()
{
    printf("AudioHwInit called\n");
}

/* Configures the external audio hardware for the required sample frequency
 *
 * samFreq: Sample frequency in Hz
 * mClk: Master clock frequency in Hz
 * dsdMode: DSD mode flag (0 for PCM, non-zero for DSD)
 * sampRes_DAC: Sample resolution for DAC in bits
 * sampRes_ADC: Sample resolution for ADC in bits
 */
void AudioHwConfig(unsigned samFreq, unsigned mClk, unsigned dsdMode, unsigned sampRes_DAC, unsigned sampRes_ADC)
{
    printf("AudioHwConfig called with samFreq: %d, mClk: %d, dsdMode: %d, sampRes_DAC: %d, sampRes_ADC: %d\n",
           samFreq, mClk, dsdMode, sampRes_DAC, sampRes_ADC);
}