/*
name: problem32a.c
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
    key_t key = ftok("/tmp", 'T');
    int semid = semget(key, 1, 0666 | IPC_CREAT);
    struct sembuf p = {0, -1, SEM_UNDO};
    struct sembuf v = {0, 1, SEM_UNDO};

    semctl(semid, 0, SETVAL, 1);
    int ticket_number = 0;

    for (int i = 0; i < 5; i++) {
        semop(semid, &p, 1);
        ticket_number++;
        printf("Ticket Number: %d\n", ticket_number);
        semop(semid, &v, 1);
        sleep(1);
    }

    return 0;
}

/*
output:
Ticket Number: 1
Ticket Number: 2
Ticket Number: 3
Ticket Number: 4
Ticket Number: 5

*/
