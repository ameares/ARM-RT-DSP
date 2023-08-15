/**
 * \file arm_rt_dsp_controller.h
 * \brief Controllers.
 * 
*/

#ifndef ARM_RT_DSP_CONTROLLER_
#define ARM_RT_DSP_CONTROLLER_

#include <stdint.h>
#include <string.h>
#include "arm_rt_dsp_core.h"


// PID Functions

#define PI_Q15_STATE_BUFFER_SIZE 2

/**
 * \brief Instance structure for the iir PI controller that uses a q15_t data type.
 *
 */
typedef struct
{
  acc16_t A0;           /**< The derived gain, A0 = Kp + Ki. */
  acc16_t A1;           /**< The derived gain, A0 = -Kp. */
  q15_t state[PI_Q15_STATE_BUFFER_SIZE];       /**< The state array of length 2. */
  acc16_t Kp;           /**< The proportional gain. */
  acc16_t Ki;           /**< The integral gain. */
} iir_pi_instance_q15;


/**
 * \brief Initializes PI instance structure.
 *
 * \param S Pointer to the PI instance structure.
 * \param resetStateFlag Set this to true to clear the state buffer.
 */
void iir_pi_init_q15(iir_pi_instance_q15 * S, int32_t resetStateFlag);


/**
 * \brief PI process function that uses q15_t data types.
 *
 * This is an IIR implementation of a PI controller and has practical limits on the
 * accumulator and output.  Note that if the output or accumulator saturate, the PI
 * controller will behave poorly.  A 32 bit accumulator is used to maintain as much
 * range as possible. Gains are given in acc16_t format.
 *
 * \param S Pointer to the PI instance structure.
 * \param in Input sample value.
 * \return The controller output value.
 */
static inline q15_t iir_pi_q15(iir_pi_instance_q15 * S, q15_t in) {
    int32_t temp;
    q15_t out;

    // I am going do this the straightforward way first. AM 3/19/21
    // Note Kp + Ki < 255
    // This results in 10.22 format.
    // 9.7 * 1.15 => 10.22
    temp = (int32_t)S->A0 * (int32_t)in;
    temp += (int32_t)S->A1 * (int32_t)S->state[0];
    temp += ((int32_t)S->state[1])<<7;  // to move the decimal from 1.15 to 1.22

    // temp is 10.22 format
    // Add rounding of the last bit here.
    temp += (1<<6);
    temp = temp >> 7;
    // now temp is in 10.15 format.
    out = (q15_t)(__SSAT(temp, 16));
    // Now out is in 1.15 format and has a range of [-1.0, 1.0)

    // Update state
    S->state[0] = in;       // state[0] is x[n-1]
    S->state[1] = out;      // state[1] is y[n-1]
    return (out);
}


#define PI_Q31_STATE_BUFFER_SIZE 2

/**
 * \brief Instance structure for the iir PI controller that uses a q31_t data type.
 *
 */
typedef struct
{
  acc32_t Kp;            /**< The proportional gain. */
  acc32_t Ki;            /**< The integral gain. */
  acc32_t A0;            /**< The derived gain, A0 = Kp + Ki + Kd . */
  acc32_t A1;            /**< The derived gain, A1 = -Kp - 2Kd. */
  q31_t state[PI_Q31_STATE_BUFFER_SIZE];        /**< The state array of length 3. */
} iir_pi_instance_q31;


/**
 * \brief Initializes PI instance structure.
 *
 * \param S Pointer to the PI instance structure.
 * \param resetStateFlag Set this to true to clear the state buffer.
 */
void iir_pi_init_q31( iir_pi_instance_q31 *S, int32_t resetStateFlag);


#define PID_Q31_STATE_BUFFER_SIZE 3

/**
 * \brief Instance structure for the iir PID controller that uses a q31_t data type.
 *
 */
typedef struct
{
  acc32_t Kp;            /**< The proportional gain. */
  acc32_t Ki;            /**< The integral gain. */
  acc32_t Kd;
  acc32_t A0;            /**< The derived gain, A0 = Kp + Ki + Kd . */
  acc32_t A1;            /**< The derived gain, A1 = -Kp - 2Kd. */
  //acc32_t A2;
  acc32_t A0d;
  acc32_t A1d;
  acc32_t A2d;
  q31_t state[PID_Q31_STATE_BUFFER_SIZE];        /**< The state array of length 3. */

  q31_t dstate;
  q31_t fdstate;

} iir_pid_instance_q31;


