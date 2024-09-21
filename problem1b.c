/*
NAME: problem1b.c
AUTHOR: SHAIK MOHAMMAD IRFAN
roll number : MT2024138
description:  Write a separate program (for each time domain) to set a interval timer in 10sec and  10micro second 
				b. ITIMER_VIRTUAL
*/
#include <stdio.h>
#include <signal.h>
#include <sys/time.h>
#include <unistd.h>

void timer_handler(int signum) {
    printf("ITIMER_VIRTUAL timer expired\n");
}

int main() {
    struct itimerval timer;
    signal(SIGVTALRM, timer_handler);
    timer.it_value.tv_sec = 10;
    timer.it_value.tv_usec = 10;
    timer.it_interval.tv_sec = 10;
    timer.it_interval.tv_usec = 10;
    if (setitimer(ITIMER_VIRTUAL, &timer, NULL) == -1) {
        perror("Error setting timer");
        return 1;
    }
    while (1) {
        pause();
    }

    return 0;
}
/*
OUTPUT:
ITIMER_VIRTUAL timer expired\n
ITIMER_VIRTUAL timer expired\n
.....
*/