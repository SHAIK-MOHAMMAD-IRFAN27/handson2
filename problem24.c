/*
name: problem24.c
author: SHAIK  MOHAMMAD IRFAN 
description:Write a program to create a message queue and print the key and message queue id.
date : 20th September 2024
*/
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdlib.h>

int main() {
    const char *path = "/home/irfan_shaik/ssy/hands_on2/tmp";
    int proj_id = 'A';
    key_t key = ftok(path, proj_id);
    if (key == -1) {
        perror("ftok error");
        exit(1);
    }
    int msgid = msgget(key, 0666 | IPC_CREAT);  
    if (msgid == -1) {
        perror("msgget error");
        exit(1);
    }
    printf("Message Queue Key: %d\n", key);
    printf("Message Queue ID: %d\n", msgid);

    return 0;
}
/*
OUTPUT:
Message Queue Key: 1091619785
Message Queue ID: 0
*/