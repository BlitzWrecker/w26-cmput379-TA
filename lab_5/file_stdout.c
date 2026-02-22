#include <unistd.h>
#include <fcntl.h>


int main() {
    int file_input = open("file_output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    dup2(file_input, STDOUT_FILENO);  // Redirect stdout to file_output.txt
    close(file_input);  // Close original file descriptor
    execve("/usr/bin/ls", (char *[]){"ls", "-l", NULL}, NULL);  // Execute ls with redirected stdout
}