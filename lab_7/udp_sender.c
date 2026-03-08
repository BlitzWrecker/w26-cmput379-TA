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
#include <arpa/inet.h>

void error(const char *msg) {
    perror(msg);
    exit(0);
}

int open_socket() {
    int socket_fd = -1;
    if ((socket_fd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
        error("Error opening socket");
    }
    return socket_fd;
}

int main(int argc, char *argv[]) {
    // Check input args
    if (argc < 3) {
        printf("usage %s port /path/to/file\n", argv[0]);
        exit(0);
    }
    int port_number = atoi(argv[1]);
    const char *file_name = argv[2];

    FILE *pipe;
    unsigned char buffer[8192];
    char command[256];
    snprintf(command, sizeof(command), "ffmpeg -loglevel quiet -i %s -f s16le -acodec pcm_s16le -ac 2 -ar 44100 -", file_name);

    pipe = popen(command, "r");

    if (!pipe) {
        perror("popen");
        return 1;
    }

    // Open a socket
    int socket_fd = open_socket();
    // Initialize the data structure
    struct sockaddr_in recv_addr;
    memset(&recv_addr, 0, sizeof(recv_addr));

    // Set the required fields
    recv_addr.sin_family = AF_INET;
    recv_addr.sin_port = htons((uint16_t)port_number);
    recv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    while (1) {
        size_t n = fread(buffer, 1, sizeof(buffer), pipe);
        if (n == 0) break;

        sendto(socket_fd, buffer, n, 0, (struct sockaddr *)&recv_addr, sizeof(recv_addr));
        usleep(50000);
    }
    
    close(socket_fd);
    return 0;
}
