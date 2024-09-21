/*
NAME: problem4.c
AUTHOR: SHAIK MOHAMMAD IRFAN
roll number : MT2024138
description:Write a program to measure how much time is taken to execute
 100 getppid ( ) system call. Use time stamp counter.
*/
#include <stdio.h>
#include <unistd.h>
unsigned long long rdtsc() {
    unsigned int lo, hi;
    asm volatile ("rdtsc" : "=a"(lo), "=d"(hi));
    return ((unsigned long long)hi << 32) | lo;
}

int main() {
    unsigned long long start, end;
    int i;
    start = rdtsc();
    for (i = 0; i < 100; i++) {
        getppid(); 
    }
    end = rdtsc();
    unsigned long long cycles = end - start;

    printf("Time taken for 100 getppid() calls: %llu CPU cycles\n", cycles);

    return 0;
}
/*
OUTPUT:
Time taken for 100 getppid() calls: 26027 CPU cycles
*/
