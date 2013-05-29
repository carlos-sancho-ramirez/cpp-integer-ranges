
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
    typedef parentType baseType;

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

template<class type1, class type2, class type3, class type4,
		int ALL_NEEDED_BITS = type1::NEEDED_BITS + type2::NEEDED_BITS +
        type3::NEEDED_BITS + type4::NEEDED_BITS>
struct Packed4Values : public Packed3Values<type1, type2, type3, ALL_NEEDED_BITS> {

    typedef Packed3Values<type1, type2, type3, ALL_NEEDED_BITS> parentType;
    typedef typename parentType::baseType baseType;

    enum
    {
        TYPE4_BIT_BASE = parentType::TYPE4_BIT_BASE,
        TYPE5_BIT_BASE = TYPE4_BIT_BASE + type4::NEEDED_BITS,
        TYPE4_BIT_MASK = MathPower<2,TYPE5_BIT_BASE>::value - MathPower<2,TYPE4_BIT_BASE>::value
    };

    public:
    void setValueForType4(type4 value)
    {
        typename parentType::packedType converted = value;
        parentType::mPacked &= ~TYPE4_BIT_MASK;
        parentType::mPacked |= (converted - type4::MIN_VALUE) << TYPE4_BIT_BASE;
    }

    type4 getValueForType4()
    {
        return ((parentType::mPacked & TYPE4_BIT_MASK) >> TYPE4_BIT_BASE) + type4::MIN_VALUE;
    }
};

template<class type1, class type2, class type3, class type4, class type5,
		int ALL_NEEDED_BITS = type1::NEEDED_BITS + type2::NEEDED_BITS +
        type3::NEEDED_BITS + type4::NEEDED_BITS + type5::NEEDED_BITS>
struct Packed5Values : public Packed4Values<type1, type2, type3, type4, ALL_NEEDED_BITS> {

    typedef Packed4Values<type1, type2, type3, type4, ALL_NEEDED_BITS> parentType;
    typedef typename parentType::baseType baseType;

    enum
    {
        TYPE5_BIT_BASE = parentType::TYPE5_BIT_BASE,
        TYPE6_BIT_BASE = TYPE5_BIT_BASE + type5::NEEDED_BITS,
        TYPE5_BIT_MASK = MathPower<2,TYPE6_BIT_BASE>::value - MathPower<2,TYPE5_BIT_BASE>::value
    };

    public:
    void setValueForType5(type5 value)
    {
        typename parentType::packedType converted = value;
        parentType::mPacked &= ~TYPE5_BIT_MASK;
        parentType::mPacked |= (converted - type5::MIN_VALUE) << TYPE5_BIT_BASE;
    }

    type5 getValueForType5()
    {
        return ((parentType::mPacked & TYPE5_BIT_MASK) >> TYPE5_BIT_BASE) + type5::MIN_VALUE;
    }
};

template<class type1, class type2, class type3, class type4, class type5,
        class type6, int ALL_NEEDED_BITS = type1::NEEDED_BITS +
        type2::NEEDED_BITS + type3::NEEDED_BITS + type4::NEEDED_BITS +
        type5::NEEDED_BITS + type6::NEEDED_BITS>
struct Packed6Values : public Packed5Values<type1, type2, type3, type4, type5, ALL_NEEDED_BITS> {

    typedef Packed5Values<type1, type2, type3, type4, type5, ALL_NEEDED_BITS> parentType;
    typedef typename parentType::baseType baseType;

    enum
    {
        TYPE6_BIT_BASE = parentType::TYPE6_BIT_BASE,
        TYPE7_BIT_BASE = TYPE6_BIT_BASE + type6::NEEDED_BITS,
        TYPE6_BIT_MASK = MathPower<2,TYPE7_BIT_BASE>::value - MathPower<2,TYPE6_BIT_BASE>::value
    };

    public:
    void setValueForType6(type6 value)
    {
        typename parentType::packedType converted = value;
        baseType::mPacked &= ~TYPE6_BIT_MASK;
        baseType::mPacked |= (converted - type6::MIN_VALUE) << TYPE6_BIT_BASE;
    }

    type6 getValueForType6()
    {
        return ((baseType::mPacked & TYPE6_BIT_MASK) >> TYPE6_BIT_BASE) + type6::MIN_VALUE;
    }
};

template<class type1, class type2, class type3, class type4, class type5,
        class type6, class type7, int ALL_NEEDED_BITS = type1::NEEDED_BITS +
        type2::NEEDED_BITS + type3::NEEDED_BITS + type4::NEEDED_BITS +
        type5::NEEDED_BITS + type6::NEEDED_BITS + type7::NEEDED_BITS>
struct Packed7Values : public Packed6Values<type1, type2, type3, type4, type5,
        type6, ALL_NEEDED_BITS> {

    typedef Packed6Values<type1, type2, type3, type4, type5, type6,
            ALL_NEEDED_BITS> parentType;
    typedef typename parentType::baseType baseType;

    enum
    {
        TYPE7_BIT_BASE = parentType::TYPE7_BIT_BASE,
        TYPE8_BIT_BASE = TYPE7_BIT_BASE + type7::NEEDED_BITS,
        TYPE7_BIT_MASK = MathPower<2,TYPE8_BIT_BASE>::value - MathPower<2,TYPE7_BIT_BASE>::value
    };

    public:
    void setValueForType7(type7 value)
    {
        typename parentType::packedType converted = value;
        baseType::mPacked &= ~TYPE7_BIT_MASK;
        baseType::mPacked |= (converted - type7::MIN_VALUE) << TYPE7_BIT_BASE;
    }

    type7 getValueForType7()
    {
        return ((baseType::mPacked & TYPE7_BIT_MASK) >> TYPE7_BIT_BASE) + type7::MIN_VALUE;
    }
};

template<class type1, class type2, class type3, class type4,
        class type5, class type6, class type7, class type8,
        int ALL_NEEDED_BITS = type1::NEEDED_BITS + type2::NEEDED_BITS +
        type3::NEEDED_BITS + type4::NEEDED_BITS + type5::NEEDED_BITS +
        type6::NEEDED_BITS + type7::NEEDED_BITS + type8::NEEDED_BITS>
struct Packed8Values : public Packed7Values<type1, type2, type3, type4, type5,
        type6, type7, ALL_NEEDED_BITS> {

    typedef Packed7Values<type1, type2, type3, type4, type5, type6, type7,
            ALL_NEEDED_BITS> parentType;
    typedef typename parentType::baseType baseType;

    enum
    {
        TYPE8_BIT_BASE = parentType::TYPE8_BIT_BASE,
        TYPE9_BIT_BASE = TYPE8_BIT_BASE + type8::NEEDED_BITS,
        TYPE8_BIT_MASK = MathPower<2,TYPE9_BIT_BASE>::value - MathPower<2,TYPE8_BIT_BASE>::value
    };

    public:
    void setValueForType8(type8 value)
    {
        typename baseType::packedType converted = value;
        baseType::mPacked &= ~TYPE8_BIT_MASK;
        baseType::mPacked |= (converted - type8::MIN_VALUE) << TYPE8_BIT_BASE;
    }

    type8 getValueForType8()
    {
        return ((baseType::mPacked & TYPE8_BIT_MASK) >> TYPE8_BIT_BASE) + type8::MIN_VALUE;
    }
};

#endif // PACKED_VALUES_HPP
