#include <stdio.h>

int main() {
    const char *sentence = "3 2 1 blast off!";
    int num1, num2, num3;
    char word[16];

    sscanf(sentence, "%d %d %d %15s", &num1, &num2, &num3, word);
    printf("%d\n", num1 + num2 + num3);  // 10
    printf("%s\n", word);  // blast
}
