/*
name: problem5.c
author: SHAIK  MOHAMMAD IRFAN 
description:
 Write a program to print the system limitation of  
       a. maximum length of the arguments to the exec family of functions.  
       b. maximum number of simultaneous process per user id.  
       c. number of clock ticks (jiffy) per second.  
       d. maximum number of open files 
       e. size of a page 
       f. total number of pages in the physical memory 
       g. number of currently available pages in the physical memory.
date : 20th September 2024
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <sys/resource.h>
#include <sys/sysinfo.h>

int main() {
    // a. Maximum length of the arguments to the exec family of functions
    long max_arg_length = sysconf(_SC_ARG_MAX);
    printf("Maximum length of arguments to exec functions: %ld bytes\n", max_arg_length);

    // b. Maximum number of simultaneous processes per user id
    long max_processes = sysconf(_SC_CHILD_MAX);
    printf("Maximum number of simultaneous processes per user ID: %ld\n", max_processes);

    // c. Number of clock ticks (jiffies) per second
    long clock_ticks = sysconf(_SC_CLK_TCK);
    printf("Number of clock ticks (jiffies) per second: %ld\n", clock_ticks);

    // d. Maximum number of open files
    long max_open_files = sysconf(_SC_OPEN_MAX);
    printf("Maximum number of open files: %ld\n", max_open_files);

    // e. Size of a page
    long page_size = sysconf(_SC_PAGESIZE);
    printf("Size of a page: %ld bytes\n", page_size);

    // f. Total number of pages in the physical memory
    struct sysinfo info;
    if (sysinfo(&info) == 0) {
        long total_pages = info.totalram / page_size;
        printf("Total number of pages in the physical memory: %ld\n", total_pages);
    } else {
        perror("sysinfo");
        return EXIT_FAILURE;
    }

    // g. Number of currently available pages in the physical memory
    long available_pages = info.freeram / page_size;
    printf("Number of currently available pages in the physical memory: %ld\n", available_pages);

    return 0;
}
/*
output:
Maximum length of arguments to exec functions: 2097152 bytes
Maximum number of simultaneous processes per user ID: 14993
Number of clock ticks (jiffies) per second: 100
Maximum number of open files: 1024
Size of a page: 4096 bytes
Total number of pages in the physical memory: 960639
Number of currently available pages in the physical memory: 911330
*/