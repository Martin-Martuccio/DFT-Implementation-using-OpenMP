# DFT Implementation using OpenMP

## Overview

This project demonstrates the parallelization and optimization of the Discrete Fourier Transform (DFT) algorithm using OpenMP to enhance performance and minimize execution time. The focus is on vectorization, parallel execution, and thread management to achieve significant performance improvements.

## Contents

- **Introduction**: Overview of the DFT algorithm and its computational challenges, along with the need for parallelization to improve performance.
  
- **Compilation and Execution**: Description of how the program is compiled using the Intel C Compiler (ICC) and executed with different optimization flags to exploit hardware features such as SIMD and multi-threading.

- **Performance Analysis**:
  - **Hotspot Identification**: Analysis of the computational hotspots in the DFT algorithm, particularly in the nested loops.
  - **Vectorization**: Discussion on vectorization strategies, alignment issues, and their impact on performance.
  - **Thread Optimization**: Evaluation of performance with varying numbers of threads and optimization flags.

## How to Compile and Run

To compile and run the code using OpenMP, follow these steps:

### Compiling with OpenMP
1. Use the Intel C Compiler (ICC) to compile the program with OpenMP support:
   ```bash
   icc -O2 -xHost -qopenmp dft_openmp.c -o dft_openmp

FLAGS : 
  - O2: Enables optimizations. ( Try -O1 -O2 -O3 -Ofast)
  - xHost: Generates instructions for the highest instruction set available on the machine.
  - qopenmp: To create a report.
  - dft_openmp.c is an example of the file's name. Use the right name.

2. Run the program:
   ```bash
   ./dft_openmp

### Performance Metrics
The performance of the DFT algorithm was measured in terms of:

**Execution Time** : Time taken to compute the DFT with different optimization levels and thread counts.
**Speedup**: Ratio of the execution time on a single processor to the execution time on multiple processors.
**Efficiency**: Measurement of how well the system's resources are utilized relative to the number of threads.

### Conclusion
The parallelization of the DFT algorithm using OpenMP resulted in substantial performance gains, especially when vectorization, multi-threading, and architecture-specific optimizations were employed. The optimal configuration was found using 32/64 threads and higher optimization levels.

For more details on the performance analysis, graphs, and implementation specifics, please refer to the full report available in this repository. Report : [Report Link]( ... )

## Authors
- [Martin Martuccio](https://github.com/Martin-Martuccio) - Project Author
- [Lorenzo Mesi](https://github.com/LorenzoMesi) - Project Author

![Build Status](https://img.shields.io/badge/build-passing-brightgreen)
![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)

