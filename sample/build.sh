#!/bin/sh

BUILD_FOLDER=built
mkdir -p $BUILD_FOLDER

g++ src/using_for.cpp -I../lib/src -std=c++0x -o $BUILD_FOLDER/using_for
echo "Compiled using_for.cpp"

g++ src/debug_switch.cpp -I../lib/src -std=c++0x -o $BUILD_FOLDER/debug_switch_disabled
echo "Compiled debug_switch.cpp when CHECK_RANGES is undeclared"

g++ src/debug_switch.cpp -I../lib/src -std=c++0x -o $BUILD_FOLDER/debug_switch_enabled -DCHECK_RANGES=1
echo "Compiled debug_switch.cpp when CHECK_RANGES is declared"

g++ src/packed_values.cpp -I../lib/src -std=c++0x -o $BUILD_FOLDER/packed_values
echo "Compiled packed_values.cpp"
