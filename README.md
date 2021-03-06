# Synchronization with C And Linux

This repository contains a set of examples related to synchronization and multithreading with C in Linux.

## Compiling all examples

To compile all examples simply run:

```
make
```

The binaries will be created in the ``bin`` folder.

## Examples

| Example | File | Purpose |
| ------- | ---- | ------- |
| Mutexes | [``mutex.c``](src/mutex.c) | Demonstrates how the ``pthread_mutex_create``, ``pthread_mutex_lock``, ``pthread_mutex_unlock`` calls are used. |
| Condition Variables | [``condition_variables.c``](src/condition_variables.c) | Demonstrates how ``pthread_cond_t`` based calls work for signaling. |
| Dining Philosophers | [``dining_philosophers.c``](src/dining_philosophers.c) | Solves the [dining philosopher's problem](https://en.wikipedia.org/wiki/Dining_philosophers_problem) using binary and counting semaphores. |
| Producer Consumer | [``producer_consumer.c``](src/producer_consumer.c) | Demonstrates the producer-consumer model in action using threads, a mutex and semaphores. | 
| Epoll | [``epoll.c``](src/epoll.c) | Demonstrates the usage of epoll using the level trigged event notifications. |
| Thread Safe Stack | [``threadsafe_stack.c``](src/threadsafe_stack.c) | An implementation of a thread safe stack. | 
| Memory Barrier Usage | [``memory_barriers.c``](src/memory_barriers.c) | Demonstrating the usage of a memory barrier. | 
| Thread Safe Ringbuffer | [``threadsafe_ringbuffer.c``](src/threadsafe_ringbuffer.c) | An implementation of a thread safe ringbuffer. | 

## Motivation

I realized I have been fairly rusty on my C code, especially in Linux. Decided to create this repository to refresh my memory and study different aspects of multithreading and synchronization.