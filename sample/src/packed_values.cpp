
#include "packedValues.hpp"
#include <iostream>

typedef Packed2Values<StaticIntegerRange<0,9>, StaticIntegerRange<4,5> > packed2_t;
typedef Packed3Values<StaticIntegerRange<0,9>, StaticIntegerRange<4,5>, StaticIntegerRange<-5,5> > packed3_t;
typedef StaticIntegerRange<0,1> bool_t;
typedef Packed8Values<bool_t, bool_t, bool_t, bool_t, bool_t, bool_t, bool_t, bool_t> flags_t;
using namespace std;

int main(int argc, char *argv[])
{
	// Pack of 2 values
    packed2_t pack2;
    pack2.setValueForType1(7);

    cout << "Product is " << (pack2.getValueForType1() * pack2.getValueForType2())
         << endl;
    cout << "This pack has a size of " << sizeof(packed2_t) << " bytes in memory" << endl;

	// Pack of 3 values
	packed3_t pack3;
	pack3.setValueForType1(3);
	pack3.setValueForType2(5);
	pack3.setValueForType3(-2);

	cout << "Product is " << (pack3.getValueForType1() * pack3.getValueForType2()
			* pack3.getValueForType3()) << endl;
    cout << "This pack has a size of " << sizeof(packed3_t) << " bytes in memory" << endl;

    // Pack of 8 booleans
	flags_t flags;
	flags.setValueForType1(0);
	flags.setValueForType2(1);
	flags.setValueForType3(0);
	flags.setValueForType4(1);
	flags.setValueForType5(0);
	flags.setValueForType6(1);
	flags.setValueForType7(1);
	flags.setValueForType8(1);

    const int ones = flags.getValueForType1() + flags.getValueForType2() +
            flags.getValueForType3() + flags.getValueForType4() + flags.getValueForType5() +
            flags.getValueForType6() + flags.getValueForType7() + flags.getValueForType8();

	cout << "There is " << ones << " flags set" << endl;
    cout << "This pack has a size of " << sizeof(flags_t) << " bytes in memory" << endl;

    return 0;
}
