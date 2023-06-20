#include <stdio.h>
#include <stdlib.h>
#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>

// Include the header file for abs_sat_q31 function
#include "common.h"
#include "arm_rt_dsp.h" 


void test_abs_q15() {
    // Initialize your test variables and inputs here
    q15_t test_inputs[] = {Q15(-1.0), Q15(0.5), Q15(-0.5), 0x7FFF, 0x7FFE, -0x8000};
    q15_t expected_outputs[] = {Q15(1.0), Q15(0.5), Q15(0.5), 0x7FFF, 0x7FFE, 0x8000};
    int num_tests = sizeof(test_inputs) / sizeof(test_inputs[0]);

    // Call the function you want to test and check its output.
    for (int i = 0; i < num_tests; i++) {
        // Prepare inputs.
        q15_t input = test_inputs[i];
        q15_t expected_output = expected_outputs[i];

        // Make calls to CU_ASSERT or CU_ASSERT_EQUAL.
        CU_ASSERT_EQUAL(abs_q15(input), expected_output);

        // Add more assertions or complex logic as needed.
    }
    
    // Add more test cases if necessary.
}


void test_abs_q31() {
    // test with negative input
    q31_t input1 = -0x7FFFFFFF;
    CU_ASSERT(abs_q31(input1) == 0x7FFFFFFF);

    // test with positive input
    q31_t input2 = 0x7FFFFFFF;
    CU_ASSERT(abs_q31(input2) == 0x7FFFFFFF);

    // test with zero
    q31_t input3 = 0;
    CU_ASSERT(abs_q31(input3) == 0);
}

void test_abs_sat_q15() {
    // Initialize your test variables and inputs here
    q15_t test_data[] = {0, 1, -1, Q15(1.0), Q15(-1.0), Q15(0.5), Q15(-0.5), 0x7FFF, 0x8000};
    q15_t expected_results[] = {0, 1, 1, 0x7FFF, 0x7FFF, Q15(0.5), Q15(0.5), 0x7FFF, 0x7FFF};

    // Call the function you want to test and check its output.
    for (size_t i = 0; i < sizeof(test_data) / sizeof(test_data[0]); i++) {
        // Prepare inputs.
        q15_t input = test_data[i];
        q15_t expected = expected_results[i];

        // Make calls to CU_ASSERT or CU_ASSERT_EQUAL.
        CU_ASSERT_EQUAL(abs_sat_q15(input), expected);
    }

    // Add more assertions or complex logic as needed.
    // Placeholder for additional test cases if required.
}


void test_abs_sat_q31() {
    // Initialize your test variables and inputs here
    q31_t test_data[] = {0, 1, -1, Q31(1.0), Q31(-1.0), Q31(0.5), Q31(-0.5), 0x7FFFFFFF, 0x80000000};
    q31_t expected_results[] = {0, 1, 1, 0x7FFFFFFF, 0x7FFFFFFF, Q31(0.5), Q31(0.5), 0x7FFFFFFF, 0x7FFFFFFF};

    // Call the function you want to test and check its output.
    for (size_t i = 0; i < sizeof(test_data) / sizeof(test_data[0]); i++) {
        // Prepare inputs.
        q31_t input = test_data[i];
        q31_t expected = expected_results[i];

        // Make calls to CU_ASSERT or CU_ASSERT_EQUAL.
        CU_ASSERT_EQUAL(abs_sat_q31(input), expected);
    }

    // Add more assertions or complex logic as needed.
    // Placeholder for additional test cases if required.
}



#if 0
void test_ssat_i64() {
    // test positive overflow
    CU_ASSERT(ssat_i64(0x8000000000000000, 63) == 0x3FFFFFFFFFFFFFFF);

    // test negative overflow
    CU_ASSERT(ssat_i64(-0x8000000000000001, 63) == -0x4000000000000000);

    // test no saturation
    CU_ASSERT(ssat_i64(0x7FFFFFFFFFFFFFFF, 63) == 0x7FFFFFFFFFFFFFFF);
}
#endif


void test_mul_q15() {
    // Initialize your test variables and inputs here
    q15_t test_data_x[] = {0, 1, -1, Q15(1.0), Q15(-1.0), Q15(0.5), Q15(-0.5), 0x7FFF, 0x8000};
    q15_t test_data_y[] = {1, -1, Q15(1.0), Q15(-1.0), Q15(0.5), Q15(-0.5), 0x7FFF, 0x8000, 0};
    q15_t expected_results[] = {0, -1, -0x7FFF, 0x7FFF, Q15(0.5), -Q15(0.5), -0x7FFF, 0x7FFF, 0};

    // Call the function you want to test and check its output.
    for (size_t i = 0; i < sizeof(test_data_x) / sizeof(test_data_x[0]); i++) {
        // Prepare inputs.
        q15_t input_x = test_data_x[i];
        q15_t input_y = test_data_y[i];
        q15_t expected = expected_results[i];

        // Make calls to CU_ASSERT or CU_ASSERT_EQUAL.
        CU_ASSERT_EQUAL(mul_q15(input_x, input_y), expected);
    }

    // Add more assertions or complex logic as needed.
    // Placeholder for additional test cases if required.
}


