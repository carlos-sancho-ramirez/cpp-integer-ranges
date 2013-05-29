
#include "packedValues.hpp"
#include <iostream>

typedef Packed2Values<StaticIntegerRange<0,9>, StaticIntegerRange<4,5> > packed2_t;
typedef Packed3Values<StaticIntegerRange<0,9>, StaticIntegerRange<4,5>, StaticIntegerRange<-5,5> > packed3_t;

using namespace std;

int main(int argc, char *argv[])
{
	// Pack of 2 values
    packed2_t pack2;
    pack2.setValueForType1(7);

    cout << "Product is " << (pack2.getValueForType1() * pack2.getValueForType2())
         << endl;

	// Pack of 3 values
	packed3_t pack3;
	pack3.setValueForType1(3);
	pack3.setValueForType2(5);
	pack3.setValueForType3(-2);

	cout << "Product is " << (pack3.getValueForType1() * pack3.getValueForType2()
			* pack3.getValueForType3()) << endl;

    return 0;
}
