/*
name: problem9.c
author: SHAIK  MOHAMMAD IRFAN 
description: Write a program to ignore a SIGINT signal then reset the default action of the SIGINT 
signal -  Use signal system call.
date : 17th September 2024
*/
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
void signalHandler(int signal) {
    printf("Caught SIGINT, but it's currently ignored.\n");
}

int main() {
    printf("Ignoring SIGINT (Ctrl+C)... Press Ctrl+C, nothing will happen.\n");
    signal(SIGINT, signalHandler);
    sleep(5);
    printf("Now resetting SIGINT to default behavior... Press Ctrl+C again.\n");
    signal(SIGINT, SIG_DFL);
    sleep(10);

    printf("Program completed.\n");
    return 0;
}
