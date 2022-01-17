#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX_BUFFER_SIZE 10

typedef struct stack {
    int count;
    pthread_mutex_t mutex;
    double *values;
} stack_t;

stack_t *create_stack() {
    stack_t *new_stack = (stack_t*)malloc(sizeof(stack_t));
    new_stack->count = 0;
    pthread_mutex_init(&new_stack->mutex, NULL);
    new_stack->values = (double*)malloc(sizeof(double) * MAX_BUFFER_SIZE);
    return new_stack;
}

void delete_stack(stack_t *stack) {
    if (stack) {
        free(stack->values);
        pthread_mutex_destroy(&stack->mutex);
        free(stack);
    }
}

bool __is_full(stack_t *stack) {
    return stack->count == MAX_BUFFER_SIZE; 
}

bool is_full(stack_t *stack) {
    bool full = false;
    pthread_mutex_lock(&stack->mutex);
    full = __is_full(stack);
    pthread_mutex_unlock(&stack->mutex);
    return full;
}

bool push(stack_t *stack, double value) {
    bool full = false; 
    pthread_mutex_lock(&stack->mutex);
    full = __is_full(stack); 
    if (!full) {
        stack->values[stack->count] = value;
        ++stack->count;
    }
    pthread_mutex_unlock(&stack->mutex);

    return full ? false : true;
}

bool __is_empty(stack_t *stack) {
    return stack->count == 0;
}

bool is_empty(stack_t *stack) {
    bool empty = false;
    pthread_mutex_lock(&stack->mutex);
    empty = stack->count == 0;
    pthread_mutex_unlock(&stack->mutex);
    return empty;
}

int pop(stack_t *stack) {
    bool empty = false;
    int ret_val = -1;
    pthread_mutex_lock(&stack->mutex);
    empty = __is_empty(stack);
    if (!empty) {
        ret_val = stack->values[stack->count];
        --stack->count;
    }
    pthread_mutex_unlock(&stack->mutex);

    return empty ? -1 : ret_val;
}

void print_stack(stack_t *stack) {
    pthread_mutex_lock(&stack->mutex);
    for(int i = stack->count - 1; i >= 0; i--) {
        printf("%f\n", stack->values[i]);
    }
    pthread_mutex_unlock(&stack->mutex);
}

int main() {
    stack_t *stack = create_stack();
    push(stack, 1);
    push(stack, 2);
    push(stack, 3);
    print_stack(stack);
    printf("\n");
    pop(stack);
    pop(stack);
    push(stack, 2);
    print_stack(stack);
    delete_stack(stack);
    return 0;
}