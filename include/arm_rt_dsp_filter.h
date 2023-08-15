/**
 * \file arm_rt_dsp_filter.h
 * \brief This file contains the definitions of the ARM DSP types and functions.
 * 
*/

#ifndef ARM_RT_DSP_FILTER_
#define ARM_RT_DSP_FILTER_

#include <stdint.h>
#include <string.h>
#include "arm_rt_dsp_core.h"


/**
 * \brief Pseudo windowed moving average data structure.
 *
 * The init function from the 56800EX DSP library sets the accumulator to a value that would output
 * the desired initial value on the first iteration.  For now, just initialize the the structure
 * to the desired window size and zero the accumulator.  Remember the accumulator will have to wind
 * up when the filter is used.  For glacially slow filters, winding up might take eons.
 */
typedef struct {
    acc64_t acc; //!< A 64-bit accumulator.
    uint16_t sh; //!< The window size is equal to 2^sh.
} filter_pma_a63_t;


/**
 * \brief A process function for a pseudo windowed moving average filter.
 *
 * \param inx The new input sample.
 * \param param The filter's configuration and state data.
 * \return A new filtered output sample.
 */
static inline q31_t filter_pma_q31(q31_t inx, filter_pma_a63_t *param) {
    q31_t y;
 
    // Accumulate
    param->acc += inx;

    // Output is average
    // I am not sure if this needs rounding or other improvements.
    y = param->acc >> param->sh;

    // Dissipate by the average.  This is the pseudo windowed part.
    param->acc -= y;
    return y;
}



#endif /* ARM_RT_DSP_FILTER_ */