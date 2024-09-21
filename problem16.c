/*
name: problem16.c
author: SHAIK  MOHAMMAD IRFAN 
description:  Write a program to send and receive data from parent to child vice versa. Use two way 
communication. 
date : 18th September 2024
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main() {
    int parentToChild[2];  
    int childToParent[2];  
    pid_t pid;
    char parentMsg[] = "Message from Parent to Child";
    char childMsg[] = "Message from Child to Parent";
    char readBuffer[128];
    if (pipe(parentToChild) == -1 || pipe(childToParent) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }
    pid = fork();

    if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        close(parentToChild[1]);
        close(childToParent[0]);  
        read(parentToChild[0], readBuffer, sizeof(readBuffer));
        printf("Child received: %s\n", readBuffer);
        write(childToParent[1], childMsg, strlen(childMsg) + 1);
        close(parentToChild[0]);
        close(childToParent[1]);

        exit(EXIT_SUCCESS);
    } else {
        close(parentToChild[0]); 
        close(childToParent[1]);  
        write(parentToChild[1], parentMsg, strlen(parentMsg) + 1);

        read(childToParent[0], readBuffer, sizeof(readBuffer));
        printf("Parent received: %s\n", readBuffer);
        close(parentToChild[1]);
        close(childToParent[0]);
        wait(NULL);
    }

    return 0;
}
/*
OUTPUT:
Child received: Message from Parent to Child
Parent received: Message from Child to Parent
*/