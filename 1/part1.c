#include <stdio.h>

int main(int argc, char* argv[]) {
    (void)argc;
    (void)argv;
    FILE* in = fopen("input", "r");
    int sum = 0;
    char line[1024] = {0};
    while (fscanf(in, "%s\n", line) != EOF) {
        int first = -1, last = 0;
        for (char *lp = line; *lp != '\0'; lp++) {
            char c = *lp;
            if (c < '0' || c > '9') continue;
            int digit = c - '0';
            if (first == -1) first = digit;
            last = digit;
        }
        sum += first * 10 + last;
    }
    fclose(in);
    printf("Sum: %d\n", sum);
}
