#include <stdio.h>
#include <pthread.h>
#include "banker.h"
#include "chef.h"

int main() {
    pthread_t threads[P];
    int ids[P];

    // Initialize Need matrix
    for (int i = 0; i < P; i++)
        for (int j = 0; j < R; j++)
            Need[i][j] = Max[i][j];

    for (int i = 0; i < P; i++) {
        ids[i] = i;
        pthread_create(&threads[i], NULL, chef, &ids[i]);
    }

    for (int i = 0; i < P; i++)
        pthread_join(threads[i], NULL);

    return 0;
}
