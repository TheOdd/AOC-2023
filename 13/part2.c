#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

int patternResult(char** grid, int width, int height, int oldRes) {
    // Check for vertical reflection line
    for (int col = 1; col < width; col++) {
        // col represents the index to the RIGHT of the reflection line
        int leftSpots = col;
        int rightSpots = width - leftSpots;
        int range = leftSpots < rightSpots ? leftSpots : rightSpots;
        bool isReflection = true;
        for (int i = 0; i < range; i++) {
            for (int j = 0; j < height; j++) {
                char l = grid[j][col - 1 - i];
                char r = grid[j][col + i];
                if (l != r) {
                    isReflection = false;
                    goto doneCheckingVertical;
                }
            }
        }
doneCheckingVertical:
        if (isReflection && leftSpots != oldRes)
            return leftSpots;
    }

    // Check for horizontal reflection line
    for (int row = 1; row < height; row++) {
        // row represents the index BELOW the reflection line
        int upSpots = row;
        int downSpots = height - upSpots;
        int range = upSpots < downSpots ? upSpots : downSpots;
        bool isReflection = true;
        for (int i = 0; i < range; i++) {
            for (int j = 0; j < width; j++) {
                char u = grid[row - 1 - i][j];
                char d = grid[row + i][j];
                if (u != d) {
                    isReflection = false;
                    goto doneCheckingHorizontal;
                }
            }
        }
doneCheckingHorizontal:
        if (isReflection && (100*upSpots) != oldRes)
            return 100 * upSpots;
    }

    return 0;
}

int resolveSmudge(char** grid, int width, int height) {
    int result; 
    int oldRes = patternResult(grid, width, height, -1);
    int pos = 0;
    do {
        int row = pos / width;
        if (row >= height)
            return 0;
        int col = pos % width;
        grid[row][col] = grid[row][col] == '.' ? '#' : '.';
        result = patternResult(grid, width, height, oldRes);
        grid[row][col] = grid[row][col] == '.' ? '#' : '.';
        pos++;
    } while (!result);
    return result;
}

int main(int argc, char* argv[]) {
    (void)argc;
    (void)argv;
    FILE* in = fopen("input", "r");
    size_t len = 0;
    char* line = NULL;
    int result = 0;
    bool startingNewGrid = true;
    int curWidth = 0;
    int curHeight = 0;
    char** curGrid = NULL;
    while (getline(&line, &len, in) != -1) {
        if (line[0] == '\n') {
            // Process current grid
            result += resolveSmudge(curGrid, curWidth, curHeight);

            // Reset for next iteration
            for (int i = 0; i < curHeight; i++)
                free(curGrid[i]);
            if (curGrid) free(curGrid);
            curGrid = NULL;
            curWidth = curHeight = 0;
            startingNewGrid = true;
            continue;
        }

        if (startingNewGrid) {
            // Initialize width
            curWidth = strlen(line) - 1;
            startingNewGrid = false;
        }

        // Copy current line
        curGrid = realloc(curGrid, ++curHeight * sizeof(*curGrid));
        curGrid[curHeight-1] = calloc(curWidth, sizeof(*curGrid[curHeight-1]));
        strncpy(curGrid[curHeight-1], line, curWidth);
    }
    printf("%d\n", result);
    if (line) free(line);
    line = NULL;
    fclose(in);
    return EXIT_SUCCESS;
}
