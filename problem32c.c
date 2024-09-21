/*
name: problem32c.c
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
#include <unistd.h>

int main() {
    key_t key = ftok("/tmp", 'R');
    int semid = semget(key, 2, 0666 | IPC_CREAT);
    struct sembuf p[2] = {{0, -1, SEM_UNDO}, {1, -1, SEM_UNDO}};
    struct sembuf v[2] = {{0, 1, SEM_UNDO}, {1, 1, SEM_UNDO}};

    semctl(semid, 0, SETVAL, 2);
    semctl(semid, 1, SETVAL, 2);

    semop(semid, p, 2);
    printf("Resource 1 and 2 acquired\n");
    semop(semid, v, 2);
    printf("Resource 1 and 2 released\n");

    return 0;
}

/*
OUTPUT:
Resource 1 and 2 acquired
Resource 1 and 2 released

*/
