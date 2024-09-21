/*
name: problem31b.c
author: SHAIK  MOHAMMAD IRFAN 
description:Write a program to create a semaphore and initialize value to the semaphore. 
a. create a counting semaphore
date : 20th September 2024
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <unistd.h>

union semun {
    int val;                // Value for SETVAL
    struct semid_ds *buf;    // Buffer for IPC_STAT, IPC_SET
    unsigned short *array;   // Array for GETALL, SETALL
};

int main() {
    key_t key;
    int semid;
    union semun sem_union;
    
    key = ftok("/home/irfan_shaik/ssy/hands_on2/semfile", 66);  
    if (key == -1) {
        perror("ftok");
        exit(EXIT_FAILURE);
    }
    semid = semget(key, 1, 0666 | IPC_CREAT);
    if (semid == -1) {
        perror("semget");
        exit(EXIT_FAILURE);
    }
    
    sem_union.val = 5;  
    if (semctl(semid, 0, SETVAL, sem_union) == -1) {
        perror("semctl");
        exit(EXIT_FAILURE);
    }
    
    printf("Counting semaphore created and initialized to 5.\n");

    // semctl(semid, 0, IPC_RMID);

    return 0;
}
/*
OUTPUT:
Counting semaphore created and initialized to 5
*/