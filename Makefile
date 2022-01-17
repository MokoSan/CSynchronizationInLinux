CC      = gcc
CFLAGS  = -I -Wall -lpthread -pthread
BIN     = bin

all: create_bin mutex condition_variables dining_philosophers epoll threadsafe_stack memory_barriers threadsafe_ringbuffer

create_bin:
	mkdir -p $(BIN) 

mutex:
	$(CC) src/mutex.c $(CFLAGS) -o $(BIN)/mutex

condition_variables:
	$(CC) src/condition_variables.c $(CFLAGS) -o $(BIN)/condition_variables

dining_philosophers:
	$(CC) src/dining_philosophers.c $(CFLAGS) -o $(BIN)/dining_philosophers

producer_consumer:
	$(CC) src/producer_consumer.c $(CFLAGS) -o $(BIN)/producer_consumer

epoll:
	$(CC) src/epoll.c $(CFLAGS) -o $(BIN)/epoll

sleeping_barber:
	$(CC) src/sleeping_barber.c $(CFLAGS) -o $(BIN)/sleeping_barber

threadsafe_stack:
	$(CC) src/threadsafe_stack.c $(CFLAGS) -o $(BIN)/threadsafe_stack

memory_barriers:
	$(CC) src/memory_barriers.c $(CFLAGS) -o $(BIN)/memory_barriers

threadsafe_ringbuffer:
	$(CC) src/threadsafe_ringbuffer.c $(CFLAGS) -o $(BIN)/threadsafe_ringbuffer 

clean:
	rm -rf ./bin