/**
 * \brief Initializes PID instance structure.
 *
 * \param S Pointer to the PI instance structure.
 * \param resetStateFlag Set this to true to clear the state buffer.
 */
void iir_pid_init_q31( iir_pid_instance_q31 *S, int32_t resetStateFlag);



/**
 * \brief PI process function that uses q31_t data types.
 *
 * This is an IIR implementation of a PI controller and has practical limits on the
 * accumulator and output.  Note that if the output or accumulator saturate, the PI
 * controller will behave nonlinearly.  A 64 bit accumulator is used to maintain as
 * much range as possible. Gains are given in acc32_t format.
 *
 * \param S Pointer to the PI instance structure.
 * \param in Input sample value.
 * \return The controller output value.
 */
static inline q31_t iir_pi_q31(iir_pi_instance_q31 *S, q31_t in)
{
    int64_t acc;
    q31_t out;

    // Could add some guard bits?
    // 2 bits would throw away
    // 17.15 * 1.31 => 18.46
    /* acc = A0 * x[n]  */
    acc = (int64_t)S->A0 * (int64_t)in;
    acc += (int64_t)S->A1 * (int64_t)S->state[0];
    acc += ((int64_t)S->state[1])<<15;   // move the decimal from 1.31 to 1.46

    // acc is in 18.46 format
    // could add rounding here.
    acc = acc >> 15;

    // The other algorithm uses __SSAT for 32 bit saturation
    out = ssat_i64(acc, 32);

    // out is [-1.0, 1.0) here and in q31_t format.  In practice the effective integrator might be saturated below that value.
    // Say we wanted a 16-bit signed integer output but we wanted the gains to be somewhat readable.
    // To get 6000 from 0.170 with a Kp of 16.4u
    // Say we shift 6000<<2 to make +/-24000, that makes the gain 66u
    // Or instead we could shift the gains by how many?
    // 1/16.4u is about 15 bits

    S->state[0] = in;
    S->state[1] = out;
    return out;
}

/**
 * \brief PID process function that uses q31_t data types.
 *
 * This is an IIR implementation of a PID controller and has practical limits on the
 * accumulator and output.  Note that if the output or accumulator saturate, the PI
 * controller will behave nonlinearly.  A 64 bit accumulator is used to maintain as
 * much range as possible. Gains are given in acc32_t format.
 *
 * \param S Pointer to the PID instance structure.
 * \param in Input sample value.
 * \return The controller output value.
 */
static inline q31_t iir_pid_q31(iir_pid_instance_q31 *S, q31_t in)
{
    int64_t acc;
    int64_t acc_d;
    q31_t out;

	// Could add some guard bits?
	// 2 bits would throw away
	// 17.15 * 1.31 => 18.46
	/* acc = A0 * x[n]  */
    acc = (int64_t)S->A0 * (int64_t)in;
    acc += (int64_t)S->A1 * (int64_t)S->state[0];
    //acc += (int64_t)S->A2 * (int64_t)S->state[1];
    acc_d = (int64_t)S->A0d * (int64_t)in;
    acc_d += (int64_t)S->A1d * (int64_t)S->state[0];
    acc_d += (int64_t)S->A2d * (int64_t)S->state[1];

//	acc = (int64_t)S->A0 * (int64_t)in;
//	acc += (int64_t)S->A1 * (int64_t)S->state[0];
//	acc += (int64_t)S->A2 * (int64_t)S->state[1];

    acc += ((int64_t)S->state[2]) << 15;   // move the decimal from 1.31 to 1.46

    // acc is in 18.46 format
    // could add rounding here.
    acc = acc >> 15;
    acc_d = acc_d >> 15;

    //S->dstate[1] = S->dstate[0];
    S->dstate = ssat_i64(acc_d, 32);
    //out_d = ssat_i64(acc_d, 32);

    //S->fdstate[1] = S->fdstate[0];
    S->fdstate = (S->dstate >> 2) + S->fdstate - (S->fdstate >> 2);
    // The other algorithm uses __SSAT for 32 bit saturation
    out = ssat_i64(acc, 32);
    out += S->fdstate;
//
//	acc += ((int64_t)S->state[2]) << 15;   // move the decimal from 1.31 to 1.46
//
//	// acc is in 18.46 format
//	// could add rounding here.
//	acc = acc >> 15;
//
//	// The other algorithm uses __SSAT for 32 bit saturation
//	out = ssat_i64(acc, 32);

    // out is [-1.0, 1.0) here and in q31_t format.  In practice the effective integrator might be saturated below that value.
    // Say we wanted a 16-bit signed integer output but we wanted the gains to be somewhat readable.
    // To get 6000 from 0.170 with a Kp of 16.4u
    // Say we shift 6000<<2 to make +/-24000, that makes the gain 66u
    // Or instead we could shift the gains by how many?
    // 1/16.4u is about 15 bits
    S->state[1] = S->state[0];
    S->state[0] = in;
    S->state[2] = out;
    return out;
}


