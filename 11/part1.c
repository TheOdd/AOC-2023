#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define WIDTH (140)
#define HEIGHT (140)

typedef struct point {
    int x;
    int y;
} point;

int main(int argc, char* argv[]) {
    (void)argc;
    (void)argv;
    FILE* in = fopen("input", "r");
    size_t len = 0;
    char* line = NULL;
    bool emptyRows[HEIGHT] = {0};
    bool emptyCols[WIDTH] = {0};
    char grid[HEIGHT][WIDTH] = {{0}};
    int row = 0;
    int numGalaxies = 0;
    while (getline(&line, &len, in) != -1) {
        strncpy(grid[row], line, WIDTH);
        bool isEmpty = true;
        for (int i = 0; i < WIDTH; i++) {
            if (line[i] != '.') {
                isEmpty = false;
                numGalaxies++;
            }
        }
        if (isEmpty)
            emptyRows[row] = true;
        row++;
    }
    if (line) free(line);
    line = NULL;
    fclose(in);
    for (int col = 0; col < WIDTH; col++) {
        bool isEmpty = true;
        for (int row = 0; row < HEIGHT; row++) {
            if (grid[row][col] != '.') {
                isEmpty = false;
                break;
            }
        }
        if (isEmpty)
            emptyCols[col] = true;
    }
    point* galaxies = calloc(numGalaxies, sizeof(point));
    int galaxyLen = 0;
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            if (grid[i][j] == '#') {
                galaxies[galaxyLen].x = j;
                galaxies[galaxyLen].y = i;
                galaxyLen++;
            }
        }
    }
    bool **pointSeen = malloc(numGalaxies * sizeof(*pointSeen));
    for (int i = 0; i < numGalaxies; i++)
        pointSeen[i] = calloc(numGalaxies, sizeof(*pointSeen[i]));
    int res = 0;
    for (int i = 0; i < numGalaxies; i++) {
        for (int j = 0; j < numGalaxies; j++) {
            if (i == j || pointSeen[i][j])
                continue;
            point a = galaxies[i];
            point b = galaxies[j];
            int diffX = a.x - b.x;
            int diffY = a.y - b.y;
            diffX = diffX < 0 ? -diffX : diffX;
            diffY = diffY < 0 ? -diffY : diffY;
            int start = a.x < b.x ? a.x : b.x;
            int end = a.x > b.x ? a.x : b.x;
            for (int k = start; k <= end; k++) {
                if (emptyCols[k])
                    diffX += 1;
            }
            start = a.y < b.y ? a.y : b.y;
            end = a.y > b.y ? a.y : b.y;
            for (int k = start; k <= end; k++) {
                if (emptyRows[k])
                    diffY += 1;
            }
            res += diffX + diffY;
            pointSeen[i][j] = true;
            pointSeen[j][i] = true;
        }
    }
    printf("Sum: %d\n", res);
    for (int i = 0; i < numGalaxies; i++)
        free(pointSeen[i]);
    free(pointSeen);
    pointSeen = NULL;
    free(galaxies);
    galaxies = NULL;
    return EXIT_SUCCESS;
}
