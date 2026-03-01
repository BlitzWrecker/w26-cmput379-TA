// Adapted from kv_storage_bidrectional.c
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>

#define MAX_STORE 100
#define MAX_KEY   64
#define MAX_VAL   256
#define BUF_SIZE  512
#define DB_FILE   "kv_store.txt"
#define FIFO_FILE  "kv_fifo_cs"

typedef struct {
    char key[MAX_KEY];
    char value[MAX_VAL];
    int used;
} kv_pair;

kv_pair store[MAX_STORE];

/* ---------- Persistence ---------- */

void save_to_file() {
    FILE *fp = fopen(DB_FILE, "w");
    if (!fp) {
        perror("fopen write");
        return;
    }

    for (int i = 0; i < MAX_STORE; i++) {
        if (store[i].used) {
            fprintf(fp, "%s %s\n", store[i].key, store[i].value);
        }
    }

    fclose(fp);
}

void load_from_file() {
    FILE *fp = fopen(DB_FILE, "r");
    if (!fp) return;  // no file yet

    char key[MAX_KEY], value[MAX_VAL];

    while (fscanf(fp, "%63s %255s", key, value) == 2) {
        for (int i = 0; i < MAX_STORE; i++) {
            if (!store[i].used) {
                store[i].used = 1;
                strcpy(store[i].key, key);
                strcpy(store[i].value, value);
                break;
            }
        }
    }

    fclose(fp);
}

/* ---------- KV Operations ---------- */

int find_key(const char *key) {
    for (int i = 0; i < MAX_STORE; i++) {
        if (store[i].used && strcmp(store[i].key, key) == 0)
            return i;
    }
    return -1;
}

void handle_command(char *cmd) {
    char op[16], key[MAX_KEY], value[MAX_VAL] = {0};

    sscanf(cmd, "%15s %63s %255s", op, key, value);

    if (strcmp(op, "SET") == 0) {
        int idx = find_key(key);

        if (idx == -1) {
            for (int i = 0; i < MAX_STORE; i++) {
                if (!store[i].used) {
                    store[i].used = 1;
                    strcpy(store[i].key, key);
                    strcpy(store[i].value, value);
                    break;
                }
            }
        } else {
            strcpy(store[idx].value, value);
        }

        save_to_file();
        printf("OK\n");
    }
    else if (strcmp(op, "GET") == 0) {
        int idx = find_key(key);
        if (idx == -1)
            printf("NOT_FOUND\n");
        else
            printf("OK %s\n", store[idx].value);
    }
    else if (strcmp(op, "DEL") == 0) {
        int idx = find_key(key);
        if (idx == -1)
            printf("NOT_FOUND\n");
        else {
            store[idx].used = 0;
            save_to_file();
            printf("OK\n");
        }
    }
    else {
        printf("ERROR unknown_command\n");
    }
}

/* ---------- Main ---------- */

int main() {
    load_from_file();

    // Create FIFO. 0666 means read/write permissions for everyone
    if (mkfifo(FIFO_FILE, 0666) == -1) {
        perror("mkfifo");
        return 1;
    }

    // Open FIFO for reading
    int fifo_cs = open(FIFO_FILE, O_RDONLY);
    if (fifo_cs == -1) {
        perror("open fifo");
        return 1;
    }

    char buffer[BUF_SIZE];

    while (read(fifo_cs, buffer, BUF_SIZE) > 0) {
        handle_command(buffer);
    }

    close(fifo_cs);
    unlink(FIFO_FILE);

    return 0;
}