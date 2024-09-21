/*
name: problem10.c
author: SHAIK  MOHAMMAD IRFAN 
description: Write a separate program using sigaction system call to catch the following signals. 
    
c. SIGFPE 
date : 20th September 2024
*/


#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void handle_sigfpe(int sig) {
    printf("Caught SIGFPE (Floating-point Exception)\n");
    exit(EXIT_FAILURE);
}

int main() {
    struct sigaction sa;
    sa.sa_handler = handle_sigfpe;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    if (sigaction(SIGFPE, &sa, NULL) == -1) {
        perror("sigaction");
        exit(EXIT_FAILURE);
    }

    // Induce a floating-point exception by dividing by zero
    printf("About to cause a floating-point exception...\n");
    int x = 1 / 0; // This will cause SIGFPE
	(void)x;
    // This line will never be reached
    printf("This line will not be printed.\n");
    return 0;
}
/*
output:
About to cause a floating-point exception...
Caught SIGFPE (Floating-point Exception)
*/