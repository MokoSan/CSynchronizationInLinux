#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

pthread_mutex_t lock;
pthread_t tid[2];
int counter = 0;

void* try_this(void* args) {
    pthread_mutex_lock(&lock);

    unsigned long i = 0;
    ++counter;

    printf("Job %d has started \n", counter);
    for (i = 0; i < (0xFFFFFFFF); i++);
    printf("Job %d has finished \n", counter);

    pthread_mutex_unlock(&lock);
    return NULL;
}

int main() {
    int i = 0;
    int error;

    if (pthread_mutex_init(&lock, NULL) != 0) {
        printf("Mutex is not initialized!\n");
        return 1;
    }

    while (i < 2) {
        error = pthread_create(&(tid[i]), NULL, &try_this, NULL);
        if (error != 0) {
            printf("Thread cannot be created: [%s]\n", strerror(error));
        }

        ++i;
    }

    pthread_join(tid[0], NULL);
    pthread_join(tid[1], NULL);
    pthread_mutex_destroy(&lock);

    return 0;
}