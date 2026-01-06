#ifndef BANKER_H
#define BANKER_H

#include <stdbool.h>

#define P 4   // number of chefs
#define R 3   // number of resources

// 0: Stove, 1: Oven, 2: Mixer
extern int Available[R];
extern int Max[P][R];
extern int Allocation[P][R];
extern int Need[P][R];

bool request_resources(int pid, int request[]);
void release_resources(int pid);

#endif
