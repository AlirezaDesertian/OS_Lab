#include <stdio.h>
#include <unistd.h>
#include "banker.h"
#include "chef.h"

char *chef_names[P] = {
    "Ghormeh Sabzi",
    "Joojeh Kabab",
    "Cake",
    "Pasta"
};

void *chef(void *arg) {
    int pid = *(int *)arg;

    printf("Chef %d (%s) is thinking...\n", pid, chef_names[pid]);
    sleep(1);

    int request[R];
    for (int i = 0; i < R; i++)
        request[i] = Max[pid][i];

    printf("Chef %d requests resources\n", pid);

    while (!request_resources(pid, request)) {
        printf("Chef %d waiting (unsafe state)...\n", pid);
        sleep(1);
    }

    printf("Chef %d is cooking \n", pid);
    sleep(2);

    release_resources(pid);
    printf("Chef %d finished and released resources \n", pid);

    return NULL;
}
