#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

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

    // Print only if the line contains 'a'.
    if (strstr(buffer, "a"))
        printf("%s", buffer);
    else
        printf("The line does not contain the character 'a'.\n");


    // Close the process
    pclose(fp);
}

// Example usage
int main() {
    // const char *command = "echo 'Hello, World!'";
    const char *command = "echo 'This line contains a character a'";
    read_from_popen(command);
    return 0;
}