// Code adapted from: https://suchprogramming.com/epoll-in-3-easy-steps/

#include <sys/epoll.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#define MAX_EVENTS 5
#define READ_SIZE 10 

int main() {
    int running = 1;
    int event_count = 0;
    int idx = 0;

    char read_buffer[READ_SIZE + 1];
    size_t bytes_read;

    struct epoll_event event;
    event.events  = EPOLLIN;
    event.data.fd = 0;

    struct epoll_event events[MAX_EVENTS];

    int epoll_fd = epoll_create1(0);

    if (epoll_fd == -1) {
        fprintf(stderr, "Failed to create epoll file descriptor.\n");
        return 1;
    }

    // Add the event to the epoll file descriptor.
    if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, 0, &event)) {
        fprintf(stderr, "Failed to add file descriptor to epoll\n");
        close(epoll_fd);
        return 1;
    }

    while(running) {
        printf("\nPolling for input..\n");
        event_count = epoll_wait(epoll_fd, events, MAX_EVENTS, 30000);
        printf("%d ready events\n", event_count);
        for(int i = 0; i < event_count; i++) {
            printf("Reading file descriptor '%d' --  ", events[i].data.fd);
            bytes_read = read(events[i].data.fd, read_buffer, READ_SIZE);
            printf("%zd bytes read. \n", bytes_read);
            printf("Read '%s'\n", read_buffer);


            if (!strncmp(read_buffer, "stop\n", 5)) {
                running = 0;
            }
        }
    }

    if (close(epoll_fd)) {
        fprintf(stderr, "Failed to close epoll file descriptor.\n");
        return 1;
    }

    return 0;
}