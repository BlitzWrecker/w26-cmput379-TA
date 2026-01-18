#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

// Function to read content from popen()
void read_from_popen(const char *command) {
    FILE *fp;
    char buffer[128];
    int numbers[4];

    // Open the command for reading
    fp = popen(command, "r");
    if (fp == NULL) {
        printf("Failed to run command\n");
        exit(1);
    }

    // Read BUFFER number of bytes from the input
    fread(buffer, 1, sizeof(buffer), fp);

    // Parse the integers and the remaining string from the buffer
    sscanf(buffer, "%d %d %d %d %s", numbers, numbers + 1, numbers + 2, numbers + 3, buffer);

    // Sum the integers to show that they were correctly parsed
    int sum = numbers[0] + numbers[1] + numbers[2] + numbers[3];

    printf("Sum: %d\n", sum);
    printf("%s\n", buffer);

    // Close the process
    pclose(fp);
}

// Example usage
int main() {
    const char *command = "echo '4 3 2 1 Blast off!'";
    read_from_popen(command);
    return 0;
}