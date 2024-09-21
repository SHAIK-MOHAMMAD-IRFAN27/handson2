/*
name: problem32d.c
author: SHAIK  MOHAMMAD IRFAN 
description:Write a program to implement semaphore to protect any critical section. 
a. rewrite the ticket number creation program using semaphore 
b. protect shared memory from concurrent write access 
c. protect multiple pseudo resources ( may be two) using counting semaphore 
d. remove the created semaphore   
date : 21st September 2024
*/

#include <stdio.h>
#include <sys/ipc.h>
#include <sys/sem.h>

int main() {
    key_t key = ftok("/tmp", 'R');
    int semid = semget(key, 2, 0666 | IPC_CREAT);

    semctl(semid, 0, IPC_RMID, 0);
    printf("Semaphore removed.\n");

    return 0;
}

/*
OUTPUT:
Semaphore removed.

*/
