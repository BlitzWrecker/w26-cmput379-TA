// Original authors: Jake Tuero and Ali Rafiei
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    int fd[2];
    if (pipe(fd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid_t pid = fork();
    if (pid == 0) {  // Child process
        close(fd[0]);  // Close read end
        sleep(3);  // Simulate delay before writing
        write(fd[1], "Data", 5);
        close(fd[1]);
        exit(EXIT_SUCCESS);
    } else {  // Parent process
        close(fd[1]);  // Close write end
        printf("Parent waiting for data...\n");
        char buffer[10];
        read(fd[0], buffer, sizeof(buffer));
        printf("Parent received: %s\n", buffer);
        close(fd[0]);
    }
    return 0;
}