/**
 * \brief Instance structure for the iir PI controller that uses a q31_t data type.
 *
 */
typedef struct
{
    acc32_t KAp;            /**< The proportional gain. */
    acc32_t KAi;            /**< The integral gain. */
    acc32_t A0;            /**< The derived gain, A0 = Kp + Ki + Kd . */
    acc32_t A1;            /**< The derived gain, A1 = -Kp - 2Kd. */

    acc32_t B0;            /**< The derived gain for the alternative control input. */
    acc32_t B1;            /**< The derived gain for the alternative control input. */
    acc32_t KBp;           /**< The proportional gain for the alternative control input. */
    acc32_t KBi;           /**< The integral gain for the alternative control input. */

    q31_t state[2];        /**< The state array of length 3. */
} iir_pi_instance_v2_q31;


/**
 * \brief Initializes PI instance structure.
 *
 * \param S Pointer to the PI instance structure.
 * \param resetStateFlag Set this to true to clear the state buffer.
 */
void iir_pi_init_v2_q31( iir_pi_instance_v2_q31 *S, int32_t resetStateFlag);


/**
 * \brief PI process function that uses q31_t data types.
 *
 * This is an IIR implementation of a PI controller and has practical limits on the
 * accumulator and output.  Note that if the output or accumulator saturate, the PI
 * controller will behave nonlinearly.  A 64 bit accumulator is used to maintain as
 * much range as possible. Gains are given in acc32_t format.
 *
 * \param S Pointer to the PI instance structure.
 * \param in Input sample value.
 * \param b_select True if using alternative set of gains (B).
 * \return The controller output value.
 */
static inline q31_t iir_pi_v2_q31(iir_pi_instance_v2_q31 *S, q31_t in, int32_t b_select)
{
    int64_t acc;
    q31_t out;


    // So how do we pre-charge the PI controller?
    // set state[1] = out0?  Might work.

    if (!b_select) {
        // Could add some guard bits?
        // 2 bits would throw away
        // 17.15 * 1.31 => 18.46
        /* acc = A0 * x[n]  */
        acc = (int64_t)S->A0 * (int64_t)in;
        acc += (int64_t)S->A1 * (int64_t)S->state[0];
    } else {
        acc = (int64_t)S->B0 * (int64_t)in;
        acc += (int64_t)S->B1 * (int64_t)S->state[0];
    }

    acc += ((int64_t)S->state[1])<<15;   // move the decimal from 1.31 to 1.46

    // acc is in 18.46 format
    // could add rounding here.
    acc = acc >> 15;

    // The other algorithm uses __SSAT for 32 bit saturation
    out = ssat_i64(acc, 32);

    // out is [-1.0, 1.0) here and in q31_t format.  In practice the effective integrator might be saturated below that value.
    // Say we wanted a 16-bit signed integer output but we wanted the gains to be somewhat readable.
    // To get 6000 from 0.170 with a Kp of 16.4u
    // Say we shift 6000<<2 to make +/-24000, that makes the gain 66u
    // Or instead we could shift the gains by how many?
    // 1/16.4u is about 15 bits

    S->state[0] = in;
    S->state[1] = out;
    return out;
}


