
/*
NAME: problem2.c
AUTHOR: SHAIK MOHAMMAD IRFAN
roll number : MT2024138
description:Write a program to print the system resource limits.
 Use getrlimit system call  
*/
#include <stdio.h>
#include <sys/resource.h>
#include <stdlib.h>

void print_limit(int resource, const char *resource_name) {
    struct rlimit limit;
    if (getrlimit(resource, &limit) == -1) {
        perror("Error getting resource limit");
        exit(EXIT_FAILURE);
    }
    printf("%s: \n", resource_name);
    if (limit.rlim_cur == RLIM_INFINITY)
        printf("  Soft limit: Unlimited\n");
    else
        printf("  Soft limit: %ld\n", limit.rlim_cur);

    if (limit.rlim_max == RLIM_INFINITY)
        printf("  Hard limit: Unlimited\n");
    else
        printf("  Hard limit: %ld\n", limit.rlim_max);

    printf("\n");
}
int main() {
    print_limit(RLIMIT_CPU, "CPU time limit (seconds)");
    print_limit(RLIMIT_FSIZE, "Maximum file size (bytes)");
    print_limit(RLIMIT_DATA, "Maximum data segment size (bytes)");
    print_limit(RLIMIT_STACK, "Maximum stack size (bytes)");
    print_limit(RLIMIT_CORE, "Core file size (bytes)");
    print_limit(RLIMIT_RSS, "Maximum resident set size (bytes)");
    print_limit(RLIMIT_NOFILE, "Maximum number of open files");
    print_limit(RLIMIT_AS, "Maximum address space (bytes)");

    return 0;
}
/*
OUTPUT:
CPU time limit (seconds): 
  Soft limit: Unlimited
  Hard limit: Unlimited

Maximum file size (bytes): 
  Soft limit: 1048576
  Hard limit: Unlimited

Maximum data segment size (bytes): 
  Soft limit: Unlimited
  Hard limit: Unlimited

Maximum stack size (bytes): 
  Soft limit: 8388608
  Hard limit: Unlimited

Core file size (bytes): 
  Soft limit: 0
  Hard limit: Unlimited

Maximum resident set size (bytes): 
  Soft limit: Unlimited
  Hard limit: Unlimited

Maximum number of open files: 
  Soft limit: 1024
  Hard limit: 4096

Maximum address space (bytes): 
  Soft limit: Unlimited
  Hard limit: Unlimited
*/
