#include <stdio.h>
#include <stdlib.h>
#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>

// Include the header file for abs_sat_q31 function
#include "common.h"
#include "arm_rt_dsp.h" 


// Tests for ramp_limit_i16
// Test case 1: ramp_limit_i16 demonstrates a basic ramp.
void test_ramp_limit_i16_pos(void) {
    ramp_limit_i16_t ramp;
    int16_t test_inputs[] = {0, 2, 10, 10, 10, 10};
    int16_t expected_outputs[] = {0, 2, 4, 6, 8, 10};

    // Initialize the ramp
    ramp.llim = 0;
    ramp.ulim = 1000;
    ramp.inc = 2;
    ramp_limit_init_i16(0, &ramp);

    // Test ramp_limit_i16 for each input
    for (int i = 0; i < sizeof(test_inputs)/sizeof(test_inputs[0]); i++) {
        CU_ASSERT_EQUAL(ramp_limit_i16(test_inputs[i], &ramp), expected_outputs[i]);
    }
}

// Test case 2: ramp_limit_i16 demonstrates a ramp with a negative increment.
void test_ramp_limit_i16_neg(void) {
    ramp_limit_i16_t ramp;
    int16_t test_inputs[] = {0, 2, 10, 10, 10, 10};
    int16_t expected_outputs[] = {0, -2, -4, -6, -8, -10};

    // Initialize the ramp
    ramp.llim = -1000;
    ramp.ulim = 0;
    ramp.inc = -2;
    ramp_limit_init_i16(0, &ramp);

    // Test ramp_limit_i16 for each input
    for (int i = 0; i < sizeof(test_inputs)/sizeof(test_inputs[0]); i++) {
        CU_ASSERT_EQUAL(ramp_limit_i16(test_inputs[i], &ramp), expected_outputs[i]);
    }
}

// Test case 3: ramp_limit_i16 demonstrates operation at the upper limit, ulim.
void test_ramp_limit_i16_ulim(void) {
    ramp_limit_i16_t ramp;
    int16_t test_inputs[] = {0, 2, 12, 12, 12, 12, 12};
    int16_t expected_outputs[] = {0, 2, 4, 6, 8, 10, 10};

    // Initialize the ramp
    ramp.llim = 0;
    ramp.ulim = 10;
    ramp.inc = 2;
    ramp_limit_init_i16(0, &ramp);

    // Test ramp_limit_i16 for each input
    for (int i = 0; i < sizeof(test_inputs)/sizeof(test_inputs[0]); i++) {
        CU_ASSERT_EQUAL(ramp_limit_i16(test_inputs[i], &ramp), expected_outputs[i]);
    }
}

// Test case 4: ramp_limit_i16 demonstrates operation at the lower limit, llim.
void test_ramp_limit_i16_llim(void) {
    ramp_limit_i16_t ramp;
    int16_t test_inputs[] = {0, 2, -12, -12, -12, -12, -12};
    int16_t expected_outputs[] = {0, 2, 4, 6, 8, 10, 10};

    // Initialize the ramp
    ramp.llim = -10;
    ramp.ulim = 0;
    ramp.inc = 2;
    ramp_limit_init_i16(0, &ramp);

    // Test ramp_limit_i16 for each input
    for (int i = 0; i < sizeof(test_inputs)/sizeof(test_inputs[0]); i++) {
        CU_ASSERT_EQUAL(ramp_limit_i16(test_inputs[i], &ramp), expected_outputs[i]);
    }
}
