// Code adapted from: https://medium.com/swlh/the-dining-philosophers-problem-solution-in-c-90e2593f64e8

#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t room;
sem_t chopstick[5];

void eat(int phil) {
    printf("Philosopher %d is eating.\n", phil);
    printf("Philosopher %d has finished eating\n", phil);
}

void* philosopher(void* num) {
    int phil = *(int*)num;

    // Wait till the philosopher can enter the room.
    printf("Philosopher %d wants to enter the room\n", phil);

    sem_wait(&room);

    printf("Philosopher %d has entered the room\n", phil);
    
    // The philosopher picks up the chopstick to the right.
    sem_wait(&chopstick[phil]);

    // The philosopher picks up the chopstick to his left. 
    sem_wait(&chopstick[(phil + 1) % 5]);

    eat(phil);

    // Release the chopstick to the left and right in the opposite order.
    sem_post(&chopstick[(phil + 1) % 5]);
    sem_post(&chopstick[phil]);
    sem_post(&room);
}

int main() {

    pthread_t philosopher_threads[5];
    int philosopher_num[5];

    // The room has only 4 seats but there are 5 philosophers.
    sem_init(&room, 0, 4);

    // Initialize chopsticks i.e. semaphores.
    for(int i = 0; i < 5; i++) {
        sem_init(&chopstick[i], 0, 1);
    }

    printf("Done with the initialization of the chopsticks.\n");

    // Create threads.
    for(int i = 0; i < 5; i++) {
        philosopher_num[i] = i;
        pthread_create(&philosopher_threads[i], NULL, philosopher, (void*)&philosopher_num[i]);
    }

    printf("Done creating threads\n"); 

    // Join threads.
    for(int i = 0; i < 5; i++) {
        printf("Thread: %d is planning to join.\n", i);
        pthread_join(philosopher_threads[i], NULL);
        printf("Thread: %d has finished joining.\n", i);
    }

    printf("Done!\n");
    return 0;
}