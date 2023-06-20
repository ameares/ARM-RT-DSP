/**
 * \file arm_rt_dsp.h
 * \brief This file contains the definitions of the ARM DSP types and functions.
 * 
*/

#ifndef ARM_RT_DSP_
#define ARM_RT_DSP_

#include <stdint.h>

#define MOCK_ARM_MATH


#ifdef MOCK_ARM_MATH
/**
 * \brief A 16-bit fractional data type in 1.15 format.
 * 
 * The most significant bit is the sign bit.
 */
typedef int16_t q15_t;

/**
 * \brief A 32-bit fractional data type in 1.31 format.
 * 
 * The most significant bit is the sign bit.
 */
typedef int32_t q31_t;

/**
 * \brief A 32-bit floating point data type.
 * 
 * This is the same as the standard C single precision float type.
*/
typedef float float32_t;

#endif

/**
 * \brief A 64-bit fractional data type in 1.63 format.
 * 
 * The most significant bit is the sign bit.
 */
typedef int64_t q63_t;

/**
 * \brief A 16-bit accumulator data type in 9.7 format.
 *
 * In order to stay consistent with the ARM DSP Q types, the sign bit is not
 * counted.
 */
typedef int16_t acc16_t;

/**
 * \brief A 32-bit accumulator data type in 17.15 format.
 *
 * In order to stay consistent with the ARM DSP Q types, the sign bit is not counted.
 *
 * Does this name even make sense.  Maybe acc32_t was better or acc17_15_t or anything. AM
 */
typedef int32_t acc32_t;

/**
 * \brief A 64-bit accumulator in 33.31 format.
 *
 * In order to stay consistent with the ARM DSP Q types, the sign bit is not counted.
 */
typedef int64_t acc64_t;

/** \brief Macro for defining a q15_t constant value in the range [-1.0, 1.0). */
#define Q15(x) ((q15_t)((x) < 0.999969482421875 ? ((x) >= -1 ? (x)*0x8000 : 0x8000) : 0x7FFF))

/** \brief Macro for defining a q31_t constant value in the range [-1.0, 1.0). */
#define Q31(x) ((q31_t)((x) < 1 ? ((x) >= -1 ? (x)*0x80000000 : 0x80000000) : 0x7FFFFFFF))

/** \brief Macro for defining an \ref acc16_t constant value in the range [-255.0, 255.0). */
#define ACC16(x) ((acc16_t)((x) < 255.9921875 ? ((x) >= -256 ? (x)*0x80 : 0x8000) : 0x7FFF))

/** \brief Macro for defining an \ref acc32_t constant value in the range [-65535.0, 65535.0). */
#define ACC32(x) ((acc32_t)((x) < 65535.999969482421875 ? ((x) >= -65536 ? (x)*0x8000 : 0x80000000) : 0x7FFFFFFF))


// For when the arm dsp library isn't present.
// I hope to either emulate ARM or setup a real test platform someday. AM 5/20/23
#ifdef MOCK_ARM_MATH

static inline int32_t __SSAT(int32_t value, uint32_t sat)
{
    int32_t max = (1 << (sat - 1)) - 1;
    int32_t min = -max - 1;

    if (value > max) {
        return max;
    } else if (value < min) {
        return min;
    } else {
        return value;
    }
}

// Adds the two int32_t values.
// Need to check on what this really does in arm_math.h
static inline int32_t __QADD(int32_t x, int32_t y)
{
    return x + y;
}

// subtracts the two int32_t values.
// Need to check on what this really does in arm_math.h
static inline int32_t __QSUB(int32_t x, int32_t y)
{
    return x - y;
}

#endif

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


/**
 * \brief   Signed Saturate
 * \details Saturates a signed value.
 * \param [in]  value  Value to be saturated
 * \param [in]    sat  Bit position to saturate to (1..32)
 * \return             Saturated value
 */
static inline int64_t ssat_i64(int64_t val, uint32_t sat)
{
  if ((sat >= 1U) && (sat <= 64U))
  {
    const int64_t max = (int64_t)((1U << (sat - 1U)) - 1U);
    const int64_t min = -1 - max ;
    if (val > max)
    {
      return max;
    }
    else if (val < min)
    {
      return min;
    }
  }
  return val;
}


/**
 * \brief Calculates the absolute value of the input without saturation.
 * 
 * \param parVal The input value.
 * \return The absolute value of the input in the range [1.0, 1.0).
 */
static inline q15_t abs_q15(q15_t parVal)
{
    if (parVal < 0) {
        return -parVal;
    } else {
        return parVal;
    }
}


/**
 * \brief Calculates the absolute value of the input without saturation.
 *
 * \param parVal The input value.
 * \return The absolute value of the input in the range [1.0, 1.0).
 */
