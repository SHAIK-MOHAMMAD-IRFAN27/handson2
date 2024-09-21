/*
name: problem28.c
author: SHAIK  MOHAMMAD IRFAN 
description:Write a program to change the exiting
 message queue permission. (use msqid_ds structure)
date : 20th September 2024
*/
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
/*
int main() {
    key_t key;
    int msgid;
    struct msqid_ds msg_queue_info;
    key = ftok("progfile", 65);
    if (key == -1) {
        perror("ftok");
        exit(EXIT_FAILURE);
    }
    msgid = msgget(key, 0666);
    if (msgid == -1) {
        perror("msgget");
        exit(EXIT_FAILURE);
    }
    if (msgctl(msgid, IPC_STAT, &msg_queue_info) == -1) {
        perror("msgctl");
        exit(EXIT_FAILURE);
    }
    printf("Current permissions: %o\n", msg_queue_info.msg_perm.mode);

    msg_queue_info.msg_perm.mode = 0644; 

    if (msgctl(msgid, IPC_SET, &msg_queue_info) == -1) {
        perror("msgctl");
        exit(EXIT_FAILURE);
    }
    printf("Updated permissions: %o\n", msg_queue_info.msg_perm.mode);

    return 0;
}
*/
int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <message queue id>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int msgid = atoi(argv[1]);
	struct msqid_ds msg_queue_info;

    if (msgctl(msgid, IPC_STAT, &msg_queue_info) == -1) {
        perror("msgctl");
        exit(EXIT_FAILURE);
    }
    printf("Current permissions: %o\n", msg_queue_info.msg_perm.mode);
	msg_queue_info.msg_perm.mode = 0644; 

    if (msgctl(msgid, IPC_SET, &msg_queue_info) == -1) {
        perror("msgctl");
        exit(EXIT_FAILURE);
    }
    printf("Updated permissions: %o\n", msg_queue_info.msg_perm.mode);
    
    return 0;
}
/*
OUTPUT:
for the code in program26

Current permissions: 666
Updated permissions: 644
*/