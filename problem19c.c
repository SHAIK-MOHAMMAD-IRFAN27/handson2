/*
name: problem19c.c
author: SHAIK  MOHAMMAD IRFAN 
description:mknod system call
date : 18th September 2024
*/
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    const char *fifo_path = "myfifowithmknod";

    if (mknod(fifo_path, S_IFIFO | 0666, 0) == -1) {
        perror("mknod");
        exit(EXIT_FAILURE);
    }

    printf("FIFO file %s created successfully.\n", fifo_path);
    return 0;
}
/*
output:
FIFO file myfifowithmknod created successfully
*/