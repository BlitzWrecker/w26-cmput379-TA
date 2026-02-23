#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <fcntl.h>

int main() {
    int pipefd[2];
    pid_t cpid;

    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    cpid = fork();

    if (cpid == -1) {
        perror("fork p1");
        exit(EXIT_FAILURE);
    } else if (cpid == 0) {    // Child process
        close(pipefd[0]);          // Close unused read end

        int input_fd = open("file_input.txt", O_RDONLY);
        
        if (input_fd == -1) {
            perror("open");
            exit(EXIT_FAILURE);
        }

        // Redirect stdin to the input file
        dup2(input_fd, STDIN_FILENO);
        close(input_fd);

        // Redirect stdout to the write end of the pipe
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]);          // Close original write end

        // Execute the command
        execve("/usr/bin/grep", (char *[]){"/usr/bin/grep", "sshd", NULL}, NULL);
        perror("execve p1");          // execve only returns on error
        exit(EXIT_FAILURE);
    } 
    
    // Parent process
    cpid = fork();

    if (cpid == -1) {
        perror("fork p2");
        exit(EXIT_FAILURE);
    } else if (cpid == 0) {    // Child process
        close(pipefd[1]);          // Close unused write end
        dup2(pipefd[0], STDIN_FILENO); // Redirect stdin to the read end of the pipe

        char buffer[128];
        ssize_t nbytes;

        int output_fd = open("file_output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);

        if (output_fd == -1) {
            perror("open");
            exit(EXIT_FAILURE);
        }

        // Redirect stdout to the output file
        dup2(output_fd, STDOUT_FILENO);
        close(output_fd);

        execve("/usr/bin/wc", (char *[]){"/usr/bin/wc", "-w", NULL}, NULL);
        perror("execve p2");          // execve only returns on error
        exit(EXIT_FAILURE);
    }

    close(pipefd[0]);          // Close read end
    close(pipefd[1]);          // Close write end
    wait(NULL);          // Wait for child process to finish
    wait(NULL);          // Wait for second child process to finish
    exit(EXIT_SUCCESS);
}