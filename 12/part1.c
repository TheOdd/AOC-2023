#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

bool isValidArrangement(char* line, int lineLen, int* groups, int groupLen) {
    int gIdx = 0;
    int i = 0;
    while (i < lineLen) {
        if (line[i] != '#') {
            i++;
            continue;
        }
        if (gIdx >= groupLen)
            return false;
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

    if (idx >= lineLen)
        return isValidArrangement(line, lineLen, groups, groupLen);

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
    int res = 0;
    while (getline(&line, &len, in) != -1) {
        char* token = strtok(line, " ");
        int layoutLen = strlen(token);
        char* layout = malloc(layoutLen * sizeof(*layout));
        memcpy(layout, token, layoutLen);
        token = strtok(NULL, " ");
        int groupCount = 1;
        for (int i = 0; token[i] != '\0'; i++)
            groupCount += token[i] == ',';
        int* groups = malloc(groupCount * sizeof(*groups));
        int i = 0;
        token = strtok(token, ",");
        while (token != NULL) {
            groups[i++] = atoi(token);
            token = strtok(NULL, ",");
        }
        res += permutationHelper(layout, layoutLen, 0, groups, groupCount);
        free(groups);
        free(layout);
    }
    printf("%d\n", res);
    if (line) free(line);
    line = NULL;
    fclose(in);
    return EXIT_SUCCESS;
}
