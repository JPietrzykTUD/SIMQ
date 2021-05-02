#!/bin/bash
if [ -d "./arm_build" ]; then
    echo "RM"
    rm -rf arm_build
fi
mkdir arm_build && cd arm_build
cmake -DCPLATFORM=ARM ..
make
cd -
