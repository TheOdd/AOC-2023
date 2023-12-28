#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

bool isValidArrangement(char* line, int lineLen, int* groups, int groupLen) {
    int gIdx = 0;
    int i = 0;
    while (i < lineLen) {
        if (gIdx >= groupLen)
            return false;
        if (line[i] != '#') {
            i++;
            continue;
        }
        // Start analyzing token
        int targetLen = groups[gIdx++];
        int curGroupLen = 0;
        for (; i < lineLen && line[i] == '#'; i++, curGroupLen++);
        if (curGroupLen != targetLen)
            return false;
    }
    return gIdx == groupLen;
}

int permutationHelper(char* line, int lineLen, int idx, int* groups, int groupLen) {
    while (idx < lineLen && line[idx] != '?')
        idx++;

    if (idx >= lineLen) {
        bool valid = isValidArrangement(line, lineLen, groups, groupLen);
        return valid ? 1 : 0;
    }

    char* lineCopy = malloc(lineLen * sizeof(*lineCopy));
    strncpy(lineCopy, line, lineLen);
    lineCopy[idx] = '.';
    line[idx] = '#';
    int a = permutationHelper(lineCopy, lineLen, idx+1, groups, groupLen);
    free(lineCopy);
    int b = permutationHelper(line, lineLen, idx+1, groups, groupLen);
    return a + b;
}

int main(int argc, char* argv[]) {
    (void)argc;
    (void)argv;
    FILE* in = fopen("input", "r");
    char* line = NULL;
    size_t len = 0;
    while (getline(&line, &len, in) != -1) {
        char* token = strtok(line, " ");
        char* layout = malloc(strlen(token) * sizeof(*layout));
        strcpy(layout, token);
        token = strtok(NULL, " ");
        int dummy[2] = {1, 2};
        int groupCount = 1;
        for (int i = 0; token[i] != '\0'; i++)
            groupCount += token[i] == ',';
        int* groups = malloc(groupCount * sizeof(*groups));

        permutationHelper(layout, strlen(layout), 0, dummy, 2);
        free(layout);
    }
    int dummy[] = {3,2,1};
    char* test = malloc(12 * sizeof(char));
    for (int i = 0; i < 12; i++) test[i] = "?###????????"[i];
    int res = permutationHelper(test, 12, 0, dummy, 3);
    printf("%d\n", res);
    bool valids[10];
    valids[0] = isValidArrangement(".###.##.#...", 12, dummy, 3);
    valids[1] = isValidArrangement(".###.##..#..", 12, dummy, 3);
    valids[2] = isValidArrangement(".###.##...#.", 12, dummy, 3);
    valids[3] = isValidArrangement(".###.##....#", 12, dummy, 3);
    valids[4] = isValidArrangement(".###..##.#..", 12, dummy, 3);
    valids[5] = isValidArrangement(".###..##..#.", 12, dummy, 3);
    valids[6] = isValidArrangement(".###..##...#", 12, dummy, 3);
    valids[7] = isValidArrangement(".###...##.#.", 12, dummy, 3);
    valids[8] = isValidArrangement(".###...##..#", 12, dummy, 3);
    valids[9] = isValidArrangement(".###....##.#", 12, dummy, 3);
    for (int i = 0; i < 10; i++)
        printf("%d\n", valids[i]);
    free(test);
    if (line) free(line);
    line = NULL;
    fclose(in);
    return EXIT_SUCCESS;
}
