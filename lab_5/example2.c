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
    if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {  // Child process
        close(fd[0]);  // Close read end
        dup2(fd[1], STDOUT_FILENO);  // Redirect stdout to pipe
        close(fd[1]);  // Close original write end
        execlp("ls", "ls", NULL);  // Execute `ls` and send output to pipe
        perror("execlp");
        exit(EXIT_FAILURE);
    } else {  // Parent process
        close(fd[1]);  // Close write end
        char buffer[200];
        read(fd[0], buffer, sizeof(buffer));
        printf("Parent received from ls command:\n%s", buffer);
        close(fd[0]);  // Close read end
    }
    return 0;
}