void test_mul_q31() {
    // Initialize your test variables and inputs here
    q31_t test_data_x[] = {0, 1, -1, Q31(1.0), Q31(-1.0), Q31(0.5), Q31(-0.5), 0x7FFFFFFF, 0x80000000};
    q31_t test_data_y[] = {1, -1, Q31(1.0), Q31(-1.0), Q31(0.5), Q31(-0.5), 0x7FFFFFFF, 0x80000000, 0};
    q31_t expected_results[] = {0, -1, -0x7FFFFFFF, 0x7FFFFFFF, Q31(0.5), -Q31(0.5), -0x7FFFFFFF, 0x7FFFFFFF, 0};

    // Call the function you want to test and check its output.
    for (size_t i = 0; i < sizeof(test_data_x) / sizeof(test_data_x[0]); i++) {
        // Prepare inputs.
        q31_t input_x = test_data_x[i];
        q31_t input_y = test_data_y[i];
        q31_t expected = expected_results[i];

        // Make calls to CU_ASSERT or CU_ASSERT_EQUAL.
        CU_ASSERT_EQUAL(mul_q31(input_x, input_y), expected);
    }

    // Add more assertions or complex logic as needed.
    // Placeholder for additional test cases if required.
}

void test_mulsat_q15() {
    // test positive * positive
    q15_t input1 = 0x7FFF;
    q15_t input2 = 0x7FFF;
    CU_ASSERT(mulsat_q15(input1, input2) == 0x7FFE);

    // test positive * negative
    input2 = -input2;
    q15_t result = mulsat_q15(input1, input2);
    //printf("Result of the test: %d\n", result);
    CU_ASSERT(result == -0x8000);   // Or should it be -0x7FFE, -0x7FFF?, this is a deep dive that is needed. AM 5/14/23

    // test with zero
    input2 = 0;
    CU_ASSERT(mulsat_q15(input1, input2) == 0);
}


void test_mulsat_q31() {
    // test positive * positive
    q31_t input1 = 0x7FFFFFFF;
    q31_t input2 = 0x7FFFFFFF;
    CU_ASSERT(mulsat_q31(input1, input2) == 0x7FFFFFFE);

    // test positive * negative
    // This one needs work. Results values are wrong. AM 5/21/2023
    input2 = -input2;
    CU_ASSERT(mulsat_q31(input1, input2) == -0x7FFFFFFE);

    // test with zero
    input2 = 0;
    CU_ASSERT(mulsat_q31(input1, input2) == 0);
}


void test_max_q31() {
    // Initialize your test variables and inputs here
    q31_t test_data_x[] = {0, 1, -1, Q31(1.0), Q31(-1.0), Q31(0.5), Q31(-0.5), 0x7FFFFFFF, 0x80000000};
    q31_t test_data_y[] = {1, -1, Q31(1.0), Q31(-1.0), Q31(0.5), Q31(-0.5), 0x7FFFFFFF, 0x80000000, 0};
    q31_t expected_results[] = {1, 1, Q31(1.0), Q31(1.0), Q31(0.5), Q31(0.5), 0x7FFFFFFF, 0x7FFFFFFF, 0};

    // Call the function you want to test and check its output.
    for (size_t i = 0; i < sizeof(test_data_x) / sizeof(test_data_x[0]); i++) {
        // Prepare inputs.
        q31_t input_x = test_data_x[i];
        q31_t input_y = test_data_y[i];
        q31_t expected = expected_results[i];

        // Make calls to CU_ASSERT or CU_ASSERT_EQUAL.
        CU_ASSERT_EQUAL(max_q31(input_x, input_y), expected);
    }
}

