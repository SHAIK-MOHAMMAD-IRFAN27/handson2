/*
name: problem20.c
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
    fd = open(fifo_path, O_WRONLY);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }
    const char *message = "Hello im Irfan!";
    if (write(fd, message, sizeof(message)) == -1) {
        perror("write");
        close(fd);
        exit(EXIT_FAILURE);
    }
    printf("Message written to FIFO: %s\n", message);
    close(fd);
    return 0;
}
/*
output:
Message written to FIFO: Hello im Irfan!
*/