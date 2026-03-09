#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

void error(const char *msg) {
    perror(msg);
    exit(1);
}

int open_socket() {
    int socket_fd = -1;
    if ((socket_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        error("Error opening socket");
    }
    return socket_fd;
}

// Assign the socket to a port
void bind_socket(int socket_fd, int port_number) {
    // Initialize the data structure
    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));

    // Set the required fields
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons((uint16_t)port_number);
    serv_addr.sin_addr.s_addr = INADDR_ANY;

    // Try to bind socket
    if (bind(socket_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        error("Error binding socket to this server");
    }
}

int main(int argc, char *argv[]) {
    // Check input args
    if (argc < 2) {
        printf("usage %s port\n", argv[0]);
        exit(0);
    }
    int port_number = atoi(argv[1]);

    // Open a socket
    int socket_fd = open_socket();

    // Bind socket to all local interfaces
    bind_socket(socket_fd, port_number);

    // Allow process to listen on socket for connections
    if (listen(socket_fd, 5) == -1) {
        error("Error listening to socket");
    }

    printf("Waiting for connections.\n");

    // Block process until a client connects to this server
    int connected_socket_fd = 0;
    struct sockaddr_in client_addr;
    int child_counter = 0;

    // Loop to accept multiple client connections
    while (1) {
        int client_addr_len = sizeof(client_addr);
        if ((connected_socket_fd = accept(socket_fd, (struct sockaddr *)&client_addr, (socklen_t *)&client_addr_len)) < 0) {
            error("Error accepting connection");
        }

        pid_t pid = fork();
        if (pid < 0) {
            error("Error forking process");
        } else if (pid == 0) { // Spawn child process to handle client connection
            pid_t child_pid = getpid();
            char *ip = inet_ntoa(client_addr.sin_addr);
            printf("===%d Child %d=== Client %s connected!\n", child_pid, child_counter + 1, ip);

            // Read message from client
            int bytes_read = 0;
            char buffer[512];
            if ((bytes_read = (int)read(connected_socket_fd, buffer, sizeof(buffer))) < 0) {
                perror("Error reading from socket");
            }
            buffer[bytes_read] = '\0';
            printf("===%d Child %d=== Received from client: %s", child_pid, child_counter + 1, buffer);

            // Send message to client
            int bytes_written = 0;
            char reply[1024];
            snprintf(reply, sizeof(reply), "===%d Child %d=== You said %s", child_pid, child_counter + 1, buffer);

            sleep(5); // Simulate some work being done by the child process

            if ((bytes_written = (int)write(connected_socket_fd, reply, strlen(reply))) < 0) {
                perror("Error writing to socket");
            }
            close(connected_socket_fd);
            close(socket_fd);
            exit(0);
        } else {
            child_counter++;
            close(connected_socket_fd);
        }
    }

    // Under the current implementation, the parent process will never reach this point. In a real server, we would want
    // to handle termination signals and clean up child processes properly.
    for (int i = 0; i < child_counter; i++) {
        wait(NULL);
    }
    
    close(socket_fd);
    return 0;
}
