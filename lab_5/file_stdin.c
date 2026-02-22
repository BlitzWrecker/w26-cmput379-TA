#include <unistd.h>
#include <fcntl.h>


int main() {
    int file_input = open("file_input.txt", O_RDONLY);
    dup2(file_input, STDIN_FILENO);  // Redirect stdin to file_input.txt
    close(file_input);  // Close original file descriptor
    execve("/usr/bin/grep", (char *[]){"grep", "--color=always","paullu", NULL}, NULL);  // Execute grep with redirected stdin
}