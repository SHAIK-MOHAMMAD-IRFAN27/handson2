/*
name: problem13b.c
author: SHAIK  MOHAMMAD IRFAN 
description:  Write two programs: first program is waiting to catch SIGSTOP signal, the second program 
will send the signal (using kill system call). Find out whether the first program is able to catch 
the signal or not. 
date : 18th September 2024
*/
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

int main() {
    pid_t target_pid;

    printf("Enter the PID of the process to send SIGSTOP to: ");
    scanf("%d", &target_pid);
    if (kill(target_pid, SIGSTOP) == -1) {
        perror("Failed to send SIGSTOP");
        exit(1);
    }

    printf("Sent SIGSTOP to process %d.\n", target_pid);
    sleep(5);
    if (kill(target_pid, SIGCONT) == -1) {
        perror("Failed to send SIGCONT");
        exit(1);
    }

    printf("Sent SIGCONT to process %d.\n", target_pid);

    return 0;
}
/*
OUTPUT:
Enter the PID of the process to send SIGSTOP to: 644
Sent SIGSTOP to process 644.
Sent SIGCONT to process 644.
*/