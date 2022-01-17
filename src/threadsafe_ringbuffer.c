// Source Adapted from: https://cs241.cs.illinois.edu/coursebook/Synchronization#correct-implementation-of-a-ring-buffer

#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define RINGBUFFER_CAPACITY 16

typedef struct ringbuffer {
    int buffer[RINGBUFFER_CAPACITY];
    int reader_idx;
    int writer_idx;
    pthread_mutex_t mutex;
    sem_t not_full;
    sem_t not_empty;
} ringbuffer_t;

ringbuffer_t *create() {
    ringbuffer_t* new_ringbuffer = (ringbuffer_t*)malloc(sizeof(ringbuffer_t));
    new_ringbuffer->reader_idx = 0;
    new_ringbuffer->writer_idx = 0;
    pthread_mutex_init(&new_ringbuffer->mutex, NULL);
    sem_init(&new_ringbuffer->not_full, 0, RINGBUFFER_CAPACITY);
    sem_init(&new_ringbuffer->not_empty, 0, 0);
    return new_ringbuffer;
}

void destroy(ringbuffer_t* ringbuffer) {
    if (ringbuffer) {
        pthread_mutex_destroy(&ringbuffer->mutex);
        sem_destroy(&ringbuffer->not_empty);
        sem_destroy(&ringbuffer->not_full);
    }
}

void enqueue(ringbuffer_t *ringbuffer, int item) {
    // If the ringbuffer is full, wait on a signal once space is available from the dequeue function.
    sem_wait(&ringbuffer->not_full);

    pthread_mutex_lock(&ringbuffer->mutex);
    ringbuffer->buffer[ (ringbuffer->writer_idx & (RINGBUFFER_CAPACITY - 1)) ] = item;
    ++ringbuffer->writer_idx;
    pthread_mutex_unlock(&ringbuffer->mutex);

    // Signal any threads waiting that the ringbuffer is no longer empty.
    sem_post(&ringbuffer->not_empty);
}

int dequeue(ringbuffer_t *ringbuffer) {
    // If the ringbuffer is empty, wait for a signal that an item has been added from the enqueue function.
    sem_wait(&ringbuffer->not_empty);

    pthread_mutex_lock(&ringbuffer->mutex);
    int item = ringbuffer->buffer[ ( ringbuffer->reader_idx & (RINGBUFFER_CAPACITY - 1)) ];
    ++ringbuffer->reader_idx;
    pthread_mutex_unlock(&ringbuffer->mutex);

    // Signal any threads in enqueue that the buffer is no longer full. 
    sem_post(&ringbuffer->not_full);

    return item;
}

int main() {
    ringbuffer_t* ringbuffer = create();
    int value1 = 1;
    int value2 = 2;
    enqueue(ringbuffer, value1);
    enqueue(ringbuffer, value2);
    int val = dequeue(ringbuffer);
    printf("Dequeued value: %d\n", val);
    return 0;
}