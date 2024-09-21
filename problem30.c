/*
name: problem30.c
author: SHAIK  MOHAMMAD IRFAN 
description:Write a program to create a shared memory. 
a. write some data to the shared memory 
b. attach with O_RDONLY and check whether you are able to overwrite. 
c. detach the shared memory 
d. remove the shared memory 
date : 20th September 2024
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
#include <unistd.h>

#define SHM_SIZE 1024  // Size of the shared memory segment

int main() {
    key_t key;
    int shmid;
    char *data;
    key = ftok("/home/irfan_shaik/ssy/hands_on2/shmfile", 65);
    if (key == -1) {
        perror("ftok");
        exit(EXIT_FAILURE);
    }
    shmid = shmget(key, SHM_SIZE, 0666 | IPC_CREAT);
    if (shmid == -1) {
        perror("shmget");
        exit(EXIT_FAILURE);
    }
    printf("Shared memory created with ID: %d\n", shmid);

    data = (char*) shmat(shmid, NULL, 0); 
    if (data == (char*) -1) {
        perror("shmat");
        exit(EXIT_FAILURE);
    }

    printf("Writing to shared memory...\n");
    strncpy(data, "Hello, Shared Memory!", SHM_SIZE);
    printf("Data written: %s\n", data);

    if (shmdt(data) == -1) {
        perror("shmdt");
        exit(EXIT_FAILURE);
    }
    printf("\nAttaching shared memory in read-only mode...\n");
    data = (char*) shmat(shmid, NULL, SHM_RDONLY);  
    if (data == (char*) -1) {
        perror("shmat (read-only)");
        exit(EXIT_FAILURE);
    }

    printf("Data read from shared memory: %s\n", data);
    printf("Attempting to write to read-only shared memory...\n");

    strcpy(data, "This should fail!"); 
    if (shmdt(data) == -1) {
        perror("shmdt");
        exit(EXIT_FAILURE);
    }

    printf("\nRemoving the shared memory...\n");
    if (shmctl(shmid, IPC_RMID, NULL) == -1) {
        perror("shmctl - IPC_RMID");
        exit(EXIT_FAILURE);
    }
    printf("Shared memory removed.\n");

    return 0;
}
/*
OUTPUT:
--->if we try to write to a READ_ONLY shared memory output is:
Shared memory created with ID: 0
Writing to shared memory...
Data written: Hello, Shared Memory!

Attaching shared memory in read-only mode...
Data read from shared memory: Hello, Shared Memory!
Attempting to write to read-only shared memory...
Segmentation fault


---> if we dont try to write into READ_ONLY a shared memory :
Shared memory created with ID: 0
Writing to shared memory...
Data written: Hello, Shared Memory!

Attaching shared memory in read-only mode...
Data read from shared memory: Hello, Shared Memory!
Attempting to write to read-only shared memory...

Removing the shared memory...
Shared memory removed.

*/