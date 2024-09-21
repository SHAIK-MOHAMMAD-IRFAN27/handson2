/*
name: problem10.c
author: SHAIK  MOHAMMAD IRFAN 
description: Write a separate program using sigaction system call to catch the following signals. 
   
   b. SIGINT 
 date : 20th September 2024
*/
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
void handle_sigint(int sig) {
    printf("Caught SIGINT (Interrupt signal)\n");
    exit(EXIT_SUCCESS);
}
int main() {
    struct sigaction sa_int;

    // Set up handler for SIGINT
    sa_int.sa_handler = handle_sigint;
    sigemptyset(&sa_int.sa_mask);
    sa_int.sa_flags = 0;
    sigaction(SIGINT, &sa_int, NULL);
    // Infinite loop to keep the program running
    printf("Press Ctrl+C to trigger SIGINT.\n");
    //printf("To trigger SIGFPE, we will attempt division by zero in 5 seconds...\n");
    // Infinite loop to keep the program alive for SIGINT
    while (1) {
        pause(); // Wait for signals
    }

    return 0;
}
/*
output:
Press Ctrl+C to trigger SIGINT.
^CCaught SIGINT (Interrupt signal)
*/