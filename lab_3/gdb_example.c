// Orginal author: Jake Tuero
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

void foo(int start, int *ret) {
    int i = 0;
    int sum = start;
    for (i = 0; i <= 10; ++i) {
#ifdef USE_BUG
        ret = NULL;
#endif
        sum += i;
    }
    *ret = sum;
}

int main(int argc, char *argv[]) {
    int start = 0;
    if (check_args(argc, argv, &start)) {
        printf("Usage: ./example start\n");
        return 1;
    }

    int ret = -1;
    foo(start, &ret);
    printf("sum from %d to %d = %d\n", start, start + 10, ret);
}
