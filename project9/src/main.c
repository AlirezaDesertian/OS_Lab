#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define N 5   // Number of philosophers

sem_t chopstick[N];
pthread_t philosophers[N];
int id[N] = {0, 1, 2, 3, 4};

void* philosopher(void* arg)
{
    int i = *(int*)arg;
    int left = i;
    int right = (i + 1) % N;

    while (1)
    {
        // Thinking
        printf("Philosopher %d is thinking.\n", i);
        sleep(1);

        // Pick up left chopstick
        printf("Philosopher %d is waiting for left chopstick (%d).\n", i, left);
        sem_wait(&chopstick[left]);
        printf("Philosopher %d picked up left chopstick (%d).\n", i, left);

        // Pick up right chopstick
        printf("Philosopher %d is waiting for right chopstick (%d).\n", i, right);
        sem_wait(&chopstick[right]);
        printf("Philosopher %d picked up right chopstick (%d).\n", i, right);

        // Eating
        printf("Philosopher %d is eating.\n", i);
        sleep(2);

        // Release chopsticks
        sem_post(&chopstick[left]);
        sem_post(&chopstick[right]);
        printf("Philosopher %d released the chopsticks and returned to thinking.\n\n", i);
    }

    return NULL;
}

int main()
{
    // Initialize semaphores
    for (int i = 0; i < N; i++)
        sem_init(&chopstick[i], 0, 1);

    // Create threads
    for (int i = 0; i < N; i++)
        pthread_create(&philosophers[i], NULL, philosopher, &id[i]);

    // Wait for threads (the program runs indefinitely)
    for (int i = 0; i < N; i++)
        pthread_join(philosophers[i], NULL);

    // Destroy semaphores (never reached)
    for (int i = 0; i < N; i++)
        sem_destroy(&chopstick[i]);

   return 0;
}