static inline q31_t abs_q31(q31_t parVal)
{
    if (parVal < 0) {
        return -parVal;
    } else {
        return parVal;
    }
}


/**
 * \brief Calculates the absolute value of the input without saturation.
 * 
 * \param parVal The input value.
 * \return The absolute value of the input in the range [1.0, 1.0).
 */
static inline q15_t abs_sat_q15(q15_t parVal)
{
    int16_t wResult;

    /* Take opposite of value and test value in the process */
    wResult = -parVal;

    if (wResult < 0)
    {
        /* result is negative, that means :
        - parVal is positive : following operation will subtract 0 to parVal
        - parVal is 0x8000 : following operation will subtract 1 to parVal => 0x7FFF */
        wResult = parVal - (((uint16_t)parVal) >> 15);
    }
    /* else result is positive, that means that parVal is negative, nothing else to do */
    return wResult;
}


/**
 * \brief Calculates the absolute value of the input with saturation.
 *
 * \param parVal The input value.
 * \return The absolute value of the input saturated to [1.0, 1.0).
 */
static inline q31_t abs_sat_q31(q31_t parVal)
{
    int32_t wResult;

    /* Take opposite of value and test value in the process */
    wResult = -parVal;

    if (wResult < 0)
    {
        /* result is negative, that means :
        - parVal is positive : following operation will subtract 0 to parVal
        - parVal is 0x80000000 : following operation will subtract 1 to parVal => 0x7FFFFFFF */
        wResult = parVal - (((uint32_t)parVal) >> 31);
    }
    /* else result is positive, that means that parVal is negative, nothing else to do */
    return wResult;
}


/**
 * \brief Multiplies two Q15s.
 * 
 * \param x The first multiplicand.
 * \param y The second multiplicand.
 * \return The product of the two multiplicands.
*/
static inline q15_t mul_q15(q15_t x, q15_t y) {
    q15_t out;
    out = ((q31_t) x * y) >> 15;
    return out;
}


/**
 * \brief Multiplies two Q31s.
 *
 * \param x The first multiplicand.
 * \param y The second multiplicand.
 * \return The product of the two multiplicands.
 */
static inline q31_t mul_q31(q31_t x, q31_t y) {
    q31_t out;
    out = ((q63_t) x * y) >> 31;
    return out;;
}


/**
 * \brief Multiplies two Q15s with saturation.
 *
 * Some of these capabilities are captured in the toolchain's intrinsics or "idioms".
 * \todo Make a rounding version.
 * \param x The first multiplicand.
 * \param y The second multiplicand.
 * \return The saturated product of the two multiplicands with a range of [-1.0, 1.0).
 */
static inline q15_t mulsat_q15(q15_t x, q15_t y) {
    q31_t out;
    out = ((q31_t) x * y) >> 16;
    out = __SSAT(out, 15);
    return out << 1U;
}


/**
 * \brief Multiplies two Q31s with saturation.
 * 
 * \param x The first multiplicand.
 * \param y The second multiplicand.
 * \return The saturated product of the two multiplicands with a range of [-1.0, 1.0).
 */
