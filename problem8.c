/*
name: problem8.c
author: SHAIK  MOHAMMAD IRFAN 
description:  Write a separate program using signal system call to catch the following signals. 
   a. SIGSEGV 
   b. SIGINT 
   c. SIGFPE 
   d. SIGALRM (use alarm system call) 
   e. SIGALRM (use setitimer system call) 
   f. SIGVTALRM (use setitimer system call) 
   g. SIGPROF (use setitimer system call)  in c
date : 17th September 2024
*/
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/time.h>

// Signal handler function
void signalHandler(int signal) {
    switch (signal) {
        case SIGSEGV:
            printf("Caught SIGSEGV: Segmentation Fault\n");
            exit(1);
        case SIGINT:
            printf("Caught SIGINT: Interrupt from keyboard (Ctrl+C)\n");
            exit(0);
        case SIGFPE:
            printf("Caught SIGFPE: Arithmetic Exception (e.g., division by zero)\n");
            exit(1);
        case SIGALRM:
            printf("Caught SIGALRM: Alarm signal\n");
            break;
        case SIGVTALRM:
            printf("Caught SIGVTALRM: Virtual timer alarm signal\n");
            break;
        case SIGPROF:
            printf("Caught SIGPROF: Profiling timer alarm signal\n");
            break;
        default:
            printf("Caught unknown signal: %d\n", signal);
            break;
    }
}

void triggerSIGFPE() {
    int x = 1;
    int y = 0;
    int z = x / y;  // This will raise SIGFPE
    (void)z;        // Prevents unused variable warning
}
void triggerSIGSEGV() {
    int *ptr = NULL;
    *ptr = 42;  // This will raise SIGSEGV
}
void triggerAlarmUsingAlarm() {
    printf("Setting an alarm for 3 seconds using alarm()...\n");
    alarm(3);  // Set alarm to go off in 3 seconds
    pause();   // Wait for the signal
} 
void triggerTimersUsingSetitimer() {
    struct itimerval timer;
    printf("Setting an alarm for 3 seconds using setitimer() (SIGALRM)...\n");
    timer.it_value.tv_sec = 3;
    timer.it_value.tv_usec = 0;
    timer.it_interval.tv_sec = 0;
    timer.it_interval.tv_usec = 0;
    setitimer(ITIMER_REAL, &timer, NULL);
    pause();
    printf("Setting a virtual timer for 2 seconds using setitimer() (SIGVTALRM)...\n");
    timer.it_value.tv_sec = 2;
    timer.it_value.tv_usec = 0;
    setitimer(ITIMER_VIRTUAL, &timer, NULL);
    pause();
    printf("Setting a profiling timer for 2 seconds using setitimer() (SIGPROF)...\n");
    timer.it_value.tv_sec = 2;
    timer.it_value.tv_usec = 0;
    setitimer(ITIMER_PROF, &timer, NULL);
    pause();
}

int main() {
    signal(SIGSEGV, signalHandler);
    signal(SIGINT, signalHandler);
    signal(SIGFPE, signalHandler);
    signal(SIGALRM, signalHandler);
    signal(SIGVTALRM, signalHandler);
    signal(SIGPROF, signalHandler);

    // Uncomment the following lines one by one to test each signal.

     //Trigger SIGFPE (division by zero)
     triggerSIGFPE();
	 printf("HELLO");

     //Trigger SIGSEGV (invalid memory access)
     triggerSIGSEGV();

    //Trigger SIGALRM using alarm() system call
    //triggerAlarmUsingAlarm();

    // Trigger SIGALRM, SIGVTALRM, and SIGPROF using setitimer() system call
    //triggerTimersUsingSetitimer();

    return 0;
}
/*
OUTPUT:
Caught SIGFPE: Arithmetic Exception (e.g., division by zero)
*/