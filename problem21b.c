/*
name: problem21b.c
author: SHAIK  MOHAMMAD IRFAN 
description:Write two programs so that both can communicate by
 FIFO -Use two way communication
date : 18th September 2024
*/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    const char *fifo1 = "fifo1";
    const char *fifo2 = "fifo2";
    int fd1, fd2;
    char buffer[100];

    // Open FIFO2 for writing
    fd2 = open(fifo2, O_WRONLY);
    if (fd2 == -1) {
        perror("open fifo2 for writing");
        exit(EXIT_FAILURE);
    }

    // Open FIFO1 for reading
    fd1 = open(fifo1, O_RDONLY);
    if (fd1 == -1) {
        perror("open fifo1 for reading");
        close(fd2);
        exit(EXIT_FAILURE);
    }

    // Read a message from FIFO1
    ssize_t bytes_read = read(fd1, buffer, sizeof(buffer) - 1);
    if (bytes_read == -1) {
        perror("read from fifo1");
        close(fd1);
        close(fd2);
        exit(EXIT_FAILURE);
    }

    buffer[bytes_read] = '\0';
    printf("Program B received: %s\n", buffer);

    // Write a message to FIFO2
    const char *message_to_a = "Hello from Program B!";
    if (write(fd2, message_to_a, sizeof(message_to_a)) == -1) {
        perror("write to fifo2");
        close(fd1);
        close(fd2);
        exit(EXIT_FAILURE);
    }
    printf("Program B sent: %s\n", message_to_a);

    // Close FIFOs
    close(fd1);
    close(fd2);

    return 0;
}
/*
output:
Program B received: Hello from Program A!
Program B sent: Hello from Program B!


*/