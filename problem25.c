/*
name: problem25.c
author: SHAIK  MOHAMMAD IRFAN 
description:. Write a program to print a message queue's  (use msqid_ds and ipc_perm structures) 
a. access permission 
b. uid, gid 
c. time of last message sent and received    
d. time of last change in the message queue 
d. size of the queue 
f. number of messages in the queue  
g. maximum number of bytes allowed  
h. pid of the msgsnd and msgrcv 
date : 20th September 2024
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

void printMessageQueueInfo(int msgid) {
    struct msqid_ds msg_queue_info;

    if (msgctl(msgid, IPC_STAT, &msg_queue_info) == -1) {
        perror("msgctl");
        exit(EXIT_FAILURE);
    }
    printf("Access Permission: %o\n", msg_queue_info.msg_perm.mode);
    
    printf("User ID (UID): %u\n", msg_queue_info.msg_perm.uid);
    printf("Group ID (GID): %u\n", msg_queue_info.msg_perm.gid);
    
    printf("Time of last message sent: %ld\n", msg_queue_info.msg_stime);
    printf("Time of last message received: %ld\n", msg_queue_info.msg_rtime);
    printf("Time of last change: %ld\n", msg_queue_info.msg_ctime);
    
    printf("Size of the queue (bytes): %lu\n", msg_queue_info.__msg_cbytes);
    printf("Number of messages in the queue: %lu\n", msg_queue_info.msg_qnum);
    
    printf("Maximum number of bytes allowed: %lu\n", msg_queue_info.msg_qbytes);
    
    printf("PID of last msgsnd: %u\n", msg_queue_info.msg_lspid);
    printf("PID of last msgrcv: %u\n", msg_queue_info.msg_lrpid);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <message queue id>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int msgid = atoi(argv[1]);
    
    printMessageQueueInfo(msgid);
    
    return 0;
}
/*
OUTPUT:
Access Permission: 666
User ID (UID): 1000
Group ID (GID): 1000
Time of last message sent: 1726814280 //unix time stamp to convert to human readable use date -d @number
Time of last message received: 1726814147
Time of last change: 1726813673
Size of the queue (bytes): 100
Number of messages in the queue: 1
Maximum number of bytes allowed: 16384
PID of last msgsnd: 638
PID of last msgrcv: 623
*/