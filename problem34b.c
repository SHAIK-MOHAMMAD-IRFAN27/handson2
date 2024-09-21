/*
name: problem34b.c
author: SHAIK  MOHAMMAD IRFAN 
description:Write a program to create a concurrent server. 
b. use pthread_create  
 date : 20th September 2024
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <pthread.h>

#define PORT 8080
#define BUFFER_SIZE 1024

void *handle_client(void *arg) {
    int client_socket = *(int *)arg;
    char buffer[BUFFER_SIZE];
    int bytes_read;

    // Read data from the client
    bytes_read = read(client_socket, buffer, BUFFER_SIZE);
    if (bytes_read > 0) {
        buffer[bytes_read] = '\0'; // Null-terminate the string
        printf("Client: %s\n", buffer);
        
        // Send a response back to the client
        const char *response = "Message received!";
        write(client_socket, response, strlen(response));
    }

    close(client_socket);
    return NULL; // End thread
}

int main() {
    int server_fd, client_socket;
    struct sockaddr_in address;
    int opt = 1;
    socklen_t addrlen = sizeof(address);

    // Create socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket failed");
        exit(EXIT_FAILURE);
    }

    // Set socket options
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    // Bind the socket
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);
    bind(server_fd, (struct sockaddr *)&address, sizeof(address));

    // Start listening for connections
    listen(server_fd, 3);
    printf("Server listening on port %d...\n", PORT);

    while (1) {
        // Accept a connection
        if ((client_socket = accept(server_fd, (struct sockaddr *)&address, &addrlen)) < 0) {
            perror("Accept");
            continue;
        }

        // Create a new thread to handle the client
        pthread_t thread_id;
        if (pthread_create(&thread_id, NULL, handle_client, (void *)&client_socket) != 0) {
            perror("pthread_create");
            close(client_socket);
        } else {
            pthread_detach(thread_id); // Detach the thread to avoid memory leaks
        }
    }

    close(server_fd);
    return 0;
}


/*
output:
in other terminal (telnet localhost 8080)
Trying 127.0.0.1...
Connected to localhost.
Escape character is '^]'.
irfan
Message received!Connection closed by foreign host.


Server listening on port 8080...
Client: irfan
*/