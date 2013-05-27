
#include "packedValues.hpp"
#include <iostream>

typedef PackedValues<StaticIntegerRange<0,9>, StaticIntegerRange<4,5> > packed_t;

using namespace std;

int main(int argc, char *argv[])
{
    packed_t pack;
    pack.setValueForType1(7);

    cout << "Product is " << (pack.getValueForType1() * pack.getValueForType2())
         << endl;

    return 0;
}
