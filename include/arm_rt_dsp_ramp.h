/**
 * \file include/arm_rt_dsp_ramp.h
 * \brief Ramp functions.
*/


#ifndef ARM_RT_DSP_RAMP_
#define ARM_RT_DSP_RAMP_

#include <stdint.h>
#include <string.h>
#include "arm_rt_dsp_core.h"


/**
 * \brief Signed int16_t ramp limiter data structure.
 *
 */
typedef struct {
    int16_t llim;
    int16_t ulim;
    int16_t inc;
    int16_t y;
} ramp_limit_i16_t;


/**
 * \brief Signed q15_t ramp limiter data structure.
 *
 */
typedef struct {
    q15_t llim;
    q15_t ulim;
    q15_t inc;
    q15_t y;
} ramp_limit_q15_t;


/**
 * \brief Signed q31_t ramp data structure.
 *
 */
typedef struct {
    q31_t inc;
    q31_t y;
} ramp_q31_t;


// Linear ramp from one number to another with upper limit and lower limit.
// I am still playing with the concept here.  Does it want limits?  Or should I just use saturated addition.
// Should it be inlined?

/**
 * \brief Initialize the linear ramp data structure with an initial output value.
 *
 * \param y0 Initial output value.
 * \param r Ramp data structure.
 */
void ramp_limit_init_i16(int16_t y0, ramp_limit_i16_t *r);


/**
 * \brief Linear ramp from one number to another with upper limit and lower limit applied.
 *
 * \param x Input value is new or current ramp target.
 * \param r Ramp data structure.
 * \return The ramped value output approaches the current target at the ramp rate specified.
 */
int16_t ramp_limit_i16(int16_t x, ramp_limit_i16_t *r);


/**
 * \brief Initialize the linear ramp data structure with an initial output value.
 *
 * \param y0 Initial output value.
 * \param r Ramp data structure.
 */
void ramp_limit_init_q15(q15_t y0, ramp_limit_q15_t *r);


/**
 * \brief Linear ramp from one number to another with upper limit and lower limit applied.
 *
 * \param x Input value is new or current ramp target.
 * \param r Ramp data structure.
 * \return The ramped value output approaches the current target at the ramp rate specified.
 */
q15_t ramp_limit_q15(q15_t x, ramp_limit_q15_t *r);


/**
 * \brief Initialize the linear ramp data structure with an initial output value.
 *
 * \param y0 Initial output value.
 * \param r Ramp data structure.
 */
void ramp_init_q31(q31_t y0, ramp_q31_t *r);


/**
 * \brief Linear ramp from one number to another.
 *
 * \param x Input value is new or current ramp target.
 * \param r Ramp data structure.
 * \return The ramped value output approaches the current target at the ramp rate specified.
 */
q31_t ramp_q31(q31_t x, ramp_q31_t *r);


#endif // _ARM_RT_DSP_RAMP_H_