#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define HEIGHT (140)
#define WIDTH (140)

typedef struct point {
    int x;
    int y;
} point;

enum direction{NORTH, SOUTH, EAST, WEST};

bool stringContainsChar(char* str, int len, char c) {
    for (int i = 0; i < len; i++) {
        if (str[i] == c)
            return true;
    }
    return false;
}

/*
 * (0,0) is top left, x increases going to the right, y increases going down
 */
enum direction move(char pipe, enum direction dir) {
    switch (pipe) {
        case '|':
            if (dir == SOUTH)
                return SOUTH;
            else
                return NORTH;
        case '-':
            if (dir == EAST)
                return EAST;
            else
                return WEST;
        case 'L':
            if (dir == SOUTH)
                return EAST;
            else
                return NORTH;
        case 'J':
            if (dir == SOUTH)
                return WEST;
            else
                return NORTH;
        case '7':
            if (dir == NORTH)
                return WEST;
            else
                return SOUTH;
        case 'F':
            if (dir == NORTH)
                return EAST;
            else
                return SOUTH;
    }
    return SOUTH;
}

point getOffset(enum direction dir) {
    switch (dir) {
        case NORTH:
            return (point){ .y = -1 };
        case SOUTH:
            return (point){ .y = 1 };
        case EAST:
            return (point){ .x = 1 };
        case WEST:
            return (point){ .x = -1 };
    }
}

int main(int argc, char* argv[]) {
    (void)argc;
    (void)argv;
    FILE* in = fopen("input", "r");
    char* line = NULL;
    size_t lineLen = 0;
    char grid[HEIGHT][WIDTH] = {{0}};
    int row = 0;
    while (getline(&line, &lineLen, in) != -1)
        strncpy(grid[row++], line, WIDTH);
    fclose(in);
    if (line) free(line);
    line = NULL;

    point start = {0};
    for (int row = 0; row < HEIGHT; row++) {
        for (int col = 0; col < WIDTH; col++) {
            if (grid[row][col] == 'S') {
                start.y = row;
                start.x = col;
                goto foundStart;
            }
        }
    }
foundStart:
    point cur = start;
    enum direction toMove;
    if (cur.y >= 1 && stringContainsChar("|7F", 3, grid[cur.y-1][cur.x])) {
        cur.y--;
        toMove = NORTH;
    } else if (cur.y < HEIGHT-1 && stringContainsChar("|LJ", 3, grid[cur.y+1][cur.x])) {
        cur.y++;
        toMove = SOUTH;
    } else {
        cur.x++;
        toMove = EAST;
    }
    int len = 1;
    while (cur.x != start.x || cur.y != start.y) {
        len++;
        toMove = move(grid[cur.y][cur.x], toMove);
        point offset = getOffset(toMove);
        cur.x += offset.x;
        cur.y += offset.y;
    }
    printf("Furthest distance: %d\n", len / 2);
    return EXIT_SUCCESS;
}
