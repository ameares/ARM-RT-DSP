/**
 * \file common.h
 * \brief Common definitions and additional documentation for unit tests.
*/

/**
 * \mainpage ARM RT DSP Library Documentation
 * 
 * \section intro_sec Introduction
 * 
 * ARM RT DSP is a library designed to provide developers with a comprehensive
 * set of digital signal processing (DSP) functions optimized for ARM processors.
 * The library offers a broad range of functionalities that include but not
 * limited to ADC operations, limit checks, delta checks, min/max functions,
 * and various other mathematical operations common in DSP.
 * 
 * \section install_sec Examples
 * 
 * 
 * 
 * 
*/

#ifndef _COMMON_H_
#define _COMMON_H_

// Struct to hold test function and its name
typedef struct {
    const char *name;
    CU_TestFunc function;
} Test;

// Struct to hold suite name and its tests
typedef struct {
    const char *name;
    Test *tests;
    int test_count;
} Suite;




#endif