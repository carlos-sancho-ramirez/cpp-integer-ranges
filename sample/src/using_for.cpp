
#include "IntegerRanges.hpp"
#include <iostream>

using namespace std;

typedef StaticIntegerRange<0,5> myInt_t;

/**
 * Expected output is:
 *  index has value 0
 *  index has value 1
 *  index has value 2
 *  index has value 3
 *  index has value 4
 *  index has value 5
 *  OutOfRangeError thrown!
 */
int main(int args, char *argv[])
{
    try
    {
        for (myInt_t index = 0; index < 10; index++ )
        {
            cout << "index has value " << static_cast<int>(index) << endl;
        }

        cout << "Finished with no error" << endl;
    }
    catch(OutOfRangeError error)
    {
        cout << "OutOfRangeError thrown!" << endl;
    }

    return 0;
}
