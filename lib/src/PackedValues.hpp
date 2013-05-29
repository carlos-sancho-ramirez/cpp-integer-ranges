
#ifndef PACKED_VALUES_HPP
#define PACKED_VALUES_HPP

#include "IntegerRanges.hpp"

/**
 * PackedXValues: Set of classes wrapping a list of IntegerRanges with the intention to
 * save memory space. All wrapped StaticIntegerRange classes will start with
 * their minimum value by default.
 *
 * As an example, given the following class:
 *
 * class MyClass
 * {
 *     unsigned int cypher;
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

template<class type1, class type2, int ALL_NEEDED_BITS = type1::NEEDED_BITS + type2::NEEDED_BITS>
struct Packed2Values {
    enum
    {
        TYPE1_BIT_BASE = 0,
        TYPE2_BIT_BASE = TYPE1_BIT_BASE + type1::NEEDED_BITS,
        TYPE3_BIT_BASE = TYPE2_BIT_BASE + type2::NEEDED_BITS,

        TYPE1_BIT_MASK = MathPower<2,TYPE2_BIT_BASE>::value - 1,
        TYPE2_BIT_MASK = MathPower<2,TYPE3_BIT_BASE>::value - TYPE1_BIT_MASK - 1
    };

    protected:
    typedef typename BoundedIntTraits<0, MathPower<2, ALL_NEEDED_BITS>::value - 1>::type packedType;
    packedType mPacked;

    public:
    Packed2Values() : mPacked(0)
    { }

    void setValueForType1(type1 value)
    {
        packedType converted = value;
        mPacked &= ~TYPE1_BIT_MASK;
        mPacked |= converted - type1::MIN_VALUE;
    }

    type1 getValueForType1()
    {
        return (mPacked & TYPE1_BIT_MASK) + type1::MIN_VALUE;
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

template<class type1, class type2, class type3,
		int ALL_NEEDED_BITS = type1::NEEDED_BITS + type2::NEEDED_BITS + type3::NEEDED_BITS>
struct Packed3Values : public Packed2Values<type1, type2, ALL_NEEDED_BITS> {

    typedef Packed2Values<type1, type2, ALL_NEEDED_BITS> parentType;

    enum
    {
        TYPE3_BIT_BASE = parentType::TYPE3_BIT_BASE,
        TYPE4_BIT_BASE = TYPE3_BIT_BASE + type3::NEEDED_BITS,
        TYPE3_BIT_MASK = MathPower<2,TYPE4_BIT_BASE>::value - MathPower<2,TYPE3_BIT_BASE>::value
    };

    public:
    void setValueForType3(type3 value)
    {
        typename parentType::packedType converted = value;
        parentType::mPacked &= ~TYPE3_BIT_MASK;
        parentType::mPacked |= (converted - type3::MIN_VALUE) << TYPE3_BIT_BASE;
    }

    type3 getValueForType3()
    {
        return ((parentType::mPacked & TYPE3_BIT_MASK) >> TYPE3_BIT_BASE) + type3::MIN_VALUE;
    }
};

#endif // PACKED_VALUES_HPP