void test_min_q31() {
    // Initialize your test variables and inputs here
    q31_t test_data_x[] = {0, 1, -1, Q31(1.0), Q31(-1.0), Q31(0.5), Q31(-0.5), 0x7FFFFFFF, 0x80000000};
    q31_t test_data_y[] = {1, -1, Q31(1.0), Q31(-1.0), Q31(0.5), Q31(-0.5), 0x7FFFFFFF, 0x80000000, 0};
    q31_t expected_results[] = {0, -1, -1, Q31(-1.0), Q31(-1.0), -Q31(0.5), -Q31(0.5), 0x80000000, 0};

    // Call the function you want to test and check its output.
    for (size_t i = 0; i < sizeof(test_data_x) / sizeof(test_data_x[0]); i++) {
        // Prepare inputs.
        q31_t input_x = test_data_x[i];
        q31_t input_y = test_data_y[i];
        q31_t expected = expected_results[i];

        // Make calls to CU_ASSERT or CU_ASSERT_EQUAL.
        CU_ASSERT_EQUAL(min_q31(input_x, input_y), expected);
    }
}

void test_adc_process_sample_q15() {
    uint16_t raw_value[] = {0, 4095, 2048, 1024};
    int16_t offset[] = {0, 0, 2048, 1024};
    q15_t slope[] = {Q15(1.0), Q15(0.5), Q15(-0.5), Q15(0.25)};
    q15_t expected[] = {0, 0, 0, 0};

    for (size_t i = 0; i < sizeof(raw_value) / sizeof(raw_value[0]); i++) {
        CU_ASSERT_EQUAL(adc_process_sample_q15(raw_value[i], offset[i], slope[i]), expected[i]);
    }
}

void test_adc_process_sample_q31() {
    uint16_t raw_value[] = {0, 4095, 2048, 1024};
    int16_t offset[] = {0, 0, 2048, 1024};
    q31_t slope[] = {Q31(1.0), Q31(0.5), Q31(-0.5), Q31(0.25)};
    q31_t expected[] = {0, 0, 0, 0};

    for (size_t i = 0; i < sizeof(raw_value) / sizeof(raw_value[0]); i++) {
        CU_ASSERT_EQUAL(adc_process_sample_q31(raw_value[i], offset[i], slope[i]), expected[i]);
    }
}

void test_adc_process_sample_u_q31() {
    uint16_t raw_value[] = {0, 4095, 2048, 1024};
    int16_t offset[] = {0, 0, 2048, 1024};
    q31_t slope[] = {Q31(1.0), Q31(0.5), Q31(-0.5), Q31(0.25)};
    q31_t expected[] = {0, 0, 0, 0};

    for (size_t i = 0; i < sizeof(raw_value) / sizeof(raw_value[0]); i++) {
        CU_ASSERT_EQUAL(adc_process_sample_u_q31(raw_value[i], offset[i], slope[i]), expected[i]);
    }
}

void test_adc_process_sample_i16_q31() {
    int16_t raw_value[] = {0, 2047, -2048, 1024, -1024};
    int16_t offset[] = {0, 0, -2048, 1024, -1024};
    q31_t slope[] = {Q31(1.0), Q31(0.5), Q31(-0.5), Q31(0.25), Q31(-0.25)};
    q31_t expected[] = {0, 0, 0, 0, 0};

    for (size_t i = 0; i < sizeof(raw_value) / sizeof(raw_value[0]); i++) {
        CU_ASSERT_EQUAL(adc_process_sample_i16_q31(raw_value[i], offset[i], slope[i]), expected[i]);
    }
}

void test_limit_f32() {
    // Initialize your test variables and inputs here
    float test_data[] = {-2.0f, -1.0f, 0.0f, 1.0f, 2.0f};
    float lower_limit = -1.0f;
    float upper_limit = 1.0f;
    float expected[] = {-1.0f, -1.0f, 0.0f, 1.0f, 1.0f};

    // Call the function you want to test and check its output.
    for (size_t i = 0; i < sizeof(test_data) / sizeof(test_data[0]); i++) {
        // Make calls to CU_ASSERT or CU_ASSERT_EQUAL.
        CU_ASSERT_EQUAL(limit_f32(test_data[i], lower_limit, upper_limit), expected[i]);
    }
}

void test_upper_limit_q31() {
    // Initialize your test variables and inputs here
    q31_t test_data[] = {Q31(-2.0), Q31(-1.0), Q31(0.0), Q31(1.0), Q31(2.0)};
    q31_t upper_limit = Q31(1.0);
    q31_t expected[] = {Q31(-2.0), Q31(-1.0), Q31(0.0), Q31(1.0), Q31(1.0)};

    // Call the function you want to test and check its output.
    for (size_t i = 0; i < sizeof(test_data) / sizeof(test_data[0]); i++) {
        // Make calls to CU_ASSERT or CU_ASSERT_EQUAL.
        CU_ASSERT_EQUAL(upper_limit_q31(test_data[i], upper_limit), expected[i]);
    }
}

