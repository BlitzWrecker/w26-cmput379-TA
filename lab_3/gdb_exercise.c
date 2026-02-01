// A complex memory management example with nested allocations
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// A struct with nested dynamic memory allocation
typedef struct {
    char *name;
    int **data;
} Item;

int main() {
    int n = 5;
    // Allocate an array of pointers
    Item *item_array = (Item *)malloc(n * sizeof(Item));
    if (item_array == NULL) {
        perror("Failed to allocate item_array");
        return 1;
    }

    for (int i = 0; i < n; i++) {
        // Allocate memory for the name
        item_array[i].name = (char *)malloc(20 * sizeof(char));
        if (item_array[i].name == NULL) {
            perror("Failed to allocate name");
            return 1;
        }
        snprintf(item_array[i].name, 20, "Item_%d", i);

        // Allocate a 2D array (5x5)
        item_array[i].data = (int **)malloc(5 * sizeof(int *));
        if (item_array[i].data == NULL) {
            perror("Failed to allocate data rows");
            return 1;
        }

        for (int j = 0; j < 5; j++) {
            item_array[i].data[j] = (int *)malloc(5 * sizeof(int));
            if (item_array[i].data[j] == NULL) {
                perror("Failed to allocate data columns");
                return 1;
            }
            for (int k = 0; k < 5; k++) {
                item_array[i].data[j][k] = (i + j + k);
            }
        }
    }

    return 0;
}