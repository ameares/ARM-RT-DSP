
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