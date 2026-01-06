#include <stdio.h>
#include <pthread.h>
#include "banker.h"

// Available resources
int Available[R] = {2, 1, 1};

// Maximum demand of each chef
int Max[P][R] = {
    {1, 1, 0}, // Chef 0
    {1, 0, 1}, // Chef 1
    {0, 1, 1}, // Chef 2
    {1, 0, 0}  // Chef 3
};

int Allocation[P][R] = {0};
int Need[P][R];

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

// Safety algorithm
static bool is_safe() {
    int Work[R];
    bool Finish[P] = {false};

    for (int i = 0; i < R; i++)
        Work[i] = Available[i];

    while (1) {
        bool found = false;

        for (int i = 0; i < P; i++) {
            if (!Finish[i]) {
                bool possible = true;
                for (int j = 0; j < R; j++) {
                    if (Need[i][j] > Work[j]) {
                        possible = false;
                        break;
                    }
                }

                if (possible) {
                    for (int j = 0; j < R; j++)
                        Work[j] += Allocation[i][j];

                    Finish[i] = true;
                    found = true;
                }
            }
        }

        if (!found)
            break;
    }

    for (int i = 0; i < P; i++)
        if (!Finish[i])
            return false;

    return true;
}

// Request resources
bool request_resources(int pid, int request[]) {
    pthread_mutex_lock(&mutex);

    for (int i = 0; i < R; i++) {
        if (request[i] > Need[pid][i] ||
            request[i] > Available[i]) {
            pthread_mutex_unlock(&mutex);
            return false;
        }
    }

    // Temporary allocation
    for (int i = 0; i < R; i++) {
        Available[i] -= request[i];
        Allocation[pid][i] += request[i];
        Need[pid][i] -= request[i];
    }

    if (!is_safe()) {
        // Rollback
        for (int i = 0; i < R; i++) {
            Available[i] += request[i];
            Allocation[pid][i] -= request[i];
            Need[pid][i] += request[i];
        }
        pthread_mutex_unlock(&mutex);
        return false;
    }

    pthread_mutex_unlock(&mutex);
    return true;
}

// Release resources
void release_resources(int pid) {
    pthread_mutex_lock(&mutex);

    for (int i = 0; i < R; i++) {
        Available[i] += Allocation[pid][i];
        Allocation[pid][i] = 0;
    }

    pthread_mutex_unlock(&mutex);
}