/**
 * \brief Instance structure for the iir PI controller that uses a q31_t data type.
 *
 */
typedef struct
{
    acc32_t KAp;            /**< The proportional gain. */
    acc32_t KAi;            /**< The integral gain. */
    acc32_t KAd;
    acc32_t A0;            /**< The derived gain, A0 = Kp + Ki + Kd . */
    acc32_t A1;            /**< The derived gain, A1 = -Kp - 2Kd. */
    acc32_t A2;

    acc32_t B0;            /**< The derived gain for the alternative control input. */
    acc32_t B1;            /**< The derived gain for the alternative control input. */
    acc32_t B2;

    acc32_t KBp;           /**< The proportional gain for the alternative control input. */
    acc32_t KBi;           /**< The integral gain for the alternative control input. */
    acc32_t KBd;

    q31_t state[3];        /**< The state array of length 3. */

    int32_t mask_count;
} iir_pid_instance_v2_q31;


/**
 * \brief Initializes PI instance structure.
 *
 * \param S Pointer to the PI instance structure.
 * \param resetStateFlag Set this to true to clear the state buffer.
 */
void iir_pid_init_v2_q31( iir_pid_instance_v2_q31 *S, int32_t resetStateFlag);


//! Defines how much the data is shifted for the iir PID controller.
#define PID_SH 4

//! Defines how much the derivative is filtered for the PID controller.
#ifdef USE_PID_V4
#define PID_FILTER_N  2
#define PID_FILTER_N2 4
#else
#define PID_FILTER_N 3
#define PID_FILTER_N2 4
#endif

/**
 * \brief PI process function that uses q31_t data types.
 *
 * This is an IIR implementation of a PI controller and has practical limits on the
 * accumulator and output.  Note that if the output or accumulator saturate, the PI
 * controller will behave nonlinearly.  A 64 bit accumulator is used to maintain as
 * much range as possible. Gains are given in acc32_t format.
 *
 * \param S Pointer to the PI instance structure.
 * \param in Input sample value.
 * \param b_select True if using alternative set of gains (B).
 * \return The controller output value.
 */
static inline q31_t iir_pid_v2_q31(iir_pid_instance_v2_q31 *S, q31_t in, int32_t b_select)
{
    int64_t acc;
    q31_t out;


    // So how do we pre-charge the PI controller?
    // set state[1] = out0?  Might work.
    if (S->mask_count > 0) {
        S->mask_count--;
        out = S->state[2];
    } else {
        if (!b_select) {
            // Could add some guard bits?
            // 2 bits would throw away
            // 17.15 * 1.31 => 18.46
            /* acc = A0 * x[n]  */
            acc = (int64_t)S->A0 * (int64_t)in;
            acc += (int64_t)S->A1 * (int64_t)S->state[0];
            acc += (int64_t)S->A2 * (int64_t)S->state[1];
        } else {
            acc = (int64_t)S->B0 * (int64_t)in;
            acc += (int64_t)S->B1 * (int64_t)S->state[0];
            acc += (int64_t)S->B2 * (int64_t)S->state[1];
        }

        acc += ((int64_t)S->state[2])<<(15+PID_SH);   // move the decimal from 1.31 to 1.46

        // acc is in 18.46 format
        // could add rounding here.
        acc = acc >> (15+PID_SH);

        // The other algorithm uses __SSAT for 32 bit saturation
        out = ssat_i64(acc, 32);
    }

    // out is [-1.0, 1.0) here and in q31_t format.  In practice the effective integrator might be saturated below that value.
    // Say we wanted a 16-bit signed integer output but we wanted the gains to be somewhat readable.
    // To get 6000 from 0.170 with a Kp of 16.4u
    // Say we shift 6000<<2 to make +/-24000, that makes the gain 66u
    // Or instead we could shift the gains by how many?
    // 1/16.4u is about 15 bits
    S->state[1] = S->state[0];
    S->state[0] = in;
    S->state[2] = out;
    return out;
}




#endif /* ARM_RT_DSP_CONTROLLER_ */