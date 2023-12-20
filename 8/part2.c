#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define LETTERS (26)

long gcd(long a, long b) {
    while (b != 0) {
        long t = b;
        b = a % b;
        a = t;
    }
    return a;
}

long lcm(long a, long b) {
    long g = gcd(a, b);
    return a / g * b;
}

long lcmArr(long* arr, int len) {
    long res = lcm(arr[0], arr[1]);
    for (int i = 2; i < len; i++)
        res = lcm(res, arr[i]);
    return res;
}

int main(int argc, char* argv[]) {
    char map[LETTERS][LETTERS][LETTERS][2][3] = {{{{{0}}}}};
    FILE* in = fopen("input", "r");
    size_t len = 0;
    char* directions = NULL;
    ssize_t dirLen = getline(&directions, &len, in) - 1;
    directions[dirLen-1] = '\0';
    char* line = NULL;
    char* keys = NULL;
    int numKeys = 0;
    while (getline(&line, &len, in) != -1) {
        if (line[0] == '\n') continue;
        char (*entry)[3] = map[line[0]-'A'][line[1]-'A'][line[2]-'A'];
        for (int i = 0; i < 3; i++) {
            entry[0][i] = line[7 + i];
            entry[1][i] = line[12 + i];
        }
        if (line[2] == 'A') {
            keys = realloc(keys, sizeof(char) * 3 * ++numKeys);
            strncpy(keys + (numKeys - 1) * 3 , line, 3);
        }
    }
    fclose(in);
    if (line) free(line);
    bool* isDone = calloc(numKeys, sizeof(bool));
    long* keySteps = calloc(numKeys, sizeof(long));
    int steps = 0;
    while (true) {
        bool done = true;
        for (int i = 0; i < numKeys; i++) {
            if (!isDone[i]) {
                done = false;
                break;
            }
        }
        if (done) break;

        int idx = directions[steps++ % dirLen] == 'L' ? 0 : 1;
        for (int i = 0; i < numKeys; i++) {
            if (isDone[i]) continue;
            char* k = &keys[i*3];
            strncpy(k, map[k[0] - 'A'][k[1] - 'A'][k[2] - 'A'][idx], 3);
            if (k[2] == 'Z') {
                isDone[i] = true;
                keySteps[i] = steps;
            }
        }
    }
    if (directions) free(directions);
    if (keys) free(keys);
    if (isDone) free(isDone);
    long res = lcmArr(keySteps, numKeys);
    printf("Steps: %ld\n", res);
    if (keySteps) free(keySteps);
    return EXIT_SUCCESS;
}
