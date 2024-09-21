/*
name: problem19d.c
author: SHAIK  MOHAMMAD IRFAN 
description: mkfifo function
date : 18th September 2024
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    const char *fifo_path = "myfifowithmkfifo";

    if (mkfifo(fifo_path, 0666) == -1) {
        perror("mkfifo");
        exit(EXIT_FAILURE);
    }

    printf("FIFO file %s created successfully.\n", fifo_path);
    return 0;
}

/*
output:
FIFO file myfifowithmkfifo created successfully
*/