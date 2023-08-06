#include <stdio.h>
#include <stdlib.h>
#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>

// Include the header file for abs_sat_q31 function
#include "common.h"
#include "arm_rt_dsp.h" 

void test_abs_q15();
void test_abs_q31();
void test_abs_sat_q15();
void test_abs_sat_q31();
void test_ssat_i64();
void test_mul_q15();
void test_mul_q31();
void test_mulsat_q15();
void test_mulsat_q31();
void test_min_q31();
void test_max_q31();
void test_adc_process_sample_q15();
void test_adc_process_sample_q31();
void test_adc_process_sample_u_q31();
void test_adc_process_sample_i16_q31();
void test_limit_f32();
void test_upper_limit_q31();
void test_lower_limit_q31();
void test_limit_i32();
void test_limit_q31();
void test_limit_u32();
void test_limit_i16();
void test_limit_u16();
void test_upper_limit_u16();

void test_ramp_limit_init_i16();
void test_ramp_limit_i16_pos(void);
void test_ramp_limit_i16_neg(void);
void test_ramp_limit_i16_ulim(void);
void test_ramp_limit_i16_llim(void);
void test_ramp_limit_init_q15();
void test_hysteresis_init_i16();
void test_hysteresis_threshold_i16();
void test_hysteresis_init();
void test_hysteresis_threshold();
void test_ramp_init_q31();
void test_ramp_q31();
void test_check_delta_q31();
void test_check_delta_f32();

void test_sequence_limit_i16(void);

void test_sequence_iir_pi_q15(void);

// Test functions for each suite
Test suite1_tests[] = {
    {"test_abs_q15", test_abs_q15},
    {"test_abs_q31", test_abs_q31},
    {"test_abs_sat_q15", test_abs_sat_q15},
    {"test_abs_sat_q31", test_abs_sat_q31},
    {"test_mul_q15", test_mul_q15},
    {"test_mul_q31", test_mul_q31},
    {"test_mulsat_q15", test_mulsat_q15},
    {"test_mulsat_q31", test_mulsat_q31},
    {"test_min_q31", test_min_q31},
    {"test_max_q31", test_max_q31},
    {"test_limit_f32", test_limit_f32},
    {"test_upper_limit_q31", test_upper_limit_q31},
    {"test_lower_limit_q31", test_lower_limit_q31},
    {"test_limit_q31", test_limit_q31},
    {"test_limit_i32", test_limit_i32},
    {"test_limit_u32", test_limit_u32},
    {"test_limit_i16", test_limit_i16},
    {"test_limit_u16", test_limit_u16},
    {"test_upper_limit_u16", test_upper_limit_u16},
    // Add more tests here as needed
};

Test suite2_tests[] = {
    {"test_ramp_limit_init_i16", test_ramp_limit_init_i16},
    {"test_ramp_limit_i16_pos", test_ramp_limit_i16_pos},
    {"test_ramp_limit_i16_neg", test_ramp_limit_i16_neg},
    {"test_ramp_limit_i16_ulim", test_ramp_limit_i16_ulim},
    {"test_ramp_limit_i16_llim", test_ramp_limit_i16_llim},
    {"test_ramp_limit_init_q15", test_ramp_limit_init_q15},
    {"test_hysteresis_init_i16", test_hysteresis_init_i16},
    {"test_hysteresis_threshold_i16", test_hysteresis_threshold_i16},
    {"test_hysteresis_init", test_hysteresis_init},
    {"test_hysteresis_threshold", test_hysteresis_threshold},
    {"test_ramp_init_q31", test_ramp_init_q31},
    {"test_ramp_q31", test_ramp_q31},
    {"test_check_delta_q31", test_check_delta_q31},
    {"test_check_delta_i32", test_check_delta_f32},
    // Add more tests here as needed
};
  
Test suite3_tests[] = {
    {"test_adc_process_sample_q15", test_adc_process_sample_q15},
    {"test_adc_process_sample_q31", test_adc_process_sample_q31},
    {"test_adc_process_sample_u_q31", test_adc_process_sample_u_q31},
    {"test_adc_process_sample_i16_q31", test_adc_process_sample_i16_q31},
    // Add more tests here as needed
};

Test suite4_tests[] = {
    {"test_sequence_limit_i16", test_sequence_limit_i16},
};

Test suite5_tests[] = {
    {"test_sequence_iir_pi_q15", test_sequence_iir_pi_q15},
};

// Suites
Suite suites[] = {
    {"Suite_1", suite1_tests, sizeof(suite1_tests) / sizeof(Test)},
    {"Suite_2", suite2_tests, sizeof(suite2_tests) / sizeof(Test)},
    {"Suite_3", suite3_tests, sizeof(suite3_tests) / sizeof(Test)},
    {"Suite_4", suite4_tests, sizeof(suite4_tests) / sizeof(Test)},
    {"Suite_5", suite5_tests, sizeof(suite5_tests) / sizeof(Test)},
    // Add more suites here as needed
};

int main() {
    int suite_size = (int) (sizeof(suites) / sizeof(Suite));

    // Initialize the CUnit test registry
    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();

    for (int i = 0; i < suite_size; i++) {
        // Add a suite to the registry
        CU_pSuite suite = CU_add_suite(suites[i].name, 0, 0);
   
        // Always check if add was successful
        if (NULL == suite) {
            CU_cleanup_registry();
            return CU_get_error();
        }

        // Add the tests to the suite
        for (int j = 0; j < suites[i].test_count; j++) {
            if (NULL == CU_add_test(suite, suites[i].tests[j].name, suites[i].tests[j].function)) {
                CU_cleanup_registry();
                return CU_get_error();
            }
        }
    }

    // Run all tests using the CUnit Basic interface
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    return CU_get_error();
}