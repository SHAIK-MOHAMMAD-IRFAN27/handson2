/*
name: problem15.c
author: SHAIK  MOHAMMAD IRFAN 
description:  Write a simple program to send some data from parent to the child process. 
date : 18th September 2024
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include<sys/wait.h>
int main() {
    int pipefd[2]; 
    pid_t pid;
    char buffer[128];  
    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid = fork();

    if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
       
        close(pipefd[1]);
        ssize_t bytesRead = read(pipefd[0], buffer, sizeof(buffer) - 1);

        if (bytesRead == -1) {
            perror("read");
            exit(EXIT_FAILURE);
        }
        buffer[bytesRead] = '\0';
        printf("Child process received message: %s\n", buffer);

        close(pipefd[0]);

        exit(EXIT_SUCCESS);
    } else {
        close(pipefd[0]);
        const char *message = "Hello from parent process!";
        write(pipefd[1], message, sizeof(message));
        close(pipefd[1]);
        wait(NULL);
    }

    return 0;
}

/*
OUTPUT:
Child process received message: Hello from parent process
*/