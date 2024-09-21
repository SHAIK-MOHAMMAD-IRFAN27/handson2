/*
name: problem22.c
author: SHAIK  MOHAMMAD IRFAN 
description: Write a program to wait for data to be written into FIFO within 10 seconds, use select 
system call with FIFO. 
 date : 20th September 2024
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/select.h>

#define FIFO_NAME "fifooo"
#define BUFFER_SIZE 1024

int main() {
    // Check if FIFO already exists
    if (access(FIFO_NAME, F_OK) == 0) {
        printf("FIFO %s already exists.\n", FIFO_NAME);
    } else {
        // Create the FIFO using mknod
        if (mknod(FIFO_NAME, S_IFIFO | 0666, 0) == -1) {
            perror("Failed to create FIFO using mknod");
            exit(EXIT_FAILURE);
        }
        printf("FIFO %s created successfully.\n", FIFO_NAME);
    }

    // Open the FIFO for reading
    int fd = open(FIFO_NAME, O_RDONLY | O_NONBLOCK);
    if (fd == -1) {
        perror("Open FIFO for reading failed");
        exit(EXIT_FAILURE);
    }

    // Use select to wait for data
    fd_set read_fds;
    struct timeval timeout;
    char buffer[BUFFER_SIZE];

    // Set up the timeout
    timeout.tv_sec = 10; // 10 seconds
    timeout.tv_usec = 0;

    // Clear the set and add the FIFO to it
    FD_ZERO(&read_fds);
    FD_SET(fd, &read_fds);

    printf("Waiting for data in FIFO for 10 seconds...\n");

    // Wait for data or timeout
    int activity = select(fd + 1, &read_fds, NULL, NULL, &timeout);
    if (activity < 0) {
        perror("select error");
        close(fd);
        exit(EXIT_FAILURE);
    } else if (activity == 0) {
        printf("Timeout occurred! No data after 10 seconds.\n");
    } else {
        // Data is available to read
        read(fd, buffer, BUFFER_SIZE);
        printf("Received: %s\n", buffer);
    }

    // Close the FIFO
    close(fd);
    return 0;
}
/*
output:
FIFO fifooo already exists.
Waiting for data in FIFO for 10 seconds...
Received: Hello, FIFO!
*/