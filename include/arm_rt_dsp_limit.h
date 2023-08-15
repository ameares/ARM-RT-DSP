/**
 * \file arm_rt_dsp_limit.h
 * \brief This file contains the definitions of the ARM DSP types and functions.
 * 
*/

#ifndef ARM_RT_DSP_LIMIT_
#define ARM_RT_DSP_LIMIT_

#include <stdint.h>
#include <string.h>
#include "arm_rt_dsp_core.h"

/**
 * \defgroup limit_group Limit Functions
 * 
 * The limit functions can be used to limit the range of an input or output value in your
 * control algorithm.  The functions are inlined to avoid function call overhead.  Variants
 * allow limiting on only one side of the range or both sides.
 * 
 * \image html test_sequence_limit_i16.png "Sequential calls to limit_i16(val, llim, ulim)"
 * \image latex test_sequence_limit_i16.png "Sequential calls to limit_i16(val, llim, ulim)" width=5cm
 * 
 * @{
*/

/**
 * \brief Limits the input value to both upper and lower limits.
 *
 * \param val Input value to be limited.
 * \param llim Lower limit to be applied.
 * \param ulim Upper limit to be applied.
 * \return A value in the range [-1.0, 1.0].
 */
static inline float limit_f32(float val, float llim, float ulim) {
    if (val > ulim) val = ulim;
    if (val < llim) val = llim;
    return val;
}


/**
 * \brief Limits the input value to the supplied upper limit.
 *
 * \param val Input value to be limited.
 * \param ulim Upper limit to be applied.
 * \return A value in the range [-1.0, ulim].
 */
static inline q31_t upper_limit_q31(q31_t val, q31_t ulim) {
    if (val > ulim) {
        val = ulim;
    }
    return val;
}


/**
 * \brief Limits the input value to the supplied lower limit.
 *
 * \param val Input value to be limited.
 * \param llim Lower limit to be applied.
 * \return A value in the range [llim, 1.0].
 */
static inline q31_t lower_limit_q31(q31_t val, q31_t llim) {
    if (val < llim) {
        val = llim;
    }
    return val;
}


/**
 * \brief Limits the input value to the supplied upper and lower limits.
 *
 * \param val Input value to be limited.
 * \param llim Lower limit to be applied.
 * \param ulim Upper limit to be applied.
 * \return A value in the range [llim, ulim].
 */
static inline q31_t limit_q31(q31_t val, q31_t llim, q31_t ulim) {
    if (val > ulim) {
        val = ulim;
    }
    if (val < llim) {
        val = llim;
    }
    return val;
}


/**
 * \brief Limits the input value to the supplied upper and lower limits.
 *
 * \param val Input value to be limited.
 * \param llim Lower limit to be applied.
 * \param ulim Upper limit to be applied.
 * \return A value in the range [llim, ulim].
 */
static inline int32_t limit_i32(int32_t val, int32_t llim, int32_t ulim) {
    if (val > ulim) {
        val = ulim;
    }
    if (val < llim) {
        val = llim;
    }
    return val;
}


/**
 * \brief Limits the input value to the supplied upper and lower limits.
 *
 * \param val Input value to be limited.
 * \param llim Lower limit to be applied.
 * \param ulim Upper limit to be applied.
 * \return A value in the range [llim, ulim].
 */
static inline uint32_t limit_u32(uint32_t val, uint32_t llim, uint32_t ulim) {
    if (val > ulim) {
        val = ulim;
    }
    if (val < llim) {
        val = llim;
    }
    return val;
}


/**
 * \brief Limits the input value to the supplied upper and lower limits.
 * 
 * 
 *
 * \param val Input value to be limited.
 * \param llim Lower limit to be applied.
 * \param ulim Upper limit to be applied.
 * \return A value in the range [llim, ulim].
 */
static inline int16_t limit_i16(int16_t val, int16_t llim, int16_t ulim) {
    if (val > ulim) {
        val = ulim;
    }
    if (val < llim) {
        val = llim;
    }
    return val;
}


/**
 * \brief Limits the input value to the supplied upper and lower limits.
 *
 * \param val Input value to be limited.
 * \param llim Lower limit to be applied.
 * \param ulim Upper limit to be applied.
 * \return A value in the range [llim, ulim].
 */
static inline uint16_t limit_u16(uint16_t val, uint16_t llim, uint16_t ulim) {
    if (val > ulim) {
        val = ulim;
    }
    if (val < llim) {
        val = llim;
    }
    return val;
}


/**
 * \brief Limits the input value to the supplied upper and lower limits.
 *
 * \param val Input value to be limited.
 * \param llim Lower limit to be applied.
 * \param ulim Upper limit to be applied.
 * \return A value in the range [llim, ulim].
 */
static inline acc32_t limit_acc31(acc32_t val, acc32_t llim, acc32_t ulim) {
    if (val > ulim) {
        val = ulim;
    }
    if (val < llim) {
        val = llim;
    }
    return val;
}


/**
 * \brief Limits the input value to the supplied upper limit.
 *
 * \param val Input value to be limited.
 * \param ulim Upper limit to be applied.
 * \return A value in the range [0, ulim].
 */
static inline uint16_t upper_limit_u16(uint16_t val, uint16_t ulim) {
    if (val > ulim) {
        val = ulim;
    }
    return val;
}


/**
 * \brief Maximum function for Q31 format.
 *
 * \param x First value.
 * \param y Second value.
 * \return The maximum of x and y.
 */
static inline q31_t max_q31(q31_t x, q31_t y) {
    if (x > y) {
        return x;
    } else {
        return y;
    }
}


/**
 * \brief Minimum function for Q31 format.
 *
 * \param x First value.
 * \param y Second value.
 * \return The minimum of x and y.
 */
static inline q31_t min_q31(q31_t x, q31_t y) {
    if (x > y) {
        return y;
    } else {
        return x;
    }
}

/**
 * @}
*/


#endif // ARM_RT_DSP_LIMIT_