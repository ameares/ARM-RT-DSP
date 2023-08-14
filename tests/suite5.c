#include <stdio.h>
#include <stdlib.h>
#include <CUnit/Basic.h>
#include <CUnit/CUnit.h>
#include "common.h"
#include "arm_rt_dsp.h"

#define TEST_SEQUENCE_LENGTH 100
#define CSV_FILE_PATH_PI_Q15 "./tests_out/test_sequence_iir_pi_q15.csv"

#define CSV_FILE_PATH_PI_Q31 "./tests_out/test_sequence_iir_pi_q31.csv"

// First Order System struct definition
typedef struct
{
    q15_t a; // system parameter a
    q15_t b; // system parameter b
    q15_t x; // system state/output
} first_order_system_q15;

// First Order System initialization function
void fos_init_q15(first_order_system_q15 *sys, q15_t a, q15_t b, q15_t initial_x)
{
    sys->a = a;
    sys->b = b;
    sys->x = initial_x;
}

// First Order System update function
q15_t fos_update_q15(first_order_system_q15 *sys, q15_t u)
{
    sys->x = mul_q15(sys->a, sys->x) - mul_q15(sys->b, u);
    return sys->x;
}

void test_sequence_iir_pi_q15(void)
{
    //int16_t seq_len = TEST_SEQUENCE_LENGTH;
    iir_pi_instance_q15 mypi;
    q15_t ref = Q15(0.1);
    q15_t error = 0;
    q15_t u = 0;

    // Initialize the first order system
    first_order_system_q15 fos;
    fos_init_q15(&fos, Q15(-0.25), Q15(0.1), Q15(0.0));

    // Initialize the filter
    mypi.Kp = ACC16(1.5);
    mypi.Ki = ACC16(1.0);
    iir_pi_init_q15(&mypi, 1);

    // Open the file for writing. This will overwrite the existing file if it exists.
    FILE *fp = fopen(CSV_FILE_PATH_PI_Q15, "w");
    if (!fp)
    {
        CU_FAIL("Could not open file for writing");
        return;
    }
    // Write the CSV header
    fprintf(fp, "input_value,output_value\n");

    // Generate TEST_SEQUENCE_LENGTH calls to the function
    for (int i = 0; i < TEST_SEQUENCE_LENGTH; i++)
    {

        // Some kind of simulation takes place here
        // Call iir_pi_q15() with a series of input values.
        // The controller takes the difference between the reference and the system output
        error = fos.x - ref;

        // The PI controller computes the control input
        u = iir_pi_q15(&mypi, error);

        // The system takes the control input and updates its state
        fos_update_q15(&fos, u);

        // Write the input and output values to the CSV file
        fprintf(fp, "%d,%d\n", i, fos.x);
    }

    // Close the file
    if (fclose(fp) == EOF)
    {
        CU_FAIL("Failed to close the file");
    }
    else
    {
        CU_PASS("Test sequence written to file successfully");
    }
}


// First Order System struct definition for q31_t
typedef struct
{
    q31_t a; // system parameter a
    q31_t b; // system parameter b
    q31_t x; // system state/output
} first_order_system_q31;

// First Order System initialization function for q31_t
void fos_init_q31(first_order_system_q31 *sys, q31_t a, q31_t b, q31_t initial_x)
{
    sys->a = a;
    sys->b = b;
    sys->x = initial_x;
}

// First Order System update function for q31_t
q31_t fos_update_q31(first_order_system_q31 *sys, q31_t u)
{
    sys->x = mul_q31(sys->a, sys->x) - mul_q31(sys->b, u);
    return sys->x;
}

void test_sequence_iir_pi_q31(void)
{
    iir_pi_instance_q31 mypi_q31;
    q31_t ref = Q31(0.1);
    q31_t error = 0;
    q31_t u = 0;

    // Initialize the first order system for q31_t
    first_order_system_q31 fos_q31;
    fos_init_q31(&fos_q31, Q31(-0.25), Q31(0.1), Q31(0.0));

    // Initialize the filter for q31_t
    mypi_q31.Kp = ACC32(1.5);
    mypi_q31.Ki = ACC32(1.0);
    iir_pi_init_q31(&mypi_q31, 1);

    FILE *fp = fopen(CSV_FILE_PATH_PI_Q31, "w");
    if (!fp)
    {
        CU_FAIL("Could not open file for writing");
        return;
    }
    // Write the CSV header
    fprintf(fp, "input_value,output_value\n");

    // Generate TEST_SEQUENCE_LENGTH calls to the function for q31_t
    for (int i = 0; i < TEST_SEQUENCE_LENGTH; i++)
    {
        error = fos_q31.x - ref;
        u = iir_pi_q31(&mypi_q31, error);
        fos_update_q31(&fos_q31, u);
        fprintf(fp, "%d,%d\n", i, fos_q31.x);
    }

    if (fclose(fp) == EOF)
    {
        CU_FAIL("Failed to close the file");
    }
    else
    {
        CU_PASS("Test sequence written to file successfully");
    }
}