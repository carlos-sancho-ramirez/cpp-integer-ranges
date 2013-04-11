/**
 * This is a test code to fully test the StaticIntegerRange template class
 */

#include "IntegerRanges.hpp"
#include <iostream>

#ifndef RANGE_MIN
#define RANGE_MIN -4
#endif

#ifndef RANGE_MAX
#define RANGE_MAX 5
#endif

#define TEST_PASSED 0
#define TEST_FAILED 1

#define TEST_PASSED_STR "Test passed: "
#define TEST_FAILED_STR "Test failed: "

#define TEST_CLASS StaticIntegerRange<RANGE_MIN,RANGE_MAX>
#define TEST_CLASS_STR STRINGIFICATION((TEST_CLASS))

#define STRINGIFICATION(str) _STRINGIFICATION(str)
#define _STRINGIFICATION(str) #str

using namespace std;

typedef TEST_CLASS range_t;

int main(int argc, char *argv[])
{
    try
    {
        range_t minValue = RANGE_MIN;
        range_t maxValue = RANGE_MAX;

        cout << TEST_PASSED_STR "Values " << static_cast<int>(minValue) << " and " <<
                static_cast<int>(maxValue) << " are valid within "
                TEST_CLASS_STR << endl;
    }
    catch(OutOfRangeError error)
    {
        cerr << TEST_FAILED_STR "Values " STRINGIFICATION(RANGE_MIN) " and "
                STRINGIFICATION(RANGE_MAX) " are invalid for "
                TEST_CLASS_STR << endl;
        return TEST_FAILED;
    }

    return TEST_PASSED;
}