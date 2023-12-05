#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    (void)argc;
    (void)argv;
    FILE* in = fopen("input", "r");
    int sum = 0;
    char* line = NULL;
    size_t len = 0;
    while (getline(&line, &len, in) != -1) {
        bool winningNums[100] = {0};
        char* lp = line + 10;
        for (int i = 0; i < 10; i++, lp += 3) {
            int num = strtol(lp, NULL, 10);
            winningNums[num] = true;
        }
        lp += 2;
        int count = 0;
        for (int i = 0; i < 25; i++, lp += 3) {
            int num = strtol(lp, NULL, 10);
            if (winningNums[num]) count++;
        }
        if (count)
            sum += 1 << (count - 1);
    }
    fclose(in);
    if (line) free(line);
    printf("Sum: %d\n", sum);
}
