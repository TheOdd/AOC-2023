#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define NUMS (21)

int main(int argc, char* argv[]) {
    (void)argc;
    (void)argv;
    FILE* in = fopen("input", "r");
    char* line = NULL;
    size_t len = 0;
    long sum = 0;
    while (getline(&line, &len, in) != -1) {
        long nums[NUMS] = {0};
        nums[0] = atol(strtok(line, " "));
        for (int i = 1; i < NUMS; i++)
            nums[i] = atol(strtok(NULL, " "));
        int lvl = 1;
        bool done = true;
        do {
            for (int i = 0; i < NUMS-lvl; i++)
                nums[i] = nums[i+1] - nums[i];

            done = true;
            for (int i = 0; i < NUMS-1-lvl; i++) {
                if (nums[i] != nums[i+1]) {
                    done = false;
                    break;
                }
            }

            lvl++;
        } while (!done);
        for (int i = NUMS - lvl; i < NUMS; i++)
            sum += nums[i];
    }
    printf("Sum: %ld\n", sum);
    fclose(in);
    if (line) free(line);
    return EXIT_SUCCESS;
}