static inline q31_t mulsat_q31(q31_t x, q31_t y) {
    q31_t out;
    out = ((q63_t) x * y) >> 32;
    out = __SSAT(out, 31);
    return out << 1U;
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
 * \brief Converts an unsigned ADC raw value to a Q15 format with offset and scale applied.
 *
 * The raw value must be provided in right justified format and is assumed to be 12 bits.
 * Saturation arithmetic is used.
 *
 * \param x The raw ADC result value in "counts".
 * \param offset The offset is specified as an unsigned "counts" value.
 * \param slope The slope is specified in Q15 format and is in the range [-1.0, 1.0).
 * \return The offset and scaled result in Q15 format is in the range [-1.0, 1.0).
 */
static inline q15_t adc_process_sample_q15(uint16_t x, int16_t offset, q15_t slope) {
    return mulsat_q15(((q15_t) x - (q15_t) offset) << 4, slope);
}


/**
 * \brief Converts an unsigned ADC raw value to a Q31 format with offset and scale applied.
 *
 * This version is for input that use the mid-rail as the reference.
 * The raw value must be provided in right justified format and is assumed to be 12 bits.
 * Saturation arithmetic is used.
 *
 * \param x The raw ADC result value in "counts".
 * \param offset The offset is specified as an unsigned "counts" value.
 * \param slope The slope is specified in Q31 format and is in the range [-1.0, 1.0).
 * \return The offset and scaled result in Q31 format is in the range [-1.0, 1.0).
 */
static inline q31_t adc_process_sample_q31(uint16_t x, int16_t offset, q31_t slope) {
   return mulsat_q31(((q31_t) x - (q31_t) offset) << 20, slope);
}


/**
 * \brief Converts an unsigned ADC raw value to a Q31 format with offset and scale applied.
 *
 * This version is for inputs that use 0V as the reference.
 *
 * \param x The raw ADC result value in "counts".
 * \param offset The offset is specified as an unsigned "counts" value.
 * \param slope The slope is specified in Q31 format and is in the range [-1.0, 1.0).
 * \return The offset and scaled result in Q31 format is in the range [-1.0, 1.0).
 */
static inline q31_t adc_process_sample_u_q31(uint16_t x, int16_t offset, q31_t slope) {
   return mulsat_q31(((q31_t) x - (q31_t) offset) << 19, slope);
}


/**
 * \brief Converts an unsigned ADC raw value to a Q31 format with offset and scale applied.
 *
 * This version is for inputs that use 0V as the reference.
 *
 * \param x The raw ADC result value in "counts".
 * \param offset The offset is specified as an unsigned "counts" value.
 * \param slope The slope is specified in Q31 format and is in the range [-1.0, 1.0).
 * \return The offset and scaled result in Q31 format is in the range [-1.0, 1.0).
 */
static inline q31_t adc_process_sample_i16_q31(int16_t x, int16_t offset, q31_t slope) {
   return mulsat_q31(((q31_t) x - (q31_t) offset) << 16, slope);
}


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
 * \brief Converts a value from 1.31 fixed point format, q31_t, to an int16_t with an applied scaling factor and rounding.
 *
 * A voltage measurement in q31_t format with a scale of 1.0 represents 1kV has
 * a range of [-1.0kV, 1.0kV).  Calling convert_round_q31_to_i16 on this
 * measurement with a scale of 1000 will yield an integer in the range of
 * [-1000, 1000) with units of volts.
 *
 * \param x Input value to be converted
 * \param scale Scaling value to be applied.
 * \return The converted value.
 */
static inline int16_t convert_round_q31_to_i16(q31_t x, uint32_t scale) {
    // >> 31 if no rounding.
    // Is it enough to just round the last bit? AM
    q63_t rval = ((q63_t)x*scale) >> 30;
    if (rval & 0x01) rval++;
    return (int16_t)(rval>>1);
}


/**
 * \brief Converts a value from 1.31 fixed point format, q31_t, to an int16_t with an applied scaling factor.
 *
 * \param x Input value to be converted
 * \param scale Scaling value to be applied.
 * \return The converted value.
 */
static inline int16_t convert_q31_to_i16(q31_t x, uint32_t scale) {
    // >> 31 if no rounding.
    //
    return (int16_t)((q63_t)x * scale >> 31);
}


/**
 * \brief Converts a value from 1.31 fixed point format, q31_t, to a uint16_t with an applied scaling factor.
 *
 * \param x Input value to be converted
 * \param scale Scaling value to be applied.
 * \return The converted value.
 */
static inline uint16_t convert_q31_to_u16(q31_t x, uint32_t scale) {
    // I wonder about uint16_t scale vs int16_t scale. AM 3/9/22
    // Does it need to check for sign? AM 3/9/22
    uint16_t rval = (uint16_t)((q63_t)x * scale >> 31);
    return rval;
}


/**
 * \brief Converts a value from 1.31 fixed point format, q31_t, to a uint32_t with an applied scaling factor.
 *
 * \param x Input value to be converted
 * \param scale Scaling value to be applied.
 * \return The converted value.
 */
static inline uint32_t convert_q31_to_u32(q31_t x, uint32_t scale) {
    // I wonder about uint16_t scale vs int16_t scale. AM 3/9/22
    // Does it need to check for sign? AM 3/9/22
    uint32_t rval = (uint32_t)((q63_t)x * scale >> 31);
    return rval;
}


/**
 * \brief Converts a value from 1.31 fixed point format, q31_t, to a int32_t with an applied scaling factor and rounding.
 *
 * \param x Input value to be converted
 * \param scale Scaling value to be applied.
 * \return The converted value.
 */
static inline int32_t convert_round_q31_to_i32(q31_t x, uint32_t scale) {
    q63_t rval = ((q63_t)x*scale) >> 30;
    if (rval & 0x01) rval++;
    return (int32_t)(rval>>1);
}


/**
 * \brief Converts a value from 1.31 fixed point format, q31_t, to a int32_t with an applied scaling factor.
 *
 * \param x Input value to be converted
 * \param scale Scaling value to be applied.
 * \return The converted value.
 */
static inline int32_t convert_q31_to_i32(q31_t x, uint32_t scale) {
    int32_t rval = (int32_t)((q63_t)x * scale >> 31);
    return rval;
}


/**
  \brief Convert a uint16_t to a q31_t.
  \param x Value to convert.
  \param mul Scale of value to convert.
  \return Converted value.
*/
static inline q31_t convert_u16_to_q31(uint16_t x, int32_t scale) {
  // For example, feed in 576 and get back 0.576
  // scale = 1000 in above example.
  return (q31_t)( ( ((uint64_t)x) << 31 ) / scale );
}


/**
  \brief Convert an int16_t to a q31_t.
  \param x Value to convert.
  \param mul Scale of value to convert.
  \return Converted value.
*/
static inline q31_t convert_i16_to_q31(int16_t x, int32_t scale) {
  // For example, feed in 576 and get back 0.576
  // scale = 1000 in above example.
  return (q31_t)( ( ((int64_t)x) << 31 ) / scale );
}


/**
  \brief Convert an int32_t to a q31_t.
  \param x Value to convert.
  \param mul Scale of value to convert.
  \return Converted value.
*/
static inline q31_t convert_i32_to_q31(int32_t x, int32_t scale) {
  // For example, feed in 576 and get back 0.576
  // scale = 1000 in above example.
  return (q31_t)( ( ((int64_t)x) << 31 ) / scale );
}


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


/**
 * \brief Context structure for the hysteresis function.
 *
 */
typedef struct
{
    q31_t hyst_on;     /**< Value determining the upper threshold */
    q31_t hyst_off;    /**< Value determining the lower threshold */
    int32_t out_state; /**< Actual state of the output */
} hysteresis_thresh_t;


/**
 * \brief Initialize a hyseresis process function.
 *
 * \param l_thresh Value determining the lower threshold.
 * \param h_thresh Value determining the upper threshold.
 * \param H The context structure for this hysteresis process.
 */
void hysteresis_init(q31_t l_thresh, q31_t h_thresh, hysteresis_thresh_t *H);


/**
 * \brief Applies a threshold with hysteresis to a q31_t value.
 *
 * \param val The input value.
 * \param H The context structure for this hysteresis process.
 * \return True or false.
 */
static inline int32_t hysteresis_threshold(q31_t val, hysteresis_thresh_t *H) {
    if (val > H->hyst_on) {
        H->out_state = 0x01;
    } else if (val < H->hyst_off) {
        H->out_state = 0x00;
    }
    return H->out_state;
}


/**
 * \brief Context structure for the hysteresis function.
 *
 */
typedef struct
{
    int16_t hyst_on;     /**< Value determining the upper threshold */
    int16_t hyst_off;    /**< Value determining the lower threshold */
    int16_t out_state; /**< Actual state of the output */
} hysteresis_thresh_i16_t;


/**
 * \brief Initialize a hyseresis process function.
 *
 * \param l_thresh Value determining the lower threshold.
 * \param h_thresh Value determining the upper threshold.
 * \param H The context structure for this hysteresis process.
 */
void hysteresis_init_i16(int16_t l_thresh, int16_t h_thresh, hysteresis_thresh_i16_t *H);


/**
 * \brief Applies a threshold with hysteresis to a i16 value.
 *
 * \param val The input value.
 * \param H The context structure for this hysteresis process.
 * \return True or false.
 */
static inline int32_t hysteresis_threshold_i16(int16_t val, hysteresis_thresh_i16_t *H) {
    if (val > H->hyst_on) {
        H->out_state = 0x01;
    } else if (val < H->hyst_off) {
        H->out_state = 0x00;
    }
    return H->out_state;
}


/**
 * \brief Checks if a value is within some delta of a nominal value.
 *
 * \param value The input value.
 * \param nominal The nominal value.
 * \param delta The delta applied above and below the nominal value.
 * \return True if nominal - delta < value < nominal + delta.  Otherwise returns false.
 */
static inline int32_t check_delta_q31(q31_t value, q31_t nominal, q31_t delta) {
    int32_t rval = 0;
    if ((value >= __QSUB(nominal, delta))&&(value <= __QADD(nominal, delta))) {
        rval = 1;
    }
    return rval;
    //return 1;
}

/**
 * \brief Checks if a value is within some delta of a nominal value.
 *
 * \param value The input value.
 * \param nominal The nominal value.
 * \param delta The delta applied above and below the nominal value.
 * \return True if nominal - delta < value < nominal + delta.  Otherwise returns false.
 */
static inline int32_t check_delta_f32(float32_t value, float32_t nominal, float32_t delta) {
    int32_t rval = 0;
    if ((value >= nominal - delta)&&(value <= nominal + delta)) {
        rval = 1;
    }
    return rval;
}




#endif