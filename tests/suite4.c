#include <stdio.h>
#include <stdlib.h>
#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>
#include "common.h"
#include "arm_rt_dsp.h"

#define TEST_SEQUENCE_LENGTH 100
#define CSV_FILE_PATH "./tests_out/test_sequence_limit_i16.csv"

void test_sequence_limit_i16(void) {
    //int16_t seq_len = TEST_SEQUENCE_LENGTH;

    // Open the file for writing. This will overwrite the existing file if it exists.
    FILE *fp = fopen(CSV_FILE_PATH, "w");
    if (!fp) {
        CU_FAIL("Could not open file for writing");
        return;
    }
    // Write the CSV header
    fprintf(fp, "input_value,output_value\n");

    // Generate TEST_SEQUENCE_LENGTH calls to limit_i16
    for (int i = 0; i < TEST_SEQUENCE_LENGTH; i++) {
        // Assign i to val
        int16_t val = i - TEST_SEQUENCE_LENGTH/2;

        // Assign constant lower limit +10
        int16_t llim = -1 * TEST_SEQUENCE_LENGTH/4;

        // Assign constant upper limit +50
        int16_t ulim = TEST_SEQUENCE_LENGTH/4;

        // Call the limit_i16 function
        int16_t output = limit_i16(val, llim, ulim);

        // Write the input and output values to the CSV file
        fprintf(fp, "%d,%d\n", val, output);
    }

    // Close the file
    if (fclose(fp) == EOF) {
        CU_FAIL("Failed to close the file");
    } else {
        CU_PASS("Test sequence written to file successfully");
    }
}
