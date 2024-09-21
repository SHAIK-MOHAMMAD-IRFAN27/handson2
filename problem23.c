/*
name: problem23.c
author: SHAIK  MOHAMMAD IRFAN 
description:Write a program to print the maximum number of files can be opened within a process and  
size of a pipe (circular buffer).
date : 19th September 2024
*/
#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

int main() {
    long max_files = sysconf(_SC_OPEN_MAX);
    
    if (max_files == -1) {
        perror("Error getting max number of open files");
        return 1;
    }

    printf("Maximum number of files a process can open: %ld\n", max_files);

    int pipe_fd[2];
    if (pipe(pipe_fd) == -1) {
        perror("Error creating pipe");
        return 1;
    }

    // Check the size of the pipe's buffer using fpathconf
    long pipe_size = fpathconf(pipe_fd[0], _PC_PIPE_BUF);
    
    if (pipe_size == -1) {
        perror("Error getting pipe buffer size");
        return 1;
    }

    printf("Size of the pipe's buffer (circular buffer): %ld bytes\n", pipe_size);

    // Close the pipe file descriptors
    close(pipe_fd[0]);
    close(pipe_fd[1]);

    return 0;
}
