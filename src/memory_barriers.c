// Source adapted from: https://cs241.cs.illinois.edu/coursebook/Synchronization#barriers

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#define THREAD_COUNT 4

pthread_barrier_t barrier;

void *thread_function(void *id) {
    int thread_id = *(int*)id;
    int wait_seconds = 1 + rand() % 5; 
    printf("thread %d: Wait for %d seconds.\n", thread_id, wait_seconds);
    sleep(wait_seconds);
    printf("thread %d, I am ready.\n", thread_id);
    pthread_barrier_wait(&barrier);
    printf("thread %d is active.\n", thread_id);
    return NULL;
}

int main() {
    int i;
    pthread_t thread_ids[THREAD_COUNT];
    int ids[THREAD_COUNT];

    pthread_barrier_init(&barrier, NULL, THREAD_COUNT + 1);

    // Initialize and start all threads.
    for(int i = 0; i < THREAD_COUNT; i++) {
        ids[i] = i;
        pthread_create(&thread_ids[i], NULL, thread_function, &ids[i]);
    }

    printf("Ready and waiting for all threads.\n");

    pthread_barrier_wait(&barrier);

    for(int i = 0; i < THREAD_COUNT; i++) {
        pthread_join(thread_ids[i], NULL);
    }

    pthread_barrier_destroy(&barrier);
    return 0;
}