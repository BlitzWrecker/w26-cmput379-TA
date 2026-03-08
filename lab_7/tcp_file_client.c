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
    exit(0);
}

int open_socket() {
    int socket_fd = -1;
    if ((socket_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        error("Error opening socket");
    }
    return socket_fd;
}

void call_socket(int socket_fd, const char *hostname, int port_number) {
    // Initialize the data structure
    struct sockaddr_in serv_addr;
    memset(&serv_addr, 0, sizeof(serv_addr));

    // Get the host address from the hostname
    struct hostent *server;
    if ((server = gethostbyname(hostname)) == NULL) {
        close(socket_fd);
        error("Error, unknown host");
    }

    // Set the required fields
    memcpy((char *)&serv_addr.sin_addr.s_addr, (char *)server->h_addr, (uint8_t)server->h_length);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons((uint16_t)port_number);

    // Try to connect
    if (connect(socket_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        error("Error connecting to server");
    }
}

int main(int argc, char *argv[]) {
    // Check input args
    if (argc < 3) {
        printf("usage %s hostname port\n", argv[0]);
        exit(0);
    }
    const char *hostname = argv[1];
    int port_number = atoi(argv[2]);

    // Open a socket
    int socket_fd = open_socket();

    // Call the server
    call_socket(socket_fd, hostname, port_number);

    // Get message from server
    int bytes_read = 0;
    char buffer[1024];
    int img_file = open("received_file", O_WRONLY | O_CREAT, 0666);
    while ((bytes_read = (int)read(socket_fd, buffer, sizeof(buffer)))) {
        if (write(img_file, buffer, bytes_read) < 0) {
            error("Error writing to file");
        }
    }
    close(socket_fd);
    close(img_file);
    rename("received_file", "received_file.png");
    return 0;
}
