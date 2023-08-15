/**
 * \file arm_rt_dsp.h
 * \brief This file contains the definitions of the ARM DSP types and functions.
 * 
*/

#ifndef ARM_RT_DSP_
#define ARM_RT_DSP_

#include <stdint.h>
#include <string.h>

#define MOCK_ARM_MATH

// This includes the basic fixed point types and support macros/functions.
#include "arm_rt_dsp_core.h"

// Limit and min/max functions.
#include "arm_rt_dsp_limit.h"

// Digital Filters
#include "arm_rt_dsp_filter.h"

// Ramp functions
#include "arm_rt_dsp_ramp.h"

// PI and PID controllers
#include "arm_rt_dsp_controller.h"

// Misc functions, convert, sample, and threshold.
#include "arm_rt_dsp_misc.h"

#if (0)
static inline int16_t __SSAT(int16_t value, uint16_t sat) {
    int16_t max = (1 << (sat - 1)) - 1;
    int16_t min = -max - 1;

    if (value > max) {
        return max;
    } else if (value < min) {
        return min;
    } else {
        return value;
    }
}
#endif


#endif