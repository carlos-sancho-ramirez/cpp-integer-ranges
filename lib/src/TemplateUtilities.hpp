
#ifndef TEMPLATE_UTILITIES_HPP
#define TEMPLATE_UTILITIES_HPP

/**
 * StaticAssert will be only defined if the boolean given as a parameter is true.
 * This means StaticAssert<expression> can be used to evaluate in compile time
 * if the expression is already true. If false, the linker will complain.
 */
template<bool CHECK>
struct StaticAssert;

template<>
struct StaticAssert<true>
{
    enum
    {
        value = 1
    };
};


/**
 * Allows calculating powers in compile time.
 *
 * Example: 2^5, which is 32, can be calculated in compile time by retrieving
 * the value in MathPower<2,5>::value
 */
template<int base, unsigned int exponent>
struct MathPower
{
    enum : int
    {
        value = base * MathPower<base, exponent - 1>::value
    };
};

template<int base>
struct MathPower<base,0>
{
    enum : int
    {
        value = 1
    };
};


/**
 * MathLog retrieves the floor integer representation of the result of
 * calculating the logarithm of a given base.
 *
 * Example:
 *  * the logarithm of 5 for base 2 is 2.3219.
 *  * the floor integer is in this case 2 (I mean by floor removing the decimal
 *    cyphers).
 *  * Then, in compile time this value can be extracted by retrieving the value
 *    at MathLog<5,2>::value.
 */
template<int num, int base, unsigned int count>
struct MathLogInternal
{
    enum : int
    {
        value = MathLogInternal<num / base, base, count + 1>::value
    };
};

template<int base, unsigned int count>
struct MathLogInternal<0, base, count>
{
    enum : int
    {
        value = count
    };
};

template<int num, int base>
struct MathLog
{
    enum : int
    {
        value = MathLogInternal<num,base,0>::value
    };
};

#endif //TEMPLATE_UTILITIES_HPP
