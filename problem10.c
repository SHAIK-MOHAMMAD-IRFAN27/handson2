/*
name: problem10.c
author: SHAIK  MOHAMMAD IRFAN 
description: Write a separate program using sigaction system call to catch the following signals. 
   a. SIGSEGV 
   b. SIGINT 
c. SIGFPE 
date : 20th September 2024
*/
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

// Signal handler functions
void handle_sigsegv(int sig) {
    printf("Caught SIGSEGV (Segmentation Fault)\n");
    exit(EXIT_FAILURE);
}


int main() {
    struct sigaction sa_seg, sa_int, sa_fpe;

    // Set up handler for SIGSEGV
    sa_seg.sa_handler = handle_sigsegv;
    sigemptyset(&sa_seg.sa_mask);
    sa_seg.sa_flags = 0;
    sigaction(SIGSEGV, &sa_seg, NULL);
    printf("About to cause a segmentation fault...\n");
    int *ptr = NULL; 
    *ptr = 42;      
    printf("This line will not be printed.\n");
    return 0;
}
/*
output:
About to cause a segmentation fault...
Caught SIGSEGV (Segmentation Fault)
*/