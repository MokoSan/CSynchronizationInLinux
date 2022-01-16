// Code Adapted from: https://shivammitra.com/c/producer-consumer-problem-in-c/#

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define MAX_ITEMS 5
#define BUFFER_SIZE 5
#define PRODUCER_THREAD_COUNT 5
#define CONSUMER_THREAD_COUNT 5

int buffer[BUFFER_SIZE];
int producer_idx = 0;
int consumer_idx = 0;

pthread_mutex_t mutex; 
sem_t empty;
sem_t full;

// Fills in a buffer to capacity and signals consumers to consume.
void *producer(void *producer_id) {
    for(int i = 0; i < MAX_ITEMS; i++) {
        int item_to_consume = rand();

        // Wait on the buffer to be empty.
        sem_wait(&empty);

        // Lock to synchronize. 
        pthread_mutex_lock(&mutex);

        buffer[producer_idx] = item_to_consume;
        printf("Producer %d: Produced item: %d at %d\n", (*((int*)producer_id), item_to_consume, buffer[producer_idx]));
        producer_idx = (producer_idx + 1) % BUFFER_SIZE;

        // Unlock to release.
        pthread_mutex_unlock(&mutex);

        // Post to notify that an item is ready to be consumed.
        sem_post(&full);
    }
}

void *consumer(void *consumer_id) {
    for(int i = 0; i < MAX_ITEMS; i++) {

        // Wait on an item from the producer.
        sem_wait(&full);

        // Lock to synchronize.
        pthread_mutex_lock(&mutex);

        int item_to_consume = buffer[consumer_idx];
        printf("Consumer %d: Consumed item: %d from %d\n", (*(int*)consumer_id), item_to_consume, consumer_idx);
        consumer_idx = (consumer_idx + 1) % BUFFER_SIZE;

        // Unlock to release.
        pthread_mutex_unlock(&mutex);

        // Post to notify that more items are ready to be consumed.
        sem_post(&empty);
    }
}

int main() {
    // Declare the threads for producers and consumers.
    pthread_t producers[PRODUCER_THREAD_COUNT];
    pthread_t consumers[CONSUMER_THREAD_COUNT];

    // Declare the identities of the producers and consumers.
    int producer_ids[PRODUCER_THREAD_COUNT];
    for(int i = 0; i < PRODUCER_THREAD_COUNT; i++) {
        producer_ids[i] = i;
    }
    int consumer_ids[PRODUCER_THREAD_COUNT];
    for(int i = 0; i < CONSUMER_THREAD_COUNT; i++) {
        consumer_ids[i] = i;
    }

    // Initialize the mutex + semaphores.
    pthread_mutex_init(&mutex, NULL);
    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);

    // Create the producer and consumer threads.
    for(int i = 0; i < PRODUCER_THREAD_COUNT; i++) {
        pthread_create( &producers[i], NULL, (void*)producer, (void*)&producer_ids[i]);
    }

    for(int i = 0; i < CONSUMER_THREAD_COUNT; i++) {
        pthread_create( &consumers[i], NULL, (void*)consumer, (void*)&consumer_ids[i]);
    }

    // Join all the threads for both the producers and consumers.
    for(int i = 0; i < PRODUCER_THREAD_COUNT; i++) {
        pthread_join(producers[i], NULL);
    }

    for(int i = 0; i < CONSUMER_THREAD_COUNT; i++) {
        pthread_join(consumers[i], NULL);
    }

    // Destroy the mutex + semaphores.
    pthread_mutex_destroy(&mutex);
    sem_destroy(&empty);
    sem_destroy(&full);

    return 0;
}