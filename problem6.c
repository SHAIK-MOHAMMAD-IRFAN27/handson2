/*
name: problem6.c
author: SHAIK  MOHAMMAD IRFAN 
description:  Write a simple program to create three threads.
date : 17th September 2024
*/
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
void* threadFunction(void* arg) {
    int threadNum = *(int*)arg;  
    printf("Thread %d is running\n", threadNum);
    sleep(1);  
    printf("Thread %d is done\n", threadNum);
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
Thread 1 is running
Thread 2 is running
Thread 3 is running
Thread 1 is done
Thread 2 is done
Thread 3 is done
All threads have completed.
*/