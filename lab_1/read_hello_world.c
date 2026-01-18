#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Function to read content from popen()
void read_from_popen(const char *command) {
    FILE *fp;
    char buffer[128];

    // Open the command for reading
    fp = popen(command, "r");
    if (fp == NULL) {
        printf("Failed to run command\n");
        exit(1);
    }

    // Read BUFFER number of bytes from the input
    fread(buffer, 1, sizeof(buffer), fp);
    printf("%s", buffer);


    // Close the process
    pclose(fp);
}

// Example usage
int main() {
    const char *command = "echo 'Hello, World!'";
    read_from_popen(command);
    return 0;
}