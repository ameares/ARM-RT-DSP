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
    input2 = -input2;
    CU_ASSERT(mulsat_q31(input1, input2) == -0x80000000);   // Or should it be -0x7FFFFFFE?

    // test with zero
    input2 = 0;
    CU_ASSERT(mulsat_q31(input1, input2) == 0);
}