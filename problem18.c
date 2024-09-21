/*
name: problem18.c
author: SHAIK  MOHAMMAD IRFAN 
description: Write a program to find out total number of directories on the pwd. 
execute ls -l | grep ^d | wc ? Use only dup2. 
date : 18th September 2024
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int pipe1[2], pipe2[2];
    pid_t pid1, pid2, pid3;

    if (pipe(pipe1) == -1) {
        perror("pipe1");
        exit(EXIT_FAILURE);
    }

    if (pipe(pipe2) == -1) {
        perror("pipe2");
        exit(EXIT_FAILURE);
    }

    if ((pid1 = fork()) == -1) {
        perror("fork1");
        exit(EXIT_FAILURE);
    }

    if (pid1 == 0) {
        close(pipe1[0]);
        dup2(pipe1[1], STDOUT_FILENO);
        close(pipe1[1]);

        execlp("ls", "ls", "-l", (char *)NULL);
        perror("execlp ls");
        exit(EXIT_FAILURE);
    }

    if ((pid2 = fork()) == -1) {
        perror("fork2");
        exit(EXIT_FAILURE);
    }

    if (pid2 == 0) {
        close(pipe1[1]);
        dup2(pipe1[0], STDIN_FILENO);
        close(pipe1[0]);

        close(pipe2[0]);
        dup2(pipe2[1], STDOUT_FILENO);
        close(pipe2[1]);

        execlp("grep", "grep", "^d", (char *)NULL);
        perror("execlp grep");
        exit(EXIT_FAILURE);
    }

    if ((pid3 = fork()) == -1) {
        perror("fork3");
        exit(EXIT_FAILURE);
    }

    if (pid3 == 0) {
        close(pipe2[1]);
        dup2(pipe2[0], STDIN_FILENO);
        close(pipe2[0]);

        execlp("wc", "wc", (char *)NULL);
        perror("execlp wc");
        exit(EXIT_FAILURE);
    }

    close(pipe1[0]);
    close(pipe1[1]);
    close(pipe2[0]);
    close(pipe2[1]);

    wait(NULL);
    wait(NULL);
    wait(NULL);

    return 0;
}
/*
OUTPUT:
 3      27     177
 3 IS NUMBER OF DIRECTORIES
 */