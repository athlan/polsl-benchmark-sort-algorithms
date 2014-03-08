#!/bin/bash

pushd ./code
gcc benchmark.c sort_algorithms/*.c -o ../target/benchmark
popd

chmod +x ./target/benchmark
