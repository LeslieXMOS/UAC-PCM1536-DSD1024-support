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

void main_tile0(chanend_t c_tile1, unsigned tile1_id)
{
    (void) c_tile1;
    (void) tile1_id;
}

void main_tile1(chanend_t c_tile0, unsigned tile0_id)
{
    (void) c_tile0;
    (void) tile0_id;
}