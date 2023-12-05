#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define WIDTH 140
#define HEIGHT 140

int getNum(char* target, int col, bool hasNum[3], int hasNumColStart);

int main(int argc, char* argv[]) {
    (void)argc;
    (void)argv;
    FILE* in = fopen("input", "r");
    int sum = 0;
    char* line = NULL;
    size_t len = 0;
    char schematic[HEIGHT][WIDTH];
    int row = 0;
    while (getline(&line, &len, in) != -1) {
        for (int col = 0; col < WIDTH; col++)
            schematic[row][col] = line[col];
        row++;
    }
    if (line)
        free(line);
    fclose(in);
    for (row = 0; row < HEIGHT; row++) {
        for (int col = 0; col < WIDTH; col++) {
            char c = schematic[row][col];
            if (c != '*') continue;
            int nums[2] = {-1, -1};
            int numsCount = 0;
            bool hasNum[3][3] = {{0}};
            for (int rOffset = -1; rOffset <= 1; rOffset++) {
                for (int cOffset = -1; cOffset <= 1; cOffset++) {
                    if (hasNum[rOffset + 1][cOffset + 1]) continue;
                    int curRow = row + rOffset;
                    int curCol = col + cOffset;
                    char curChar = schematic[curRow][curCol];
                    if (curChar < '0' || curChar > '9') continue;
                    if (numsCount == 2) goto next_char;
                    int n = getNum(schematic[curRow], curCol, hasNum[rOffset + 1], col - 1);
                    nums[numsCount++] = n;
                }
            }
            if (numsCount == 2)
                sum += nums[0] * nums[1];
next_char:
            continue;
        }
    }
    printf("Sum: %d\n", sum);
}

int getNum(char* line, int col, bool hasNum[3], int hasNumColStart) {
    int numColStart = col;
    for (; numColStart >= 0; numColStart--) {
        char ch = *(line + numColStart);
        if (ch < '0' || ch > '9') break;
    }
    numColStart++;
    char* end = NULL;
    int num = strtol(line + numColStart, &end, 10);
    int len = *end == '\0' ? WIDTH - numColStart : end - (line + numColStart);
    int i = numColStart <= hasNumColStart ? hasNumColStart : numColStart;
    for (; i < (numColStart + len); i++) {
        if (i > hasNumColStart + 2) break;
        hasNum[i - hasNumColStart] = true;
    }
    return num;
}
