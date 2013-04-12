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
    // Assigning values
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

#define TEST_STR "post ++ operator on a value that is actually in the limit for "

    // Operator ++
    try
    {
        range_t value = RANGE_MAX;
        value++;

        cerr << TEST_FAILED_STR TEST_STR TEST_CLASS_STR << endl;
        return TEST_FAILED;
    }
    catch(OutOfRangeError error)
    {
        cout << TEST_PASSED_STR TEST_STR TEST_CLASS_STR << endl;
    }

#undef TEST_STR
#define TEST_STR "pre ++ operator on a value that is actually in the limit for "

    try
    {
        range_t value = RANGE_MAX;
        ++value;

        cerr << TEST_FAILED_STR TEST_STR TEST_CLASS_STR << endl;
        return TEST_FAILED;
    }
    catch(OutOfRangeError error)
    {
        cout << TEST_PASSED_STR TEST_STR TEST_CLASS_STR << endl;
    }

#undef TEST_STR
#define TEST_STR "post ++ operator on a value that is not in the limit for "

    try
    {
        range_t value = RANGE_MAX - 1;
        value++;

        cout << TEST_PASSED_STR TEST_STR TEST_CLASS_STR << endl;
    }
    catch(OutOfRangeError error)
    {
        cerr << TEST_FAILED_STR TEST_STR TEST_CLASS_STR << endl;
        return TEST_FAILED;
    }

#undef TEST_STR
#define TEST_STR "pre ++ operator on a value that is not in the limit for "

    try
    {
        range_t value = RANGE_MAX - 1;
        ++value;

        cout << TEST_PASSED_STR TEST_STR TEST_CLASS_STR << endl;
    }
    catch(OutOfRangeError error)
    {
        cerr << TEST_FAILED_STR TEST_STR TEST_CLASS_STR << endl;
        return TEST_FAILED;
    }

#undef TEST_STR
#define TEST_STR "post -- operator on a value that is actually in the limit for "

    // Operator --
    try
    {
        range_t value = RANGE_MIN;
        value--;

        cerr << TEST_FAILED_STR TEST_STR TEST_CLASS_STR << endl;
        return TEST_FAILED;
    }
    catch(OutOfRangeError error)
    {
        cout << TEST_PASSED_STR TEST_STR TEST_CLASS_STR << endl;
    }

#undef TEST_STR
#define TEST_STR "pre -- operator on a value that is actually in the limit for "

    try
    {
        range_t value = RANGE_MIN;
        --value;

        cerr << TEST_FAILED_STR TEST_STR TEST_CLASS_STR << endl;
        return TEST_FAILED;
    }
    catch(OutOfRangeError error)
    {
        cout << TEST_PASSED_STR TEST_STR TEST_CLASS_STR << endl;
    }

#undef TEST_STR
#define TEST_STR "post -- operator on a value that is not in the limit for "

    try
    {
        range_t value = RANGE_MIN + 1;
        value--;

        cout << TEST_PASSED_STR TEST_STR TEST_CLASS_STR << endl;
    }
    catch(OutOfRangeError error)
    {
        cerr << TEST_FAILED_STR TEST_STR TEST_CLASS_STR << endl;
        return TEST_FAILED;
    }

#undef TEST_STR
#define TEST_STR "pre -- operator on a value that is not in the limit for "

    try
    {
        range_t value = RANGE_MIN + 1;
        --value;

        cout << TEST_PASSED_STR TEST_STR TEST_CLASS_STR << endl;
    }
    catch(OutOfRangeError error)
    {
        cerr << TEST_FAILED_STR TEST_STR TEST_CLASS_STR << endl;
        return TEST_FAILED;
    }

#undef TEST_STR
#define TEST_STR "value + 1 throws an exception for "

    // Adding
    try
    {
        range_t value = RANGE_MAX;
        cout << TEST_PASSED_STR "(value + 1) is " << static_cast<int>(value + 1) << " for " TEST_CLASS_STR << endl;
    }
    catch(OutOfRangeError error)
    {
        cerr << TEST_FAILED_STR TEST_STR TEST_CLASS_STR << endl;
        return TEST_FAILED;
    }

#undef TEST_STR
#define TEST_STR "value - 1 throws an exception for "

    // Substracting
    try
    {
        range_t value = RANGE_MIN;
        cout << TEST_PASSED_STR "(value - 1) is " << static_cast<int>(value - 1) << " for " TEST_CLASS_STR << endl;
    }
    catch(OutOfRangeError error)
    {
        cerr << TEST_FAILED_STR TEST_STR TEST_CLASS_STR << endl;
        return TEST_FAILED;
    }

    cout << "All test passed" << endl;
    return TEST_PASSED;
}