/*
name: problem11.c
author: SHAIK  MOHAMMAD IRFAN 
description: Write a program to ignore a SIGINT signal then reset the default action of the SIGINT signal  
use sigaction system call.
date : 17th September 2024
*/
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
void signalHandler(int signal) {
    printf("Caught SIGINT, but it's currently ignored.\n");
}

int main() {
    struct sigaction sa;
    sa.sa_handler = signalHandler;  
    sigemptyset(&sa.sa_mask);     
    sa.sa_flags = 0;           
    sigaction(SIGINT, &sa, NULL);
    
    printf("Ignoring SIGINT (Ctrl+C)... Press Ctrl+C, nothing will happen.\n");
    
    sleep(5);
    sa.sa_handler = SIG_DFL;
    sigaction(SIGINT, &sa, NULL);

    printf("Now resetting SIGINT to default behavior... Press Ctrl+C again.\n");

    sleep(10);

    printf("Program completed.\n");
    return 0;
}
/*
OUTPUT:
Ignoring SIGINT (Ctrl+C)... Press Ctrl+C, nothing will happen.
^CCaught SIGINT, but it's currently ignored.
Now resetting SIGINT to default behavior... Press Ctrl+C again.
^C

*/