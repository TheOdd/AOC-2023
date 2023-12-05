#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    (void)argc;
    (void)argv;
    FILE* in = fopen("input", "r");
    int sum = 0;
    char* line = NULL;
    size_t len = 0;
    while (getline(&line, &len, in) != -1) {
        char* lp = line + 8;
        while (*lp < '0' || *lp > '9') lp++;
        char* cubes = strtok(lp, ";,");
        int max[3] = {0};
        while (cubes != NULL) {
            if (*cubes == ' ') cubes++;
            int num = 0;
            while (*cubes != ' ') {
                num *= 10;
                num += *cubes - '0';
                cubes++;
            }
            cubes++;
            for (int i = 0; i < 3; i++) {
                if (*cubes == "rgb"[i] && num > max[i])
                    max[i] = num;
            }
            cubes = strtok(NULL, ";,");
        }
        sum += max[0] * max[1] * max[2];
    }
    fclose(in);
    if (line)
        free(line);
    printf("Sum: %d\n", sum);
}
