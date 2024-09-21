/*
name: problem13a.c
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

void signalHandler(int signal) {
    printf("Caught signal: %d\n", signal);
}

int main() {
    struct sigaction sa;
    sa.sa_handler = signalHandler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(SIGINT, &sa, NULL);
    sigaction(SIGTERM, &sa, NULL); 
    sigaction(SIGUSR1, &sa, NULL); 
    sigaction(SIGUSR2, &sa, NULL); 

    printf("Process PID: %d\n", getpid());
    printf("Waiting for signals...\n");
    while (1) {
        pause(); 
    }

    return 0;
}
/*
OUTPUT:
Process PID: 644
Waiting for signals...

[2]+  Stopped
*/