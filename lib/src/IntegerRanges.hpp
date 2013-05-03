
#ifndef INTEGER_RANGES_HPP
#define INTEGER_RANGES_HPP

#include <climits>
#include <stdint.h>

#include "TemplateUtilities.hpp"
#include "OutOfRangeError.hpp"

template<bool sign, bool minInsideSignedChar, bool minInsideSignedShort,
        bool minInsideSignedInt, bool maxInsideSignedChar,
        bool maxInsideUnsignedChar, bool maxInsideSignedShort,
        bool maxInsideUnsignedShort, bool maxInsideSignedInt>
struct BoundedIntType;

template<>
struct BoundedIntType<true, true, true, true, true, true, true, true, true>
{
    typedef char type;
    typedef int_fast8_t fastType;
};

template<bool minInsideSignedChar, bool maxInsideSignedChar, bool maxInsideUnsignedChar>
struct BoundedIntType<true, minInsideSignedChar, true, true,
        maxInsideSignedChar, maxInsideUnsignedChar, true, true, true>
{
    typedef int16_t type;
    typedef int_fast16_t fastType;
};

template<bool minInsideSignedChar, bool minInsideSignedShort,
        bool maxInsideSignedChar, bool maxInsideUnsignedChar,
        bool maxInsideSignedShort, bool maxInsideUnsignedShort>
struct BoundedIntType<true, minInsideSignedChar, minInsideSignedShort,
        true, maxInsideSignedChar, maxInsideUnsignedChar, maxInsideSignedShort,
        maxInsideUnsignedShort, true>
{
    typedef int32_t type;
    typedef int_fast32_t fastType;
};

template<bool maxInsideSignedChar>
struct BoundedIntType< false, true, true, true, maxInsideSignedChar,
        true, true, true, true>
{
    typedef unsigned char type;
    typedef uint_fast8_t fastType;
};

template<bool maxInsideSignedChar,  bool maxInsideUnsignedChar, bool maxInsideSignedShort>
struct BoundedIntType<false, true, true, true, maxInsideSignedChar,
        maxInsideUnsignedChar, maxInsideSignedShort, true, true>
{
    typedef uint16_t type;
    typedef uint_fast16_t fastType;
};

template<bool maxInsideSignedChar, bool maxInsideUnsignedChar,
        bool maxInsideSignedShort, bool maxInsideUnsignedShort,
        bool maxInsideSignedInt>
struct BoundedIntType< false, true, true, true, maxInsideSignedChar,
        maxInsideUnsignedChar, maxInsideSignedShort,
        maxInsideUnsignedShort, maxInsideSignedInt>
{
    typedef uint32_t type;
    typedef uint_fast32_t fastType;
};


template<int MIN, int MAX>
struct BoundedIntTraits
{
    typedef typename BoundedIntType<
        MIN < 0,
        MIN >= CHAR_MIN,
        MIN >= SHRT_MIN,
        MIN >= INT_MIN,
        MAX <= CHAR_MAX,
        MAX <= UCHAR_MAX,
        MAX <= SHRT_MAX,
        MAX <= USHRT_MAX,
        MAX <= INT_MAX>::type type;

    typedef typename BoundedIntType<
        MIN < 0,
        MIN >= CHAR_MIN,
        MIN >= SHRT_MIN,
        MIN >= INT_MIN,
        MAX <= CHAR_MAX,
        MAX <= UCHAR_MAX,
        MAX <= SHRT_MAX,
        MAX <= USHRT_MAX,
        MAX <= INT_MAX>::fastType fastType;

    enum
    {
        MIN_VALUE = MIN,
        MAX_VALUE = MAX,
        RANGE = MAX - MIN,
        STEPS = RANGE + 1,

        // Minimum amount of bits required to hold all possible steps, but not its value
        NEEDED_BITS = MathLog<RANGE,2>::value,

        // Mask that can be applied to a value that the MIN_VALUE has been substracted or MIN_VALUE is 0
        RELATIVE_MASK = (1 << NEEDED_BITS) - 1,
    };
};

/**
 * IntegerRange: Class wrapping an integer with a suitable size and ensures the
 * wrapped integer never gets outside the given value.
 *
 * It is intended to keep this class in a way it can be managed in the code as
 * if a normal integer with no restriction was. This way the resulting code
 * should be able to just declare this class in a typedef and switch its
 * definition to a normal integer if looking for performance.
 */
template<int MIN, int MAX, typename TYPE = typename BoundedIntTraits<MIN, MAX>::type>
struct StaticIntegerRange
{
    enum
    {
        validRangeDeclaredCheck = StaticAssert<(MIN <= MAX)>::value
    };
    typedef TYPE type;

    private:
    TYPE mValue;

    public:
    StaticIntegerRange(const TYPE value) : mValue(value)
    {
        if (MIN > value || value > MAX)
        {
            throw OutOfRangeError();
        }
    }

    template<typename RANGE_TYPE>
    StaticIntegerRange(const RANGE_TYPE &value) :
            mValue(static_cast<const TYPE>(value))
    {
        if (MIN > mValue || mValue > MAX)
        {
            throw OutOfRangeError();
        }
    }

    StaticIntegerRange<MIN,MAX,TYPE> &operator++() // Prefix (++x)
    {
        if (mValue >= MAX)
        {
            throw OutOfRangeError();
        }

        mValue++;
        return *this;
    }

    StaticIntegerRange<MIN,MAX,TYPE> &operator++(int unused) // Postfix (x++)
    {
        return operator++();
    }

    StaticIntegerRange<MIN,MAX,TYPE> &operator--() // Prefix (--x)
    {
        if (mValue <= MIN)
        {
            throw OutOfRangeError();
        }

        mValue--;
        return *this;
    }

    StaticIntegerRange<MIN,MAX,TYPE> &operator--(int unused) // Postfix (x--)
    {
        return operator--();
    }

    StaticIntegerRange<MIN,MAX,TYPE> &operator+=(TYPE value)
    {
        if (MIN > (mValue + value) || (mValue + value) > MAX)
        {
            throw OutOfRangeError();
        }

        mValue += value;
        return *this;
    }

    StaticIntegerRange<MIN,MAX,TYPE> &operator-=(TYPE value)
    {
        if (MIN > (mValue - value) || (mValue - value) > MAX)
        {
            throw OutOfRangeError();
        }

        mValue -= value;
        return *this;
    }

    operator TYPE() const
    {
        return mValue;
    }
};

#endif //INTEGER_RANGES_HPP
