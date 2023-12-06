#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>

#define NUM_SEEDS 20

int main(int argc, char* argv[]) {
    (void)argc;
    (void)argv;
    long mappings[7][50][3] = {{{0}}};
    long seeds[NUM_SEEDS] = {0};
    long lowest = LONG_MAX;
    FILE* in = fopen("input", "r");
    char* line = NULL;
    size_t len = 0;
    int curMapping = -1;
    ssize_t charsRead = 0;
    int mapIdx = 0;
    {
        getline(&line, &len, in);
        char* num = strtok(line + 7, " ");
        for (int i = 0; num != NULL; i++, num = strtok(NULL, " "))
            seeds[i] = strtol(num, NULL, 10);
    }
    while ((charsRead = getline(&line, &len, in)) != -1) {
        if (charsRead < 2) continue;
        if (line[charsRead - 2] == ':') {
            curMapping++;
            mapIdx = 0;
            continue;
        }
        char* num = strtok(line, " ");
        for (int i = 0; num != NULL; i++, num = strtok(NULL, " "))
            mappings[curMapping][mapIdx][i] = strtol(num, NULL, 10);
        mapIdx++;
    }
    fclose(in);
    if (line) free(line);
    for (int i = 0; i < NUM_SEEDS; i += 2) {
        long start = seeds[i];
        for (long l = 0; l < seeds[i+1]; l++) {
            long src = start + l;
            for (int j = 0; j < 7; j++) {
                long dest = src;
                for (int k = 0; k < 50; k++) {
                    long* map = mappings[j][k];
                    if (map[2] == 0) break;
                    if (src >= map[1] && src < map[1] + map[2]) {
                        long offset = src - map[1];
                        dest = map[0] + offset;
                        break;
                    }
                }
                src = dest;
            }
            if (src < lowest) lowest = src;
        }
    }
    printf("Lowest: %ld\n", lowest);
}
