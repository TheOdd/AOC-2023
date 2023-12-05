#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define WIDTH 140
#define HEIGHT 140

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
            if (c < '0' || c > '9') continue;
            char* start = &schematic[row][col];
            char* end = NULL;
            int num = strtol(start, &end, 10);
            int len = *end == '\0' ? WIDTH - col : end - &schematic[row][col];
            bool isNextToSymbol = false;
            for (int i = 0; i < len; i++) {
                int curCol = col + i;
                for (int r = row - 1; r <= row + 1; r++) {
                    if (r < 0) continue;
                    if (r >= HEIGHT) break;
                    for (int c = curCol - 1; c <= curCol + 1; c++) {
                        if (c < 0) continue;
                        if (c >= WIDTH) break;
                        char ch = schematic[r][c];
                        if ((ch < '0' || ch > '9') && ch != '.') {
                            isNextToSymbol = true;
                            goto after_adjacent_check;
                        }
                    }
                }
            }
after_adjacent_check:
            if (isNextToSymbol) sum += num;
            col += (len - 1);
        }
    }
    printf("Sum: %d\n", sum);
}
