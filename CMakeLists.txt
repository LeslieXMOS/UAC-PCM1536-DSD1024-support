# cmake
cmake_minimum_required(VERSION 3.21)
include($ENV{XMOS_CMAKE_PATH}/xcommon.cmake)
project(template)

# root
set(XMOS_SANDBOX_DIR ${CMAKE_SOURCE_DIR}/sandbox)

# target
set(APP_HW_TARGET boards/XK_VOICE_L71.xn)
set(APP_XSCOPE_SRCS src/basic.xscope)

# Dependencies
set(APP_DEPENDENT_MODULES
)

set(APP_COMPILER_FLAGS
    -O3 -mno-dual-issue -g -report -Wall -mcmodel=large -Wno-xcore-fptrgroup
    -lquadflash
)

XMOS_REGISTER_APP()

# ai library
# include(${CMAKE_SOURCE_DIR}/aitools.cmake)