/*
NAME: problem1a.c
AUTHOR: SHAIK MOHAMMAD IRFAN
roll number : MT2024138
description:  Write a separate program (for each time domain) to set a interval timer in 10sec and  10micro second 
				a. ITIMER_REAL
*/
#include <stdio.h>
#include <signal.h>
#include <sys/time.h>
#include <unistd.h>

void timer_handler(int signum) {
    printf("ITIMER_REAL timer expired\n");
}

int main() {
    struct itimerval timer;
    signal(SIGALRM, timer_handler);
    timer.it_value.tv_sec = 10;
    timer.it_value.tv_usec = 10;
    timer.it_interval.tv_sec = 10;
    timer.it_interval.tv_usec = 10;
    if (setitimer(ITIMER_REAL, &timer, NULL) == -1) {
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
 ITIMER_REAL timer expired
 ITIMER_REAL timer expired
 ITIMER_REAL timer expired
 .......
 until i manually stop the program
 */