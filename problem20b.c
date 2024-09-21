/*
name: problem20b.c
author: SHAIK  MOHAMMAD IRFAN 
description:Write two programs so that both can communicate by
 FIFO -Use one way communication
date : 18th September 2024
*/
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    const char *fifo_path = "myfifo";
    int fd;
    char buffer[100];
    fd = open(fifo_path, O_RDONLY);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    // Read the message from the FIFO
    ssize_t bytes_read = read(fd, buffer, sizeof(buffer) - 1);
    if (bytes_read == -1) {
        perror("read");
        close(fd);
        exit(EXIT_FAILURE);
    }

    // Null-terminate the buffer and print the message
    buffer[bytes_read] = '\0';
    printf("Message read from FIFO: %s\n", buffer);

    // Close the FIFO
    close(fd);
    return 0;
}
/*
output:
Message read from FIFO: Hello im Irfan!
*/