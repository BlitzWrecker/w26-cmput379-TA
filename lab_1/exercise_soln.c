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

    // Keep reading until end of file
    while (fgets(buffer, sizeof(buffer), fp) != NULL)
        printf("%s", buffer);

    // This only reads a part of the output from popen()
    // fread(buffer, 1, sizeof(buffer), fp);
    // buffer[sizeof(buffer) - 1] = '\0';  // Ensure null-termination
    // printf("%s", buffer);

    // Close the process
    pclose(fp);
}

// Example usage
int main() {
    const char *command = "cat exercise_input.txt";
    read_from_popen(command);
    return 0;
}