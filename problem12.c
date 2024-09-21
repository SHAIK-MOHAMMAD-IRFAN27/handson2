/*
name: problem12.c
author: SHAIK  MOHAMMAD IRFAN 
description:  Write a program to create an orphan process. Use kill system call to send SIGKILL signal to 
the parent process from the child process.
date : 17th September 2024
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>

int main() {
    pid_t pid;
    pid = fork();

    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    } else if (pid == 0) {
        printf("Child process (PID: %d) created.\n", getpid());
        printf("Child sending SIGKILL to parent (PID: %d).\n", getppid());

        kill(getppid(), SIGKILL);

        sleep(2);

        printf("Child process (PID: %d) is now orphaned and adopted by init/systemd (PID: %d).\n", getpid(), getppid());
        exit(0);
    } else {
        printf("Parent process (PID: %d) waiting...\n", getpid());
        sleep(10);

        printf("Parent process completed.\n");
    }

    return 0;
}
/*
OUTPUT:
Parent process (PID: 451) waiting...
Child process (PID: 452) created.
Child sending SIGKILL to parent (PID: 451).
Killed
Child process (PID: 452) is now orphaned and adopted by init/systemd (PID: 14).
*/