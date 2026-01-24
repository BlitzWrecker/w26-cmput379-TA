#include <stdio.h>
#include <stdlib.h>

int main() {
    const char *command = "ls -l";  // Example command to list files
    FILE *fp = popen(command, "r"); // Open a pipe to the child process
    if (fp == NULL) {
        perror("popen failed");
        return 1;
    }

    // The buffer size of 256 is an arbitrary default for typical command outputs
    // balancing memory efficiency and handling most line lengths.
    char line[256]; // Buffer for reading output
    printf("Output of command '%s':\n", command);
    while (fgets(line, sizeof(line), fp)) { // Read line by line
        printf("%s", line); // Print each line
    }

    int status = pclose(fp); // Close the pipe and get the child process exit status
    if (status == -1) {
        perror("pclose failed");
    } else {
        printf("Command exited with status %d\n", WEXITSTATUS(status));
    }

    return 0;
}
