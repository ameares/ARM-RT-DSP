/*
My common header file for all my C projects.

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