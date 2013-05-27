
#ifndef PACKED_VALUES_HPP
#define PACKED_VALUES_HPP

#include "IntegerRanges.hpp"

/**
 * PackedValues: Class wrapping a list of IntegerRanges with the intention to
 * save memory space. All wrapped StaticIntegerRange classes will start with
 * their minimum value by default.
 *
 * As an example, given the following class:
 *
 * class MyClass
 * {
 *     unsinged int cypher;
 *     bool used;
 * }
 *
 * Usually a compiler for 32-bit code will pack this class using 8 bytes for
 * alignment reasons. But if we know for sure cypher can only have values from 0
 * to 9 (both included), we can rewrite this using IntegerRanges instead,
 * resulting in the following code.
 *
 * class MyClass
 * {
 *     StaticIntegerRange<0,9> cypher;
 *     bool used;
 * }
 *
 * This way, the IntegerRange will see only 4 bits are needed to codify the
 * cypher, then it will become an 8-bit integer as it is the minimum normal
 * processors can handle. So this class will use 2 bytes of memory, but due to
 * the alignment, in 32-bit will become 4 bytes.
 *
 * packedvalues class template can be used to pack more than one attribute
 * saving space memory. Then the previous class can be expressed as:
 *
 * typedef PackedValues<StaticIntegerRange<0,9>, StaticIntegerRange<0,1> > MyClass;
 *
 * Then the class will only use 1 byte, as cypher needs 4 bits and the boolean
 * only one, so there are still 3 more available.
 */
template<class type1, class type2>
struct PackedValues {
    enum
    {
        TYPE1_BIT_BASE = 0,
        TYPE2_BIT_BASE = TYPE1_BIT_BASE + type1::NEEDED_BITS,
        NEEDED_BITS = TYPE2_BIT_BASE + type2::NEEDED_BITS,

        TYPE1_BIT_MASK = MathPower<2,TYPE2_BIT_BASE>::value - 1,
        TYPE2_BIT_MASK = MathPower<2,NEEDED_BITS>::value - TYPE1_BIT_MASK - 1
    };

    typedef typename BoundedIntTraits<0, MathPower<2, NEEDED_BITS>::value - 1>::type packedType;

    private:
    packedType mPacked;

    public:

    PackedValues() : mPacked(0)
    { }

    void setValueForType1(type1 value)
    {
        packedType converted = value;
        mPacked &= ~TYPE1_BIT_MASK;
        mPacked |= (converted - type1::MIN_VALUE) << TYPE1_BIT_BASE;
    }

    type1 getValueForType1()
    {
        return ((mPacked & TYPE1_BIT_MASK) >> TYPE1_BIT_BASE) + type1::MIN_VALUE;
    }

    void setValueForType2(type2 value)
    {
        packedType converted = value;
        mPacked &= ~TYPE2_BIT_MASK;
        mPacked |= (converted - type2::MIN_VALUE) << TYPE2_BIT_BASE;
    }

    type2 getValueForType2()
    {
        return ((mPacked & TYPE2_BIT_MASK) >> TYPE2_BIT_BASE) + type2::MIN_VALUE;
    }    
};

#endif // PACKED_VALUES_HPP
