#include <stdio.h>
#include <stdlib.h>
#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>

// Include the header file for abs_sat_q31 function
#include "common.h"
#include "arm_rt_dsp.h"


// ADC Sample Processing Test Functions

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