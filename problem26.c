/*
name: problem26.c
author: SHAIK  MOHAMMAD IRFAN 
description:Write a program to send messages to the message queue. Check $ipcs -q 
date : 20th September 2024
*/
// msg_send.c
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <stdlib.h>

// Define message structure
struct msg_buffer {
    long msg_type;  // Message type
    char msg_text[100];  // Message content
};

int main() {
    key_t key;
    int msgid;
	
    // Generate unique key for sender
    key = ftok("/home/irfan_shaik/ssy/hands_on2/tmp1", 65);
    
    // Create message queue and return id
    msgid = msgget(key, 0666 | IPC_CREAT);
    if (msgid < 0) {
        perror("msgget");
        exit(1);
    }
    printf("msg queue id %d",msgid);
    struct msg_buffer message;
    message.msg_type = 2; // Different message type for sender

    printf("Enter message: ");
    fgets(message.msg_text, sizeof(message.msg_text), stdin);
    
    // Send message
    if (msgsnd(msgid, &message, sizeof(message.msg_text), 0) == -1) {
        perror("msgsnd");
        exit(1);
    }

    //printf("Message sent with type %ld: %s\n", message.msg_type, message.msg_text);
	printf("Message sent with type %ld from PID %d: %s\n", message.msg_type, message.sender_pid, message.msg_text);

    return 0;
}
/*OUTPUT:
Enter message: shaikirfanpathan
Message sent with type 2: shaikirfan
*/