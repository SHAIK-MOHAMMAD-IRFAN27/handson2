/*
name: problem27b.c
author: SHAIK  MOHAMMAD IRFAN 
description:Write a program to receive messages from the message queue. 
 
b. with IPC_NOWAIT as a flag 
date : 20th September 2024
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdlib.h>

// Define message structure
struct msg_buffer {
    long msg_type;  // Message type
    char msg_text[100];  // Message content
};

int main() {
    key_t key;
    int msgid;

    // Generate unique key for receiver
    key = ftok("/home/irfan_shaik/ssy/hands_on2/tmp1", 65); // Use a different file and ID

    // Access the message queue
    msgid = msgget(key, 0666 | IPC_CREAT);
    if (msgid < 0) {
        perror("msgget");
        exit(1);
    }

    struct msg_buffer message;

    // Receive message of type 2 (sent by sender)
    if (msgrcv(msgid, &message, sizeof(message.msg_text), 2, IPC_NOWAIT) == -1) {
        perror("msgrcv");
        exit(1);
    }

    // Display the received message
    printf("Received message with type %ld: %s\n", message.msg_type, message.msg_text);

    // Optional: destroy the message queue after receiving
    // msgctl(msgid, IPC_RMID, NULL);

    return 0;
}
/*
OUTPUT:
if message is not sent then 
msgrcv: No message of desired type

if message is sent the 

Received message with type 2: irfansand
*/