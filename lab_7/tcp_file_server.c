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
#include <fcntl.h>

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
    if (argc < 3) {
        printf("usage %s port /path/to/file\n", argv[0]);
        exit(0);
    }
    int port_number = atoi(argv[1]);
    const char *file_path = argv[2];

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
    int client_addr_len = sizeof(client_addr);
    if ((connected_socket_fd = accept(socket_fd, (struct sockaddr *)&client_addr, (socklen_t *)&client_addr_len)) < 0) {
        error("Error accepting connection");
    }
    char *ip = inet_ntoa(client_addr.sin_addr);
    printf("Client %s connected!\n", ip);

    int file = open(file_path, O_RDONLY);
    if (file == -1) {
        error("Error opening file");
    }

    char buffer[512];
    int bytes_read;
    while ((bytes_read = (int)read(file, buffer, sizeof(buffer))) > 0) {
        if (write(connected_socket_fd, buffer, bytes_read) < 0) {
            error("Error writing to socket");
        }
    }

    close(connected_socket_fd);
    close(socket_fd);
    return 0;
}
