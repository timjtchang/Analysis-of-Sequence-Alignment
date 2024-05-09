# Analysis of Sequence Alignment using DP & Memory Efficient Algorithm

Implemnt sequency alighment using Dynamic Programming and using Memory Efficient Algorihthm

- Tim Chang

## Table of Contents

- datapoints:\
    Contains all the input data used for the analysis graph in the summary file.

- report_data:\
    Includes the time cost comparison graph for the basic algorithm and the memory-efficient algorithm, 
    as well as the memory usage graph for both algorithms.

- SampleTestCases:\
    Contains sample test cases.

- basic.cpp:\
    Source code for the basic algorithm.

- efficient.cpp:\
    Source code for the memory-efficient algorithm.

- basic.sh:\
    Bash script to compile and run the basic algorithm.

- efficient.sh:\
    Bash script to compile and run the memory-efficient algorithm.

- plot.py:\
    Plot two analysis graphs using Python.

- Summary.pdf:\
    Summarize the performance and analysis of the two algorithms."

- Makefile:\

    To compile basic.cpp and efficient.cpp
    ```bash
    $ make all
    ```

    To compile basic.cpp
    ```bash
    $ make basic
    ```

    To compile efficient.cpp
    ```bash
    $ make efficient
    ```

    To remove basic and efficient
    ```bash
    $ make clean
    ```
    

## Usage

- Run the basic algorithm implemented using dynamic programming:

    ```bash
    $ ./basic.sh "input file" "output file"
    ```

- Run the memory-efficient algorithm implemented using divide-and-conquer:

    ```bash
    $ ./efficient.sh "input file" "output file"

    ```
    
