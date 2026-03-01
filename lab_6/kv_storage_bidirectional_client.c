#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define FIFO_CS  "kv_fifo_cs"
#define FIFO_SC  "kv_fifo_sc"

int main() {
    // Open FIFO for writing, we assume server already created it
    int fifo_cs = open(FIFO_CS, O_WRONLY);
    if (fifo_cs == -1) {
        perror("open fifo");
        return 1;
    }

    // Open FIFO for reading, we assume server already created it
    int fifo_sc = open(FIFO_SC, O_RDONLY);
    if (fifo_sc == -1) {
        perror("open fifo");
        return 1;
    }

    char *commands[] = {
        "SET name Alice",
        "SET age 20",
        "GET name",
        "DEL name",
        "GET name",
        NULL
    };

    char buffer[512];

    for (int i = 0; commands[i] != NULL; i++) {
        write(fifo_cs, commands[i], strlen(commands[i]) + 1);
        read(fifo_sc, buffer, 512);
        printf("Server response: %s", buffer);
    }

    close(fifo_cs);
    close(fifo_sc);
    return 0;
}