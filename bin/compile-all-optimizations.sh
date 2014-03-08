#!/bin/bash

pushd ./code
gcc -O0 benchmark.c sort_algorithms/*.c -o ../target/benchmark-o0
gcc -O1 benchmark.c sort_algorithms/*.c -o ../target/benchmark-o1
gcc -O2 benchmark.c sort_algorithms/*.c -o ../target/benchmark-o2
gcc -O3 benchmark.c sort_algorithms/*.c -o ../target/benchmark-o3
popd

chmod +x ./target/benchmark*
