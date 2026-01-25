#include <stdio.h>
#include <string.h>

int main() {
    // Read from a file for deterministic input
    const char *cmd = "cat exercise_input.txt";

    // Buffer for each line
    char line[256];

    // Simulating reading multiple lines (e.g., from a file or pipe)
    FILE *fp = popen(cmd, "r");
    if (fp == NULL) {
        perror("popen failed");
        return 1;
    }

    printf("Matching for processes with 'sshd' in executable:\n");

    // Process each line
    while (fgets(line, sizeof(line), fp)) {
        // Variables to store parsed fields
        int pid, ppid;
        char user[64], exe[128];

        // Parse the line into components
        if (sscanf(line, "%d %d %63s %127s", &pid, &ppid, user, exe) == 4) {
            // NOTE: '63' and '127' are field width specifiers. 
            // They limit the maximum number of characters that sscanf will read for that field.
            
            printf("Parsed: PID=%d, PPID=%d, User=%s, Executable=%s\n", pid, ppid, user, exe);

            // Example string matching: Look for "sshd" in the executable
            if (strstr(exe, "sshd") != NULL) {
                printf("  Match found for PID=%d with executable '%s'\n", pid, exe);
            }
        } else {
            printf("Failed to parse line: %s", line);
        }
    }

    fclose(fp); // Close the simulated input
    return 0;
}
