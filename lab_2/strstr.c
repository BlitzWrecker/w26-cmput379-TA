#include <string.h>
#include <stdio.h>

int main() {
    const char *sentence = "This is a sentence. This is another sentence.";

    char *substring = strstr(sentence, "sentence");
    printf("%s\n", substring);
    // sentence. This is another sentence.
}
