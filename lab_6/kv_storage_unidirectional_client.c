#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define FIFO_FILE  "kv_fifo_cs"

int main() {
    // Open FIFO for writing, we assume server already created it
    int fifo_cs = open(FIFO_FILE, O_WRONLY);
    if (fifo_cs == -1) {
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

    for (int i = 0; commands[i] != NULL; i++) {
        write(fifo_cs, commands[i], strlen(commands[i]) + 1);

        // wait a bit before sending next command so we don't botch all the commands together in the server's read
        // buffer as there are no message boundaries in FIFOs, and we cannot use read/write to block.
        sleep(1);
    }

    close(fifo_cs);
    return 0;
}