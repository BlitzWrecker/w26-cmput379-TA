#include <stdio.h>
#include <string.h>

int main() {
    // Example input simulating multiple lines of process data
    const char *input =
        "123 456 someuser /usr/bin/example --option\n"
        "789 123 otheruser /usr/bin/other\n"
        "101 456 root /sbin/init --this_text_is_not_displayed\n";

    // Buffer for each line
    char line[256];

    // Simulating reading multiple lines (e.g., from a file or pipe)
    FILE *fp = fmemopen((void *)input, strlen(input), "r");
    if (fp == NULL) {
        perror("fmemopen failed");
        return 1;
    }

    printf("Matching for processes with 'example' in executable:\n");

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

            // Example string matching: Look for "example" in the executable
            if (strstr(exe, "example") != NULL) {
                printf("  Match found for PID=%d with executable '%s'\n", pid, exe);
            }
        } else {
            printf("Failed to parse line: %s", line);
        }
    }

    fclose(fp); // Close the simulated input
    return 0;
}
