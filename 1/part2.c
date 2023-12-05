#include <stdio.h>
#include <stdbool.h>
#include <string.h>

bool getNumber(const char* str, int* val);

int main(int argc, char* argv[]) {
    (void)argc;
    (void)argv;
    FILE *in = fopen("input", "r");
    int sum = 0;
    char line[1024] = {0};
    while (fscanf(in, "%s\n", line) != EOF) {
        int first = -1, last = 0;
        for (char* lp = line; *lp != '\0'; lp++) {
            int val = 0;
            if (getNumber(lp, &val)) {
                if (first == -1) first = val;
                last = val;
            }
        }
        sum += first * 10 + last;
    }
    fclose(in);
    printf("Sum: %d\n", sum);
}

bool getNumber(const char* str, int* val) {
    int strLen = strlen(str);
    char* digWords[] = {
        "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"
    };
    char c = *str;
    if (c >= '0' && c <= '9') {
        *val = c - '0';
        return true;
    }
    for (int i = 0; i < 9; i++) {
        int digLen = strlen(digWords[i]);
        if (strLen < digLen) continue;
        if (strncmp(str, digWords[i], digLen) == 0) {
            *val = i + 1;
            return true;
        }
    }
    return false;
}
