# Dining Philosophers Problem
This project implements the Dining Philosophers Problem as an Operating Systems laboratory experiment using C, POSIX threads (pthread), and semaphores.

## Description
- There are 5 philosophers sitting around a circular table.
- Each philosopher alternates between thinking and eating.
- To eat, a philosopher must pick up two adjacent chopsticks (left first, then right).
- Each philosopher is implemented as a separate thread.
- Each chopstick is represented by a binary semaphore.

The program continuously prints the state of each philosopher, including thinking, waiting for chopsticks, eating, and releasing resources.

## Note:

This implementation may lead to deadlock, as all philosophers pick up the left chopstick before the right one.

## Compilation

```bash
gcc main.c -o dining_philosophers -pthread
```
## Execution

```bash
./dining_philosophers
```
