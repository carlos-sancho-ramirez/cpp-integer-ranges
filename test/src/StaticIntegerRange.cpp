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

#define TEST_CLASS2 StaticIntegerRange<RANGE_MIN,RANGE_MAX - 1>
#define TEST_CLASS2_STR STRINGIFICATION((TEST_CLASS2))

#define STRINGIFICATION(str) _STRINGIFICATION(str)
#define _STRINGIFICATION(str) #str

#define TEST_ASSERT_TRUE(condition) \
        if (condition) \
        { \
            cout << TEST_PASSED_STR TEST_STR TEST_CLASS_STR << endl; \
        } \
        else \
        { \
            cerr << TEST_FAILED_STR TEST_STR TEST_CLASS_STR << endl; \
            return TEST_FAILED; \
        }

#define TEST_ASSERT_FALSE(condition) \
        if (condition) \
        { \
            cerr << TEST_FAILED_STR TEST_STR TEST_CLASS_STR << endl; \
            return TEST_FAILED; \
        } \
        else \
        { \
            cout << TEST_PASSED_STR TEST_STR TEST_CLASS_STR << endl; \
        }

#define SHOW_OUT_OF_RANGE_ERROR \
    cerr << TEST_FAILED_STR "OutOfRangeError thrown. " TEST_STR TEST_CLASS_STR << endl; \
    return TEST_FAILED

using namespace std;

typedef TEST_CLASS range_t;
typedef TEST_CLASS2 range2_t;

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

#define TEST_STR "Reassign value for "

    // Reassigning values
    try
    {
        range_t value = RANGE_MIN;
        value = RANGE_MAX;

        cout << TEST_PASSED_STR TEST_STR TEST_CLASS_STR << endl;
    }
    catch(OutOfRangeError error)
    {
        cerr << TEST_FAILED_STR TEST_STR TEST_CLASS_STR << endl;
        return TEST_FAILED;
    }

#undef TEST_STR
#define TEST_STR "Comparing with == operator when normal int on the right equals for "

    try
    {
        range_t value = RANGE_MAX;
        int expected = RANGE_MAX;

        TEST_ASSERT_TRUE(value == expected)
    }
    catch(OutOfRangeError error)
    {
        SHOW_OUT_OF_RANGE_ERROR;
    }

#undef TEST_STR
#define TEST_STR "Comparing with == operator when normal int on the left equals for "

    try
    {
        range_t value = RANGE_MAX;
        int expected = RANGE_MAX;

        TEST_ASSERT_TRUE(expected == value)
    }
    catch(OutOfRangeError error)
    {
        SHOW_OUT_OF_RANGE_ERROR;
    }

#undef TEST_STR
#define TEST_STR "Comparing with == operator when other " TEST_CLASS_STR " equals for "

    try
    {
        range_t value1 = RANGE_MAX;
        range_t value2 = RANGE_MAX;

        TEST_ASSERT_TRUE(value1 == value2)
    }
    catch(OutOfRangeError error)
    {
        SHOW_OUT_OF_RANGE_ERROR;
    }

#undef TEST_STR
#define TEST_STR "Comparing with == operator when other " TEST_CLASS2_STR " equals for "

    try
    {
        range_t value1 = RANGE_MIN;
        range2_t value2 = RANGE_MIN;

        TEST_ASSERT_TRUE(value1 == value2)
    }
    catch(OutOfRangeError error)
    {
        SHOW_OUT_OF_RANGE_ERROR;
    }

#undef TEST_STR
#define TEST_STR "Comparing with == operator when normal int on the right differs for "

    try
    {
        range_t value = RANGE_MAX;
        int expected = RANGE_MAX - 1;

        TEST_ASSERT_FALSE(value == expected)
    }
    catch(OutOfRangeError error)
    {
        SHOW_OUT_OF_RANGE_ERROR;
    }

#undef TEST_STR
#define TEST_STR "Comparing with == operator when normal int on the left differs for "

    try
    {
        range_t value = RANGE_MAX;
        int expected = RANGE_MAX - 1;

        TEST_ASSERT_FALSE(expected == value)
    }
    catch(OutOfRangeError error)
    {
        SHOW_OUT_OF_RANGE_ERROR;
    }

#undef TEST_STR
#define TEST_STR "Comparing with == operator when other " TEST_CLASS_STR " differs for "

    try
    {
        range_t value1 = RANGE_MAX;
        range_t value2 = RANGE_MAX - 1;

        TEST_ASSERT_FALSE(value1 == value2)
    }
    catch(OutOfRangeError error)
    {
        SHOW_OUT_OF_RANGE_ERROR;
    }

