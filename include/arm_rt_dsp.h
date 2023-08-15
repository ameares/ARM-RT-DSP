/**
 * \file arm_rt_dsp.h
 * \brief The main header file for the ARM RT DSP library.
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

#endif