# Memory Management Lab – mmap & munmap

This project demonstrates the usage of `mmap()` and `munmap()` system calls
in Linux to study virtual memory mapping.

## Files
- `mmap_example.c` : Sample program using mmap and munmap
- `testfile.txt`   : File mapped into virtual memory
- `README.md`      : Project description

## Experiment
The program maps a file into the virtual address space of the process and
observes changes using:
```bash
/proc/[pid]/maps
```
## Key Concepts
- Virtual Memory
- Memory Mapping
- Demand Paging
- mmap / munmap system calls
