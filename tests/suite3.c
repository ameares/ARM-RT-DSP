#include <stdio.h>
#include <stdlib.h>
#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>
#include "common.h"
#include "arm_rt_dsp.h"

  
// ADC Sample Processing Test Functions

void test_adc_process_sample_q15() {
    uint16_t raw_value[] = {0, 500, 2048, 4095};
    int16_t offset[] =     {2048, 2048, 2048, 2048};
    q15_t slope[] =        {Q15(0.1), Q15(0.1), Q15(0.1), Q15(0.1)};
    q15_t expected[] =     {-3276, -2478, 0, 3274};
    
    for (size_t i = 0; i < sizeof(raw_value) / sizeof(raw_value[0]); i++) {
        q15_t r = adc_process_sample_q15(raw_value[i], offset[i], slope[i]);
        // print the result
        //printf("raw_value: %d, offset: %d, slope: %d, result: %d\n", raw_value[i], offset[i], slope[i], r);
        CU_ASSERT_EQUAL(r, expected[i]);
    }
}

void test_adc_process_sample_q31() {
    uint16_t raw_value[] = {0, 500, 2048, 4095};
    int16_t offset[] = {2048, 2048, 2048, 2048};
    q31_t slope[] = {Q31(0.1), Q31(0.1), Q31(0.1), Q31(0.1)};
    q31_t expected[] = {-214748364, -162319566, 0, 214643506};

    for (size_t i = 0; i < sizeof(raw_value) / sizeof(raw_value[0]); i++) {
        //CU_ASSERT_EQUAL(adc_process_sample_q31(raw_value[i], offset[i], slope[i]), expected[i]);

        q31_t r = adc_process_sample_q31(raw_value[i], offset[i], slope[i]);
        // print the result
        //printf("raw_value: %d, offset: %d, slope: %d, result: %d\n", raw_value[i], offset[i], slope[i], r);
        CU_ASSERT_EQUAL(r, expected[i]);
    }
}

void test_adc_process_sample_u_q31() {
    uint16_t raw_value[] = {0, 500, 2048, 4095};
    int16_t offset[] = {0, 0, 0, 0};
    q31_t slope[] = {Q31(0.1), Q31(0.1), Q31(0.1), Q31(0.1)};
    q31_t expected[] = {0, 26214398, 107374182, 214695934};

    for (size_t i = 0; i < sizeof(raw_value) / sizeof(raw_value[0]); i++) {
        //CU_ASSERT_EQUAL(adc_process_sample_u_q31(raw_value[i], offset[i], slope[i]), expected[i]);

        q31_t r = adc_process_sample_u_q31(raw_value[i], offset[i], slope[i]);
        // print the result
        //printf("raw_value: %d, offset: %d, slope: %d, result: %d\n", raw_value[i], offset[i], slope[i], r);
        CU_ASSERT_EQUAL(r, expected[i]);
    }
}

void test_adc_process_sample_i16_q31() {
    int16_t raw_value[] = {0, 500, 2048, 4095};
    int16_t offset[] = {2048, 2048, 2048, 2048};
    q31_t slope[] = {Q31(0.1), Q31(0.1), Q31(0.1), Q31(0.1)};
    q31_t expected[] = {-13421774, -10144974, 0, 13415218};

    for (size_t i = 0; i < sizeof(raw_value) / sizeof(raw_value[0]); i++) {
        //CU_ASSERT_EQUAL(adc_process_sample_i16_q31(raw_value[i], offset[i], slope[i]), expected[i]);

        q31_t r = adc_process_sample_i16_q31(raw_value[i], offset[i], slope[i]);
        // print the result
        //printf("raw_value: %d, offset: %d, slope: %d, result: %d\n", raw_value[i], offset[i], slope[i], r);
        CU_ASSERT_EQUAL(r, expected[i]);
    }
}