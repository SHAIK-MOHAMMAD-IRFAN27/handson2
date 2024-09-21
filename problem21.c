/*
name: problem21.c
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

    // Open FIFO1 for writing
    fd1 = open(fifo1, O_WRONLY);
    if (fd1 == -1) {
        perror("open fifo1 for writing");
        exit(EXIT_FAILURE);
    }

    // Open FIFO2 for reading
    fd2 = open(fifo2, O_RDONLY);
    if (fd2 == -1) {
        perror("open fifo2 for reading");
        close(fd1);
        exit(EXIT_FAILURE);
    }

    // Write a message to FIFO1
    const char *message_to_b = "Hello from Program A!";
    if (write(fd1, message_to_b, sizeof(message_to_b)) == -1) {
        perror("write to fifo1");
        close(fd1);
        close(fd2);
        exit(EXIT_FAILURE);
    }
    printf("Program A sent: %s\n", message_to_b);

    // Read a message from FIFO2
    ssize_t bytes_read = read(fd2, buffer, sizeof(buffer) - 1);
    if (bytes_read == -1) {
        perror("read from fifo2");
        close(fd1);
        close(fd2);
        exit(EXIT_FAILURE);
    }

    buffer[bytes_read] = '\0';
    printf("Program A received: %s\n", buffer);

    // Close FIFOs
    close(fd1);
    close(fd2);

    return 0;
}
/*
output:
Program A sent: Hello from Program A!
Program A received: Hello from Program B!

*/