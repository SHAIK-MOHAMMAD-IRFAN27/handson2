/*
name: problem17c.c
author: SHAIK  MOHAMMAD IRFAN 
description:  Write a program to execute ls -l | wc. 
a. use fcntl 
date : 18th September 2024
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include<sys/wait.h>

int main() {
    int pipefds[2];
    pid_t pid1, pid2;

    if (pipe(pipefds) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    // First child process for `ls -l`
    if ((pid1 = fork()) == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid1 == 0) {
        // Child process: execute `ls -l`
        close(pipefds[0]); // Close unused read end
        fcntl(pipefds[1], F_DUPFD, STDOUT_FILENO); // Duplicate write end to stdout
        close(pipefds[1]); // Close original write end

        execlp("ls", "ls", "-l", (char *)NULL);
        perror("execlp");
        exit(EXIT_FAILURE);
    }

    // Second child process for `wc`
    if ((pid2 = fork()) == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid2 == 0) {
        // Child process: execute `wc`
        close(pipefds[1]); // Close unused write end
        fcntl(pipefds[0], F_DUPFD, STDIN_FILENO); // Duplicate read end to stdin
        close(pipefds[0]); // Close original read end

        execlp("wc", "wc", (char *)NULL);
        perror("execlp");
        exit(EXIT_FAILURE);
    }

    // Parent process: close both ends and wait for children
    close(pipefds[0]);
    close(pipefds[1]);

    wait(NULL);
    wait(NULL);

    return 0;
}

/*
OUTPUT:
cant guarentee that fup() will be assigned to stdin and stdout


-rw-r--r-- 1 irfan_shaik irfan_shaik   798 Sep 12 09:54 demo.c
-rwxr-xr-x 1 irfan_shaik irfan_shaik 16312 Sep 18 17:57 my
-rwxr-xr-x 1 irfan_shaik irfan_shaik 16232 Sep 12 09:55 mys
-rw-r--r-- 1 irfan_shaik irfan_shaik   986 Sep 18 16:38 probelm13a.c
-rw-r--r-- 1 irfan_shaik irfan_shaik  1096 Sep 17 19:49 problem11.c
-rw-r--r-- 1 irfan_shaik irfan_shaik  1239 Sep 17 19:51 problem12.c
-rw-r--r-- 1 irfan_shaik irfan_shaik  1044 Sep 18 16:38 problem13b.c
-rw-r--r-- 1 irfan_shaik irfan_shaik   488 Sep 18 16:59 problem14.c
-rw-r--r-- 1 irfan_shaik irfan_shaik  1240 Sep 18 17:16 problem15.c
-rw-r--r-- 1 irfan_shaik irfan_shaik  1644 Sep 18 17:31 problem16.c
-rw-r--r-- 1 irfan_shaik irfan_shaik  1127 Sep 18 17:55 problem17a.c
-rw-r--r-- 1 irfan_shaik irfan_shaik  1600 Sep 18 17:56 problem17b.c
-rw-r--r-- 1 irfan_shaik irfan_shaik  1595 Sep 18 17:57 problem17c.c
-rw-r--r-- 1 irfan_shaik irfan_shaik   939 Sep 12 09:17 problem1a.c
-rw-r--r-- 1 irfan_shaik irfan_shaik   889 Sep 12 09:59 problem1b.c
-rw-r--r-- 1 irfan_shaik irfan_shaik  1083 Sep 12 10:05 problem1c.c
-rw-r--r-- 1 irfan_shaik irfan_shaik  2034 Sep 12 10:30 problem2.c
-rw-r--r-- 1 irfan_shaik irfan_shaik  1619 Sep 12 10:42 problem3.c
-rw-r--r-- 1 irfan_shaik irfan_shaik   793 Sep 12 10:58 problem4.c
-rw-r--r-- 1 irfan_shaik irfan_shaik   961 Sep 17 14:32 problem6.c
-rw-r--r-- 1 irfan_shaik irfan_shaik   885 Sep 17 14:39 problem7.c
-rw-r--r-- 1 irfan_shaik irfan_shaik  3384 Sep 18 15:31 problem8.c
-rw-r--r-- 1 irfan_shaik irfan_shaik   715 Sep 17 19:47 problem9.c
*/