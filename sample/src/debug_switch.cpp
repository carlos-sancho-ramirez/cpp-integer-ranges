
#define RANGE_MIN 0
#define RANGE_MAX 10

typedef int rangedRaw_t;

#ifdef CHECK_RANGES

#include "IntegerRanges.hpp"
typedef StaticIntegerRange<RANGE_MIN, RANGE_MAX, rangedRaw_t> rangedInt_t;
typedef StaticIntegerRange<RANGE_MIN, RANGE_MAX + 1, rangedRaw_t> counter_t;

#else

typedef rangedRaw_t rangedInt_t;
typedef rangedRaw_t counter_t;

#endif //CHECK_RANGES

#include <iostream>

using namespace std;

/**
 * This file can be compiled declaring or not declaring CHECK_RANGES.
 *
 * If declared, types rangedInt_t and counter_t are actually integer ranges and
 * an exception will be thrown in case the variable goes out of range.
 *
 * If not declared, types rangedInt_t and counter_t will be normal integers and
 * ranges will not be checked, so the execution will continue in case of being
 * outside the ranges.
 *
 * Checking the ranges involves more code, so the final executed file will be
 * bigger and slower than just using normal integers. But if the ranges are
 * checked the developer can be sure all values are inside the range. The idea
 * is testing the app with CHECK_RANGES declared and release it without.
 */

namespace
{
    void showValue(const rangedInt_t value)
    {
        cout << "Showing value " << static_cast<int>(value) << endl;
    }
}

int main(int args, char *argv[])
{
    for(counter_t counter = RANGE_MIN; counter < RANGE_MAX; counter++)
    {
        showValue(counter);
    }

    return 0;
}
