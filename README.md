Benchmark Sorting Algorithms
===============================

Author: Piotr Pelczar (piotpel817@student.polsl.pl)

Silesian University of Technology, Algorithms and Data Structures course.

Full article is avaliable under:<br />
http://athlan.pl/incopy/polsl-benchmark-sort-algorithms/Main.pdf

### Abstract

This paper describes and compares counting sort and bucket sort algorithms implementations written in C language. The main doubt is what is the impact of pointers operations in *bucket sort* relatively to single operations on arrays in *counting sort*.

### Repository structure

* TeX paper is unser `article` directory
* Source code is under `code` directory
* `bin` directory contains some Bash scripts utils

### Results

**Counting sort is more effective than Bucket sort** (4.76 times in average and **5.91 times** for full optimization) in all cases for key range from 0 to 65k. Key range (in integer range) have no impact on time consumtion.

Moreover, **gcc optimization have huge impact for Bucket sort which has operations on pointers** (132% faster) and small impact for Counting sort (22% faster).

Operations on pointers can be strongly optimized and have huge impact on algorithms.

![](https://raw.github.com/athlan/polsl-benchmark-sort-algorithms/master/article/materials/compare-gcc-opt3.png)

![](https://raw.github.com/athlan/polsl-benchmark-sort-algorithms/master/article/materials/compare-gcc-opt-0and3.png)

### `./bin` usage

There are several utils in this project:

#### Programs compilation
```
./bin/compile.sh
```
or in all gcc modes:
```
./bin/compile-all-optimizations.sh
```
Results will be stored in `./target`

#### Generate random dataset
If you want to output COUNT numbers from MIN\_VALUE to MAX\_VALUE, each in new line, just type:
```
./bin/rand-dataset.sh MIN_VALUE MAX_VALUE COUNT > somefile.txt
```

#### Run benchmark
You can edit script and and run. Results are in CSV format, separated by semicolon.
```
./bin/run-benchmark.sh > some_results.csv
```

#### Article TeX compilation
To compile tex article, please ensure, taht you have `pdflatex` in your `$PATH` and run:
```
./bin/print-tex.sh
```
