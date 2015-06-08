#!/bin/bash

if [ $# -ge 2 ]; then
    r=$2
else
    r="a.rhobj"
fi

if [ $# -ge 3 ]; then
    t=$3
else
    t=0.0
fi

../src/build/rhock-as $1 &&
../src/build/rhock $r -e -t $t
