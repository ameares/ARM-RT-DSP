#include <stdio.h>
#include <stdlib.h>
#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>

// Include the header file for abs_sat_q31 function
#include "common.h"
#include "arm_rt_dsp.h" 

void test_ramp_limit_init_i16() {
    // Initialize your test variables and inputs here
    ramp_limit_i16_t test_structure = {100, 200, 20, 0}; 
    int16_t test_start_values[] = {50, 150, 250};

    // Call the function you want to test and check the structure members
    for (size_t i = 0; i < sizeof(test_start_values) / sizeof(test_start_values[0]); i++) {
        ramp_limit_init_i16(test_start_values[i], &test_structure);

        // Test the y member of the structure
        if(test_start_values[i] < test_structure.llim) {
            CU_ASSERT_EQUAL(test_structure.y, test_structure.llim);
        } else if (test_start_values[i] > test_structure.ulim) {
            CU_ASSERT_EQUAL(test_structure.y, test_structure.ulim);
        } else {
            CU_ASSERT_EQUAL(test_structure.y, test_start_values[i]);
        }
    }
}

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
    for (int i = 0; i < (int)(sizeof(test_inputs)/sizeof(test_inputs[0])); i++) {
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
    for (int i = 0; i < (int)(sizeof(test_inputs)/sizeof(test_inputs[0])); i++) {
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
    for (int i = 0; i < (int)(sizeof(test_inputs)/sizeof(test_inputs[0])); i++) {
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
    for (int i = 0; i < (int)(sizeof(test_inputs)/sizeof(test_inputs[0])); i++) {
        CU_ASSERT_EQUAL(ramp_limit_i16(test_inputs[i], &ramp), expected_outputs[i]);
    }
}


void test_ramp_limit_init_q15() {
    // Initialize your test variables and inputs here
    ramp_limit_q15_t test_structure = {100, 200, 20, 0}; 
    q15_t test_start_values[] = {50, 150, 250};

    // Call the function you want to test and check the structure members
    for (size_t i = 0; i < sizeof(test_start_values) / sizeof(test_start_values[0]); i++) {
        ramp_limit_init_q15(test_start_values[i], &test_structure);

        // Test the y member of the structure
        if(test_start_values[i] < test_structure.llim) {
            CU_ASSERT_EQUAL(test_structure.y, test_structure.llim);
        } else if (test_start_values[i] > test_structure.ulim) {
            CU_ASSERT_EQUAL(test_structure.y, test_structure.ulim);
        } else {
            CU_ASSERT_EQUAL(test_structure.y, test_start_values[i]);
        }
    }
}

void test_hysteresis_init_i16() {
    // Initialize your test variables and inputs here
    hysteresis_thresh_i16_t H;
    int16_t lower_threshold = 100;
    int16_t upper_threshold = 200;

    // Call the function you want to test
    hysteresis_init_i16(lower_threshold, upper_threshold, &H);

    // Check that the lower and upper thresholds in the structure are correctly initialized
    CU_ASSERT_EQUAL(H.hyst_off, lower_threshold);
    CU_ASSERT_EQUAL(H.hyst_on, upper_threshold);
}

void test_hysteresis_threshold_i16() {
    // Initialize your test variables and inputs here
    hysteresis_thresh_i16_t H = {200, 100, 0}; 
    int16_t test_values[] = {50, 150, 250};

    // Call the function you want to test and check the structure members
    for (size_t i = 0; i < sizeof(test_values) / sizeof(test_values[0]); i++) {
        int32_t output_state = hysteresis_threshold_i16(test_values[i], &H);

        // Test the output state
        if(test_values[i] > H.hyst_on) {
            CU_ASSERT_EQUAL(output_state, 0x01);
            CU_ASSERT_EQUAL(H.out_state, 0x01);
        } else if (test_values[i] < H.hyst_off) {
            CU_ASSERT_EQUAL(output_state, 0x00);
            CU_ASSERT_EQUAL(H.out_state, 0x00);
        } else {
            // If the input value is between the thresholds, the output state should remain the same.
            CU_ASSERT_EQUAL(output_state, H.out_state);
        }
    }
}


void test_hysteresis_init() {
    // Initialize your test variables and inputs here
    hysteresis_thresh_t H;
    q31_t lower_threshold = 100;
    q31_t upper_threshold = 200;

    // Call the function you want to test
    hysteresis_init(lower_threshold, upper_threshold, &H);

    // Check that the lower and upper thresholds in the structure are correctly initialized
    CU_ASSERT_EQUAL(H.hyst_off, lower_threshold);
    CU_ASSERT_EQUAL(H.hyst_on, upper_threshold);
}

void test_hysteresis_threshold() {
    // Initialize your test variables and inputs here
    hysteresis_thresh_t H = {200, 100, 0}; 
    q31_t test_values[] = {50, 150, 250};

    // Call the function you want to test and check the structure members
    for (size_t i = 0; i < sizeof(test_values) / sizeof(test_values[0]); i++) {
        int32_t output_state = hysteresis_threshold(test_values[i], &H);

        // Test the output state
        if(test_values[i] > H.hyst_on) {
            CU_ASSERT_EQUAL(output_state, 0x01);
            CU_ASSERT_EQUAL(H.out_state, 0x01);
        } else if (test_values[i] < H.hyst_off) {
            CU_ASSERT_EQUAL(output_state, 0x00);
            CU_ASSERT_EQUAL(H.out_state, 0x00);
        } else {
            // If the input value is between the thresholds, the output state should remain the same.
            CU_ASSERT_EQUAL(output_state, H.out_state);
        }
    }
}

void test_ramp_init_q31() {
    // Initialize your test variables and inputs here
    ramp_q31_t r;
    q31_t y0 = 100;

    // Call the function you want to test
    ramp_init_q31(y0, &r);

    // Check that the y in the structure is correctly initialized
    CU_ASSERT_EQUAL(r.y, y0);
}

void test_ramp_q31() {
    // Initialize your test variables and inputs here
    ramp_q31_t r = {10, 0}; // Increment by 10 each time
    q31_t target_values[] = {50, 60, 70, 80, 90, 100};

    // Call the function you want to test and check the output
    for (size_t i = 0; i < sizeof(target_values) / sizeof(target_values[0]); i++) {
        q31_t output = ramp_q31(target_values[i], &r);

        // The ramp function should approach the target value at the increment rate
        // Therefore, the expected output should be (i + 1) * r.inc 
        q31_t expected_output = (i + 1) * r.inc;

        CU_ASSERT_EQUAL(output, expected_output);
        CU_ASSERT_EQUAL(r.y, expected_output);
    }
}

void test_check_delta_q31() {
    // Define some test variables
    q31_t nominal = 0;
    q31_t delta = 100;
    q31_t input_values[] = {50, 200};
    int32_t expected_results[] = {1, 0};
    int num_tests = sizeof(input_values) / sizeof(q31_t);

    // Test if function returns expected results
    for(int i = 0; i < num_tests; ++i) {
        CU_ASSERT_EQUAL(check_delta_q31(input_values[i], nominal, delta), expected_results[i]);
    }
}

void test_check_delta_f32() {
    // Define some test variables
    float32_t nominal = 0.0f;
    float32_t delta = 0.1f;
    float32_t input_values[] = {0.05f, 0.2f};
    int32_t expected_results[] = {1, 0};
    int num_tests = sizeof(input_values) / sizeof(float32_t);

    // Test if function returns expected results
    for(int i = 0; i < num_tests; ++i) {
        CU_ASSERT_EQUAL(check_delta_f32(input_values[i], nominal, delta), expected_results[i]);
    }
}