# IPC Pipe Example in C (Parent–Child)

This project demonstrates basic Inter‑Process Communication (IPC) using two Unix pipes and `fork()` in C.  
The parent process sends an integer array to the child, and the child returns two values:  
1. The sum of all elements  
2. The count of even numbers  

Only the following system calls are used:  
`pipe(), fork(), read(), write(), close(), wait()`  
No `dup()` or `dup2()` are used.

## How it works
- `pipe1`: Parent → Child  
- `pipe2`: Child → Parent  
- The parent writes the array into `pipe1`.  
- The child reads the array, computes the results, and sends them back through `pipe2`.

## Build
Compile with GCC:
```bash
gcc pipe_os.c -o pipe_os
```

## Run
```bash
./pipe_os
```

## Output Example
```bash
Sum = 58
Even Count = 6
```
