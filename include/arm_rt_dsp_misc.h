/**
 * \file arm_rt_dsp_misc.h
 * \brief This file contains the definitions of the ARM DSP types and functions.
 * 
*/

#ifndef ARM_RT_DSP_MISC_
#define ARM_RT_DSP_MISC_

#include <stdint.h>
#include <string.h>
#include "arm_rt_dsp_core.h"

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



#endif /*ARM_RT_DSP_MISC_*/