#undef TEST_STR
#define TEST_STR "Comparing with == operator when other " TEST_CLASS2_STR " differs for "

    try
    {
        range_t value1 = RANGE_MIN + 1;
        range2_t value2 = RANGE_MIN;

        TEST_ASSERT_FALSE(value1 == value2)
    }
    catch(OutOfRangeError error)
    {
        SHOW_OUT_OF_RANGE_ERROR;
    }

#undef TEST_STR
#define TEST_STR "Comparing with != operator when normal int on the right equals for "

    try
    {
        range_t value = RANGE_MAX;
        int expected = RANGE_MAX;

        TEST_ASSERT_FALSE(value != expected)
    }
    catch(OutOfRangeError error)
    {
        SHOW_OUT_OF_RANGE_ERROR;
    }

#undef TEST_STR
#define TEST_STR "Comparing with != operator when normal int on the left equals for "

    try
    {
        range_t value = RANGE_MAX;
        int expected = RANGE_MAX;

        TEST_ASSERT_FALSE(expected != value)
    }
    catch(OutOfRangeError error)
    {
        SHOW_OUT_OF_RANGE_ERROR;
    }

#undef TEST_STR
#define TEST_STR "Comparing with != operator when other " TEST_CLASS_STR " equals for "

    try
    {
        range_t value1 = RANGE_MAX;
        range_t value2 = RANGE_MAX;

        TEST_ASSERT_FALSE(value1 != value2)
    }
    catch(OutOfRangeError error)
    {
        SHOW_OUT_OF_RANGE_ERROR;
    }

#undef TEST_STR
#define TEST_STR "Comparing with != operator when other " TEST_CLASS2_STR " equals for "

    try
    {
        range_t value1 = RANGE_MIN;
        range2_t value2 = RANGE_MIN;

        TEST_ASSERT_FALSE(value1 != value2)
    }
    catch(OutOfRangeError error)
    {
        SHOW_OUT_OF_RANGE_ERROR;
    }

#undef TEST_STR
#define TEST_STR "Comparing with != operator when normal int on the right differs for "

    try
    {
        range_t value = RANGE_MAX;
        int expected = RANGE_MAX - 1;

        TEST_ASSERT_TRUE(value != expected)
    }
    catch(OutOfRangeError error)
    {
        SHOW_OUT_OF_RANGE_ERROR;
    }

#undef TEST_STR
#define TEST_STR "Comparing with != operator when normal int on the left differs for "

    try
    {
        range_t value = RANGE_MAX;
        int expected = RANGE_MAX - 1;

        TEST_ASSERT_TRUE(expected != value)
    }
    catch(OutOfRangeError error)
    {
        SHOW_OUT_OF_RANGE_ERROR;
    }

#undef TEST_STR
#define TEST_STR "Comparing with != operator when other " TEST_CLASS_STR " differs for "

    try
    {
        range_t value1 = RANGE_MAX;
        range_t value2 = RANGE_MAX - 1;

        TEST_ASSERT_TRUE(value1 != value2)
    }
    catch(OutOfRangeError error)
    {
        SHOW_OUT_OF_RANGE_ERROR;
    }

#undef TEST_STR
#define TEST_STR "Comparing with != operator when other " TEST_CLASS2_STR " differs for "

    try
    {
        range_t value1 = RANGE_MIN + 1;
        range2_t value2 = RANGE_MIN;

        TEST_ASSERT_TRUE(value1 != value2)
    }
    catch(OutOfRangeError error)
    {
        SHOW_OUT_OF_RANGE_ERROR;
    }

#undef TEST_STR
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

#undef TEST_STR
#define TEST_STR "value += 1 for "

    // Adding and assigning
    try
    {
        range_t value = RANGE_MAX;
        value += 1;
        cerr << TEST_FAILED_STR TEST_STR TEST_CLASS_STR << endl;
        return TEST_FAILED;
    }
    catch(OutOfRangeError error)
    {
        cout << TEST_PASSED_STR TEST_STR TEST_CLASS_STR << endl;
    }

#undef TEST_STR
#define TEST_STR "value -= 1 for "

    // Substracting and assigning
    try
    {
        range_t value = RANGE_MIN;
        value -= 1;
        cerr << TEST_FAILED_STR TEST_STR TEST_CLASS_STR << endl;
        return TEST_FAILED;
    }
    catch(OutOfRangeError error)
    {
        cout << TEST_PASSED_STR TEST_STR TEST_CLASS_STR << endl;
    }

    cout << "All test passed" << endl;
    return TEST_PASSED;
}