#include <stdio.h>

// NOTE: There is no "one way" of handling data structures
// This is one example from many other possible methods

#define MAX_PROCESSES 10 // Maximum capacity for simplicity

typedef struct {
    int pid;        // Process ID
    int ppid;       // Parent Process ID
    char user[64];  // User who owns the process
    char exe[128];  // Executable name or path
} Process;

int main() {
    // Example data simulating a list of processes
    Process processes[MAX_PROCESSES] = {
        {123, 0, "root", "/sbin/init"},
        {456, 123, "user1", "/usr/bin/bash"},
        {789, 123, "user2", "/usr/bin/ssh"},
    };

    int numProcesses = 3; // Current number of valid entries

    printf("Initial Stored Processes:\n");
    for (int i = 0; i < numProcesses; i++) {
        printf("PID: %d, PPID: %d, User: %s, Executable: %s\n",
               processes[i].pid, processes[i].ppid,
               processes[i].user, processes[i].exe);
    }

    // Hardcoding the addition of one more process
    processes[3] = (Process){1010, 789, "user3", "/usr/bin/example"};
    numProcesses++; // Increment the count

    printf("\nHardcoded new process added (PID=1010, PPID=789, User=user3, Executable=/usr/bin/example).\n");

    // Display updated processes
    printf("\nUpdated Stored Processes:\n");
    for (int i = 0; i < numProcesses; i++) {
        printf("PID: %d, PPID: %d, User: %s, Executable: %s\n",
               processes[i].pid, processes[i].ppid,
               processes[i].user, processes[i].exe);
    }

    // Find and print processes with a specific parent PID
    int targetPpid = 123;
    printf("\nProcesses with PPID=%d:\n", targetPpid);
    for (int i = 0; i < numProcesses; i++) {
        if (processes[i].ppid == targetPpid) {
            printf("PID: %d, Executable: %s\n",
                   processes[i].pid, processes[i].exe);
        }
    }

    return 0;
}
