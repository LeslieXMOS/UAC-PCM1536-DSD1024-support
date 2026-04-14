# cmake
cmake_minimum_required(VERSION 3.21)
include($ENV{XMOS_CMAKE_PATH}/xcommon.cmake)
project(UAC_PCM1536_DSD1024)

# root
set(XMOS_SANDBOX_DIR ${CMAKE_SOURCE_DIR}/sandbox)

# target
set(APP_HW_TARGET boards/XK_VOICE_L71.xn)
set(APP_XSCOPE_SRCS src/basic.xscope)

# Dependencies
set(APP_DEPENDENT_MODULES
    "lib_xua(5.4.0)"
    "lib_i2s(develop)"
)

set(APP_INCLUDES src)

set(APP_COMPILER_FLAGS
    -O3 -mno-dual-issue -g -report -Wall -mcmodel=large -Wno-xcore-fptrgroup
    -lquadflash
    # Dedicated I2S Config
    -DI2S_MASTER_CHANS_ADC=0
    -DI2S_MASTER_CHANS_DAC=2
)

XMOS_REGISTER_APP()