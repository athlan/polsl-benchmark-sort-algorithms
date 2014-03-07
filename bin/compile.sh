#!/bin/bash

cd code
gcc benchmark.c sort_algorithms/*.c -o ../target/benchmark
cd ..

chmod +x ./target/benchmark
