/*
NAME: problem1c.c
AUTHOR: SHAIK MOHAMMAD IRFAN
roll number : MT2024138
description:  Write a separate program (for each time domain) to set a interval timer in 10sec and  10micro second 
				c. ITIMER_PROF
*/
#include <stdio.h>
#include <signal.h>
#include <sys/time.h>
#include <unistd.h>

void timer_handler(int signum) {
    printf("ITIMER_PROF timer expired\n");
}

int main() {
    struct itimerval timer;

    // Register signal handler for SIGPROF
    signal(SIGPROF, timer_handler);

    // Set timer interval to 10 seconds and 10 microseconds
    timer.it_value.tv_sec = 10;
    timer.it_value.tv_usec = 10;
    timer.it_interval.tv_sec = 10;
    timer.it_interval.tv_usec = 10;

    // Set the timer for ITIMER_PROF
    if (setitimer(ITIMER_PROF, &timer, NULL) == -1) {
        perror("Error setting timer");
        return 1;
    }

    // Wait for signals to arrive
    while (1) {
        pause();
    }

    return 0;
}

/*
OUTPUT:
ITIMER_PROF timer expired
ITIMER_PROF timer expired
ITIMER_PROF timer expired
...

*/