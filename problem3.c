/*
NAME: problem3.c
AUTHOR: SHAIK MOHAMMAD IRFAN
roll number : MT2024138
description:Write a program to set (any one) system resource limit. 
Use setrlimit system call. 
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>

void print_max_as() {
    struct rlimit rl;

    // Get the current maximum resident set size limit
    if (getrlimit(RLIMIT_AS, &rl) == -1) {
        perror("Error getting maximum address space set size limit");
        exit(EXIT_FAILURE);
    }

    printf("Current maximum address space limit: ");
    if (rl.rlim_cur == RLIM_INFINITY)
        printf("Unlimited\n");
    else
        printf("%ld bytes\n", rl.rlim_cur);

    printf("Hard limit: ");
    if (rl.rlim_max == RLIM_INFINITY)
        printf("Unlimited\n");
    else
        printf("%ld bytes\n", rl.rlim_max);
}

void set_max_as(rlim_t limit) {
    struct rlimit rl;

    // Set the maximum resident set size limit
    rl.rlim_cur = limit;
    rl.rlim_max = limit*1000;
    if (setrlimit(RLIMIT_AS, &rl) == -1) {
        perror("Error setting maximum address space limit");
        exit(EXIT_FAILURE);
    }
}

int main() {
    // Print the current maximum resident set size limit
    print_max_as();

    // Set the maximum resident set size limit to 50 MB
    set_max_as(50 * 1024 * 1024);

    // Print the updated maximum resident set size limit
    print_max_as();

    return 0;
}
/*
OUTPUT:
Current maximum address space limit: Unlimited
Hard limit: Unlimited
Current maximum address space limit: 52428800 bytes
Hard limit: 52428800000 bytes

*/