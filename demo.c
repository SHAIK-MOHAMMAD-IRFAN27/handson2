#include <stdio.h>
#include <signal.h>
#include <sys/time.h>
#include <unistd.h>

void virtual_timer_handler(int signum) {
    printf("ITIMER_VIRTUAL timer expired\n");
}

int main() {
    struct itimerval timer;
    signal(SIGVTALRM, virtual_timer_handler);

    // Set timer interval to 5 seconds
    timer.it_value.tv_sec = 5;
    timer.it_value.tv_usec = 0;
    timer.it_interval.tv_sec = 0;
    timer.it_interval.tv_usec = 0;
    if (setitimer(ITIMER_VIRTUAL, &timer, NULL) == -1) {
        perror("Error setting ITIMER_VIRTUAL");
        return 1;
    }
    printf("Starting virtual timer (5 seconds), entering busy loop\n");
    for (int i = 0; i < 1000000000; i++);  // Busy work in user mode
	sleep(10);
    printf("Busy work done, exiting\n");
    return 0;
}
