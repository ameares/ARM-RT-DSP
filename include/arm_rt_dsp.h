

#ifndef ARM_RT_DSP_
#define ARM_RT_DSP_

#include <stdint.h>

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
typedef int16_t acc15_t;

/**
 * \brief A 32-bit accumulator data type in 17.15 format.
 *
 * In order to stay consistent with the ARM DSP Q types, the sign bit is not counted.
 *
 * Does this name even make sense.  Maybe acc32_t was better or acc17_15_t or anything. AM
 */
typedef int32_t acc31_t;

/**
 * \brief A 64-bit accumulator in 33.31 format.
 *
 * In order to stay consistent with the ARM DSP Q types, the sign bit is not counted.
 */
typedef int64_t acc63_t;

/** \brief Macro for defining a q15_t constant value in the range [-1.0, 1.0). */
#define Q15(x) ((q15_t)((x) < 0.999969482421875 ? ((x) >= -1 ? (x)*0x8000 : 0x8000) : 0x7FFF))

/** \brief Macro for defining a q31_t constant value in the range [-1.0, 1.0). */
#define Q31(x) ((q31_t)((x) < 1 ? ((x) >= -1 ? (x)*0x80000000 : 0x80000000) : 0x7FFFFFFF))

/** \brief Macro for defining an \ref acc15_t constant value in the range [-255.0, 255.0). */
#define ACC15(x) ((acc15_t)((x) < 255.9921875 ? ((x) >= -256 ? (x)*0x80 : 0x8000) : 0x7FFF))

/** \brief Macro for defining an \ref acc31_t constant value in the range [-65535.0, 65535.0). */
#define ACC31(x) ((acc31_t)((x) < 65535.999969482421875 ? ((x) >= -65536 ? (x)*0x8000 : 0x80000000) : 0x7FFFFFFF))

static inline int32_t __SSAT(int32_t value, uint32_t sat) {
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
*/
static inline q15_t mul_q15(q15_t x, q15_t y) {
    q15_t out;
    out = ((q31_t) x * y) >> 15;
    //out = __SSAT(out, 15);
    // I am still playing around with the finer points of DSP operations. AM 2/15/21
    return out; // << 1U;
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
    //out = __SSAT(out, 31);
    // I am still playing around with the finer points of DSP operations. AM 2/15/21
    return out; // << 1U;
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
 * The saturated version sacrifices the lowest bit.
 *
 * \todo Make a rounding version.
 * \param x The first multiplicand.
 * \param y The second multiplicand.
 * \return The saturated product of the two multiplicands with a range of [-1.0, 1.0).
 */
static inline q31_t mulsat_q31(q31_t x, q31_t y) {
    q31_t out;
    out = ((q63_t) x * y) >> 32;
    out = __SSAT(out, 31);
    // I am still playing around with the finer points of DSP operations. AM 2/15/21
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


#endif