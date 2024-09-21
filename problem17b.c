/*
name: problem17b.c
author: SHAIK  MOHAMMAD IRFAN 
description:  Write a program to execute ls -l | wc. 
a. use dup2 
date : 18th September 2024
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include<sys/wait.h>
int main() {
    int pipefds[2];
    pid_t pid1, pid2;

    if (pipe(pipefds) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    // First child process for `ls -l`
    if ((pid1 = fork()) == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid1 == 0) {
        // Child process: execute `ls -l`
        close(pipefds[0]);           // Close unused read end
        dup2(pipefds[1], STDOUT_FILENO); // Redirect stdout to pipe write end
        close(pipefds[1]);           // Close original write end

        execlp("ls", "ls", "-l", (char *)NULL);
        perror("execlp");
        exit(EXIT_FAILURE);
    }

    // Second child process for `wc`
    if ((pid2 = fork()) == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid2 == 0) {
        // Child process: execute `wc`
        close(pipefds[1]);           // Close unused write end
        dup2(pipefds[0], STDIN_FILENO); // Redirect stdin to pipe read end
        close(pipefds[0]);           // Close original read end

        execlp("wc", "wc", (char *)NULL);
        perror("execlp");
        exit(EXIT_FAILURE);
    }

    // Parent process: close both ends and wait for children
    close(pipefds[0]);
    close(pipefds[1]);

    wait(NULL);
    wait(NULL);

    return 0;
}
/*
OUTPUT:
    24     209    1550
	*/