CC      = gcc
CFLAGS  = -I -Wall -lpthread
BIN     = bin

all: create_bin mutex condition_variables dining_philosophers epoll

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

clean:
	rm -rf ./bin