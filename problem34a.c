/*
name: problem34a.c
author: SHAIK  MOHAMMAD IRFAN 
description:Write a program to create a concurrent server. 
a. use fork  
 date : 20th September 2024
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/wait.h>

#define PORT 8080
#define BUFFER_SIZE 1024

void handle_client(int client_socket) {
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
    exit(0); // End child process
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

        // Fork a new process to handle the client
        if (fork() == 0) {
            close(server_fd); // Close the listening socket in the child process
            handle_client(client_socket);
        }
        close(client_socket); // Close the client socket in the parent process
        waitpid(-1, NULL, WNOHANG); // Clean up terminated child processes
    }

    close(server_fd);
    return 0;
}
/*
output:

---->in other terminal
Trying 127.0.0.1...
Connected to localhost.
Escape character is '^]'.
hello
Message received!Connection closed by foreign host.

--->in main terminal

Server listening on port 8080...
Client: hello
*/