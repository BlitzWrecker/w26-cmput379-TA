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
#include <alsa/asoundlib.h>

void error(const char *msg) {
    perror(msg);
    exit(1);
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

int open_socket() {
    int socket_fd = -1;
    if ((socket_fd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
        error("Error opening socket");
    }
    return socket_fd;
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
    bind_socket(socket_fd, port_number);

    snd_pcm_t *pcm;
    snd_pcm_open(&pcm, "default", SND_PCM_STREAM_PLAYBACK, 0);

    snd_pcm_set_params(
        pcm,
        SND_PCM_FORMAT_S16_LE,
        SND_PCM_ACCESS_RW_INTERLEAVED,
        1,
        44100,
        1,
        500000
    );

    unsigned char buffer[4096];
    int offset = 0;
    while (1) {
        ssize_t n = recvfrom(socket_fd, buffer + offset, 4096, 0, NULL, NULL);
        if (n < 0) {
            error("Error receiving data");
        }
        snd_pcm_writei(pcm, buffer, n / 2);
    }

    close(socket_fd);
    return 0;
}