void test_lower_limit_q31() {
    // Initialize your test variables and inputs here
    q31_t test_data[] = {Q31(-2.0), Q31(-1.0), Q31(0.0), Q31(1.0), Q31(2.0)};
    q31_t lower_limit = Q31(-1.0);
    q31_t expected[] = {Q31(-1.0), Q31(-1.0), Q31(0.0), Q31(1.0), Q31(2.0)};

    // Call the function you want to test and check its output.
    for (size_t i = 0; i < sizeof(test_data) / sizeof(test_data[0]); i++) {
        // Make calls to CU_ASSERT or CU_ASSERT_EQUAL.
        CU_ASSERT_EQUAL(lower_limit_q31(test_data[i], lower_limit), expected[i]);
    }
}

void test_limit_q31() {
    // Initialize your test variables and inputs here
    q31_t test_data[] = {Q31(-2.0), Q31(-1.0), Q31(0.0), Q31(1.0), Q31(2.0)};
    q31_t lower_limit = Q31(-1.0);
    q31_t upper_limit = Q31(1.0);
    q31_t expected[] = {Q31(-1.0), Q31(-1.0), Q31(0.0), Q31(1.0), Q31(1.0)};

    // Call the function you want to test and check its output.
    for (size_t i = 0; i < sizeof(test_data) / sizeof(test_data[0]); i++) {
        // Make calls to CU_ASSERT or CU_ASSERT_EQUAL.
        CU_ASSERT_EQUAL(limit_q31(test_data[i], lower_limit, upper_limit), expected[i]);
    }
}

void test_limit_i32() {
    // Initialize your test variables and inputs here
    int32_t test_data[] = {INT32_MIN, -100, 0, 100, INT32_MAX};
    int32_t lower_limit = -1;
    int32_t upper_limit = 1;
    int32_t expected[] = {-1, -1, 0, 1, 1};

    // Call the function you want to test and check its output.
    for (size_t i = 0; i < sizeof(test_data) / sizeof(test_data[0]); i++) {
        // Make calls to CU_ASSERT or CU_ASSERT_EQUAL.
        CU_ASSERT_EQUAL(limit_i32(test_data[i], lower_limit, upper_limit), expected[i]);
    }
}

void test_limit_u32() {
    // Initialize your test variables and inputs here
    uint32_t test_data[] = {0, 100, 200, 300, UINT32_MAX};
    uint32_t lower_limit = 100;
    uint32_t upper_limit = 200;
    uint32_t expected[] = {100, 100, 200, 200, 200};

    // Call the function you want to test and check its output.
    for (size_t i = 0; i < sizeof(test_data) / sizeof(test_data[0]); i++) {
        // Make calls to CU_ASSERT or CU_ASSERT_EQUAL.
        CU_ASSERT_EQUAL(limit_u32(test_data[i], lower_limit, upper_limit), expected[i]);
    }
}

void test_limit_i16() {
    // Initialize your test variables and inputs here
    int16_t test_data[] = {INT16_MIN, -10, 0, 10, INT16_MAX};
    int16_t lower_limit = -5;
    int16_t upper_limit = 5;
    int16_t expected[] = {-5, -5, 0, 5, 5};

    // Call the function you want to test and check its output.
    for (size_t i = 0; i < sizeof(test_data) / sizeof(test_data[0]); i++) {
        // Make calls to CU_ASSERT or CU_ASSERT_EQUAL.
        CU_ASSERT_EQUAL(limit_i16(test_data[i], lower_limit, upper_limit), expected[i]);
    }
}


void test_limit_u16() {
    // Initialize your test variables and inputs here
    uint16_t test_data[] = {0, 50, 100, 150, UINT16_MAX};
    uint16_t lower_limit = 50;
    uint16_t upper_limit = 100;
    uint16_t expected[] = {50, 50, 100, 100, 100};

    // Call the function you want to test and check its output.
    for (size_t i = 0; i < sizeof(test_data) / sizeof(test_data[0]); i++) {
        // Make calls to CU_ASSERT or CU_ASSERT_EQUAL.
        CU_ASSERT_EQUAL(limit_u16(test_data[i], lower_limit, upper_limit), expected[i]);
    }
}


void test_upper_limit_u16() {
    // Initialize your test variables and inputs here
    uint16_t test_data[] = {0, 1000, 2000, 3000, 5000, UINT16_MAX};
    uint16_t upper_limit = 4000;
    uint16_t expected[] = {0, 1000, 2000, 3000, 4000, 4000};

    // Call the function you want to test and check its output.
    for (size_t i = 0; i < sizeof(test_data) / sizeof(test_data[0]); i++) {
        // Make calls to CU_ASSERT or CU_ASSERT_EQUAL.
        CU_ASSERT_EQUAL(upper_limit_u16(test_data[i], upper_limit), expected[i]);
    }
}