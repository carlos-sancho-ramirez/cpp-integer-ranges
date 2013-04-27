#!/bin/sh

mkdir test

# This compilation should fail as RANGE_MIN > RANGE_MAX
g++ src/StaticIntegerRange.cpp -I../lib/src -std=c++0x -o test/test -DRANGE_MIN=8 -DRANGE_MAX=7 > /dev/null 2> /dev/null
if [ $? == "0" ]; then
    echo "Test failed: Program compiling for RANGE_MIN > RANGE_MAX"
    exit 1
else
    echo "Test passed: Program not compiling for RANGE_MIN > RANGE_MAX"
fi

# This compilation should work RANGE_MIN + 1 == RANGE_MAX
g++ src/StaticIntegerRange.cpp -I../lib/src -std=c++0x -o test/test -DRANGE_MIN=-4 -DRANGE_MAX=-3 > /dev/null
if [ $? == "0" ]; then
    echo "Test passed: Program compiling for RANGE_MIN == RANGE_MAX"
else
    echo "Test failed: Program not compiling for RANGE_MIN == RANGE_MAX"
    exit 1
fi

g++ src/StaticIntegerRange.cpp -I../lib/src -std=c++0x -o test/test > /dev/null 2> /dev/null
./test/test

rm -r test
