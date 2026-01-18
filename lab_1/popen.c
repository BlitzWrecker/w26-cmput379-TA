#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>

int main() {
    int pipefd[2];
    pid_t cpid;

    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    cpid = fork();

    if (cpid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    } else if (cpid == 0) {    // Child process
        close(pipefd[0]);          // Close unused read end

        // Redirect stdout to the write end of the pipe
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]);          // Close original write end

        // Execute the command
        execve("/usr/bin/echo", (char *[]){"echo", "Hello World!", NULL}, NULL);
        perror("execve");          // execve only returns on error
        exit(EXIT_FAILURE);
    } else {                        // Parent process
        close(pipefd[1]);          // Close unused write end

        char buffer[128];
        ssize_t nbytes;

        // Read from the read end of the pipe
        while ((nbytes = read(pipefd[0], buffer, sizeof(buffer)-1)) > 0) {
            buffer[nbytes] = '\0';  // Null-terminate the string
            printf("%s", buffer);   // Print the output from child
        }

        if (nbytes == -1) {
            perror("read");
            exit(EXIT_FAILURE);
        }

        close(pipefd[0]);          // Close read end
        wait(NULL);                // Wait for child process to finish
        exit(EXIT_SUCCESS);
    }
}