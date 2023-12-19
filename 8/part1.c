#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LETTERS (26)

int main(int argc, char* argv[]) {
    (void)argc;
    (void)argv;
    char map[LETTERS][LETTERS][LETTERS][2][3] = {{{{{0}}}}};
    FILE* in = fopen("input", "r");
    size_t len = 0;
    char* directions = NULL;
    ssize_t dirLen = getline(&directions, &len, in);
    directions[--dirLen-1] = '\0';
    char* line = NULL;
    while (getline(&line, &len, in) != -1) {
        if (line[0] == '\n') continue;
        char (*entry)[3] = map[line[0]-'A'][line[1]-'A'][line[2]-'A'];
        for (int i = 0; i < 3; i++) {
            entry[0][i] = line[7 + i];
            entry[1][i] = line[12 + i];
        }
    }
    fclose(in);
    if (line) free(line);
    int steps = 0;
    char* curKey = "AAA";
    while (strcmp(curKey, "ZZZ") != 0) {
        int idx = directions[steps++ % dirLen] == 'L' ? 0 : 1;
        curKey = map[curKey[0]-'A'][curKey[1]-'A'][curKey[2]-'A'][idx];
    }
    printf("Steps: %d\n", steps);
    if (directions) free(directions);
    return EXIT_SUCCESS;
}
