/*
name: problem29.c
author: SHAIK  MOHAMMAD IRFAN 
description:Write a program to remove the message queue
date : 20th September 2024
*/
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <message_queue_id>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    int msgid = atoi(argv[1]);
    if (msgctl(msgid, IPC_RMID, NULL) == -1) {
        perror("msgctl - IPC_RMID");
        exit(EXIT_FAILURE);
    }

    printf("Message queue with ID %d has been removed.\n", msgid);

    return 0;
}
/*OUTPUT:
./porgram 0  --> remove the queue with id:0

Message queue with ID 0 has been removed.
*/