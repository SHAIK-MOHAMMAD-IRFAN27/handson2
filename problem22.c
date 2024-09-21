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

#define FIFO_NAME "fifooo"

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

    // Open the FIFO for writing
    int fd = open(FIFO_NAME, O_WRONLY);
    if (fd == -1) {
        perror("Open FIFO for writing failed");
        exit(EXIT_FAILURE);
    }

    // Write data to the FIFO
    const char *message = "Hello, FIFO!";
    write(fd, message, strlen(message) + 1); // +1 for null terminator

    printf("Message written to FIFO: %s\n", message);

    // Close the FIFO
    close(fd);
    return 0;
}


/*
output:
FIFO fifooo created successfully.
Message written to FIFO: Hello, FIFO!
*/