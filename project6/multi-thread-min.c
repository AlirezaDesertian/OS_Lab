#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

int *A;
int *minArr;
int N;
int THREAD_COUNT;

typedef struct {
    int id;
    int start;
    int end;
} ThreadArg;

void* find_min(void *arg) {
    ThreadArg *t = (ThreadArg*)arg;

    int local_min = A[t->start];
    for (int i = t->start + 1; i <= t->end; i++) {
        if (A[i] < local_min)
            local_min = A[i];
    }

    minArr[t->id] = local_min;

    pthread_exit(NULL);
}

long long current_time_ms() {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    long long ms = ts.tv_sec * 1000LL + ts.tv_nsec / 1000000LL;
    return ms;
}

int main() {
    printf("Enter N: ");
    scanf("%d", &N);

    printf("Enter thread count: ");
    scanf("%d", &THREAD_COUNT);

    A = malloc(sizeof(int) * N);
    minArr = malloc(sizeof(int) * THREAD_COUNT);

    srand(time(NULL));
    for (int i = 0; i < N; i++)
        A[i] = rand() % 1000000;

    long long t1 = current_time_ms();

    int single_min = A[0];
    for (int i = 1; i < N; i++)
        if (A[i] < single_min)
            single_min = A[i];

    long long t2 = current_time_ms();
    long long single_time = t2 - t1;

    pthread_t threads[THREAD_COUNT];
    ThreadArg args[THREAD_COUNT];

    int chunk = N / THREAD_COUNT;

    long long t3 = current_time_ms();

    for (int i = 0; i < THREAD_COUNT; i++) {
        args[i].id = i;
        args[i].start = i * chunk;

        if (i == THREAD_COUNT - 1)
            args[i].end = N - 1;
        else
            args[i].end = (i + 1) * chunk - 1;

        pthread_create(&threads[i], NULL, find_min, (void*)&args[i]);
    }

    for (int i = 0; i < THREAD_COUNT; i++)
        pthread_join(threads[i], NULL);

    long long t4 = current_time_ms();
    long long multi_time = t4 - t3;

    int final_min = minArr[0];
    for (int i = 1; i < THREAD_COUNT; i++)
        if (minArr[i] < final_min)
            final_min = minArr[i];

    printf("\nMin of each thread:\n");
    for (int i = 0; i < THREAD_COUNT; i++)
        printf("Thread %d -> %d\n", i, minArr[i]);

    printf("\nFinal minimum (multi-thread): %d\n", final_min);
    printf("Single-thread min: %d\n", single_min);

    printf("\nSingle-thread time: %lld ms\n", single_time);
    printf("Multi-thread time:  %lld ms\n", multi_time);

    free(A);
    free(minArr);

    return 0;
}
