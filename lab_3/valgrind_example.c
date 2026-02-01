// A simple memory leak example for Valgrind
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

int check_args(int argc, char *argv[], int *start) {
    if (argc != 2 || strlen(argv[1]) == 0) {
        return 1;
    }

    char *p = NULL;
    errno = 0;    // not 'int errno', because the '#include' already defined it
    *start = (int)strtol(argv[1], &p, 10);
    if (*p != '\0' || errno != 0) {
        return 1;
    }
    return 0;
}

int main(int argc, char *argv[]) {
    int num_elements = 0;
    if (check_args(argc, argv, &num_elements)) {
        printf("Usage: ./example start\n");
        return 1;
    }

    // Allocate memory but do not free it to simulate a memory leak
    int *leak = (int *)malloc(sizeof(int) * num_elements);
    if (leak == NULL) {
        perror("malloc failed");
        return 1;
    }

    // Use the allocated memory
    for (int i = 0; i < num_elements; i++) {
        leak[i] = i * i;
        printf("%d ", leak[i]);
    }
    printf("\n");

    // Intentionally not freeing the allocated memory to demonstrate a leak
    // free(leak);

    return 0;
}