/**
 * \file arm_rt_dsp.c
 * \brief Real-time DSP functions.
*/
#include <stdint.h>
#include "arm_rt_dsp.h"


/*-----------------------------------------------------------------------------
History:

Notes:

-----------------------------------------------------------------------------*/
void ramp_limit_init_i16(int16_t y0, ramp_limit_i16_t *r) {
    // Sets the starting value to between the lower limit and the upper limit.
    if (y0 < r->llim) {
        r->y = r->llim;
    } else if (y0 > r->ulim) {
        r->y = r->ulim;
    } else {
        r->y = y0;
    }
}


/*-----------------------------------------------------------------------------
History:

Notes:
This does not saturate.
-----------------------------------------------------------------------------*/
int16_t ramp_limit_i16(int16_t x, ramp_limit_i16_t *r) {
    int32_t delta = 0;
 
    delta = x - r->y;

    // inc is the limit of speed of movement from one number to the next.
    // Lets just do this the verbose way first.
    if (delta > r->inc) {
        delta = r->inc;
    } else if (delta < (0-r->inc)) {
        delta = 0 - r->inc;
    }

    r->y += delta;

    // Sets the return value to between the lower limit and the upper limit.
    if (r->y < r->llim) {
        r->y = r->llim;
    } else if (r->y > r->ulim) {
        r->y = r->ulim;
    }

    return r->y;
}


/*-----------------------------------------------------------------------------
History:

Notes:

-----------------------------------------------------------------------------*/
void ramp_limit_init_q15(q15_t y0, ramp_limit_q15_t *r) {
    // Sets the starting value to between the lower limit and the upper limit.
    if (y0 < r->llim) {
        r->y = r->llim;
    } else if (y0 > r->ulim) {
        r->y = r->ulim;
    } else {
        r->y = y0;
    }
}


/*-----------------------------------------------------------------------------
History:

Notes:
This does not saturate.
-----------------------------------------------------------------------------*/
q15_t ramp_limit_q15(q15_t x, ramp_limit_q15_t *r) {
    int32_t delta = 0;

    delta = x - r->y;

    // inc is the limit of speed of movement from one number to the next.
    // Lets just do this the verbose way first.
    if (delta > r->inc) {
        delta = r->inc;
    } else if (delta < (0-r->inc)) {
        delta = 0 - r->inc;
    }

    r->y += delta;

    // Sets the return value to between the lower limit and the upper limit.
    if (r->y < r->llim) {
        r->y = r->llim;
    } else if (r->y > r->ulim) {
        r->y = r->ulim;
    }

    return r->y;
}


/*-----------------------------------------------------------------------------
History:

Notes:

-----------------------------------------------------------------------------*/
void ramp_init_q31(q31_t y0, ramp_q31_t *r) {
    r->y = y0;
}


/*-----------------------------------------------------------------------------
History:

Notes:
This saturates and uses the full range.
-----------------------------------------------------------------------------*/
q31_t ramp_q31(q31_t x, ramp_q31_t *r) {
    q31_t result = 0;

    result = r->y;
    if (x > r->y)
    {
        // If desired > actual
        // The algorithm adds the rampUp to actual
        result = __QADD(r->y, r->inc);
        if (result > x)           /* If it overshoots */
        {
            result = x;           /* it uses the desired */
        }
    } else if (x < r->y)  /* If desired < actual */
    {
        /* The algorithm subtracts the rampDown from actual */
        result = __QSUB(r->y, r->inc);
        if (result < x)           /* If it undershoots */
        {
            result = x;           /* it uses the desired */
        }
    }
    // Does it really need to even check this state? AM
    //if (x == r->y)
    //{
    //    result = x;
    //}
    r->y = result;
    return result;
}


/*-----------------------------------------------------------------------------
History:

Notes:

-----------------------------------------------------------------------------*/
void hysteresis_init(q31_t l_thresh, q31_t h_thresh, hysteresis_thresh_t *H) {
    H->hyst_off = l_thresh;
    H->hyst_on = h_thresh;
    H->out_state = 0;
}


/*-----------------------------------------------------------------------------
History:

Notes:

-----------------------------------------------------------------------------*/
void hysteresis_init_i16(int16_t l_thresh, int16_t h_thresh, hysteresis_thresh_i16_t *H) {
    H->hyst_off = l_thresh;
    H->hyst_on = h_thresh;
    H->out_state = 0;
}



