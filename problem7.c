/*
name: problem7.c
author: SHAIK  MOHAMMAD IRFAN 
description:  Write a simple program to print the created thread ids.
date : 17th September 2024
*/
#include <stdio.h>
#include <pthread.h>
void* threadFunction(void* arg) {
    pthread_t threadID = pthread_self();
    printf("Thread %d has ID: %lu\n", *(int*)arg, threadID);
    return NULL;
}

int main() {
    pthread_t threads[3]; 
    int threadArgs[3];   
    for (int i = 0; i < 3; i++) {
        threadArgs[i] = i + 1;  
        pthread_create(&threads[i], NULL, threadFunction, (void*)&threadArgs[i]);
    }
    for (int i = 0; i < 3; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("All threads have completed.\n");
    return 0;
}
/*
OUTPUT:-
Thread 1 has ID: 140318574474816
Thread 2 has ID: 140318566082112
Thread 3 has ID: 140318557689408
All threads have completed.
*/