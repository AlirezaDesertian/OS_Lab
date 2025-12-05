# Multithreaded Minimum Finder (C, pthreads)

This project implements a multithreaded program in C that finds the minimum value of an integer array. The array is divided among several threads, each thread computes the minimum of its own segment, and the main thread computes the final global minimum.

## Features
- Dynamic array size (N) and thread count.
- Array automatically filled with random integers.
- Each thread computes the minimum of its assigned segment.
- No synchronization primitives are required (each thread writes to its own index).
- Final minimum is calculated in the main thread.
- Execution time is measured for:
  - Single‑threaded version
  - Multi‑threaded version
- Allows performance comparison and speedup analysis.

## How It Works
1. The program generates an array of size `N`.
2. The array is evenly divided among `T` threads.
3. Each thread computes a local minimum and stores it in a shared `minArr[T]` array (no race conditions).
4. The main thread waits for all threads (`pthread_join`) and then computes the global minimum.
5. Execution time is recorded using `clock_gettime(CLOCK_MONOTONIC)`.

## Build & Run
Compile with:
```bash
gcc -o mt multi-thread-min.c -lpthread
```
Run:
```bash
./mt
```

You will be prompted for:
- Array size (N)
- Number of threads

## Output
The program prints:
- Minimum value found by each thread
- Final global minimum
- Single‑thread execution time (ms)
- Multi‑thread execution time (ms)

## Requirements
- GCC
- pthreads library
- Linux environment (tested on Debian)