/*-----------------------------------------------------------------------------
History:

Notes:

-----------------------------------------------------------------------------*/
void iir_pi_init_q15(iir_pi_instance_q15 * S, int32_t resetStateFlag) {

  // Derived coefficient A0
  // QADD16 is a q-setting dual saturating operation.
  S->A0 = __QADD16(S->Kp, S->Ki);
  // Note Kp is strictly > 0
  S->A1 = __QSUB16(0, S->Kp);

  // Check whether state needs reset or not
  if (resetStateFlag)
  {
    // Clear the state buffer.  The size will be always 2 samples
    memset(S->state, 0, PI_Q15_STATE_BUFFER_SIZE * sizeof(q15_t));
  }

}


/*-----------------------------------------------------------------------------
History:

Notes:

-----------------------------------------------------------------------------*/
void iir_pi_init_q31( iir_pi_instance_q31 *S, int32_t resetStateFlag)
{
  /* Run the below code for Cortex-M4 and Cortex-M3 */

  /* Derived coefficient A0 */
  S->A0 = __QADD(S->Kp, S->Ki);

  /* Derived coefficient A1 */
  S->A1 = 0 - S->Kp;

  /* Check whether state needs reset or not */
  if (resetStateFlag)
  {
    /* Clear the state buffer.  The size will be always 2 samples */
    memset(S->state, 0, PI_Q31_STATE_BUFFER_SIZE * sizeof(q31_t));
  }

}


/*-----------------------------------------------------------------------------
History:

Notes:

-----------------------------------------------------------------------------*/
void iir_pid_init_q31( iir_pid_instance_q31 *S, int32_t resetStateFlag)
{
  /* Run the below code for Cortex-M4 and Cortex-M3 */

  /* Derived coefficient A0 */
  //S->A0 = __QADD(__QADD(S->KAp, S->KAi), S->KAd);
  S->A0 = __QADD(S->Kp, S->Ki);
  S->A0d = S->Kd;

  /* Derived coefficient A1 */
  //S->A1 = 0 - S->KAp - S->KAd - S->KAd; //<<1);
  S->A1 = 0 - S->Kp;
  S->A1d = 0 - S->Kd - S->Kd;

  //S->A2 = S->KAd;
  S->A2d = S->Kd;

  /* Check whether state needs reset or not */
  if (resetStateFlag)
  {
    /* Clear the state buffer.  The size will be always 2 samples */
    memset(S->state, 0, PID_Q31_STATE_BUFFER_SIZE * sizeof(q31_t));
    S->dstate = 0;
    S->fdstate = 0;
  }

}


/*-----------------------------------------------------------------------------
History:

Notes:

-----------------------------------------------------------------------------*/
void iir_pi_init_v2_q31( iir_pi_instance_v2_q31 *S, int32_t resetStateFlag)
{
  /* Run the below code for Cortex-M4 and Cortex-M3 */

  /* Derived coefficient A0 */
  S->A0 = __QADD(S->KAp, S->KAi);

  /* Derived coefficient A1 */
  S->A1 = 0 - S->KAp;

  /* Derived coefficient A0 */
  S->B0 = __QADD(S->KBp, S->KBi);

  /* Derived coefficient A1 */
  S->B1 = 0 - S->KBp;

  /* Check whether state needs reset or not */
  if (resetStateFlag)
  {
    /* Clear the state buffer.  The size will be always 2 samples */
    memset(S->state, 0, 2U * sizeof(q31_t));
  }

}


/*-----------------------------------------------------------------------------
History:

Notes:
Could use some work on the saturated add/subtract.

-----------------------------------------------------------------------------*/
void iir_pid_init_v2_q31( iir_pid_instance_v2_q31 *S, int32_t resetStateFlag)
{
  /* Run the below code for Cortex-M4 and Cortex-M3 */

  /* Derived coefficient A0 */
  S->A0 = __QADD(__QADD(S->KAp, S->KAi), S->KAd);

  /* Derived coefficient A1 */
  S->A1 = 0 - S->KAp - S->KAd - S->KAd; //<<1);

  S->A2 = S->KAd;

  /* Derived coefficient B0 */
  S->B0 = __QADD(__QADD(S->KBp, S->KBi), S->KBd);

  /* Derived coefficient B1 */
  S->B1 = 0 - S->KBp - S->KBd - S->KBd; //<<1);

  S->B2 = S->KBd;

  /* Check whether state needs reset or not */
  if (resetStateFlag)
  {
    /* Clear the state buffer.  The size will be always 2 samples */
    memset(S->state, 0, 3U * sizeof(q31_t));
  }

  S->mask_count = 0;

}
