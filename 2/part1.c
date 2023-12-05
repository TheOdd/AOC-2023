#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    (void)argc;
    (void)argv;
    FILE* in = fopen("input", "r");
    int sum = 0;
    char* line = NULL;
    size_t len = 0;
    int id = 1;
    while (getline(&line, &len, in) != -1) {
        char* lp = line + 8;
        while (*lp < '0' || *lp > '9') lp++;
        char* drawState;
        char* draw = strtok_r(lp, ";", &drawState);
        while (draw != NULL) {
            if (*draw == ' ') draw++;
            char* colorState;
            char* color = strtok_r(draw, ",", &colorState);
            while (color != NULL) {
                if (*color == ' ') color++;
                int num = 0;
                while (*color != ' ') {
                    num *= 10;
                    num += *color - '0';
                    color++;
                }
                color++;
                switch (*color) {
                    case 'r':
                        if (num > 12) goto next_line;
                        break;
                    case 'g':
                        if (num > 13) goto next_line;
                        break;
                    case 'b':
                        if (num > 14) goto next_line;
                        break;
                }
                color = strtok_r(NULL, ",", &colorState);
            }
            draw = strtok_r(NULL, ";", &drawState);
        }
        sum += id;
next_line:
        id++;
    }
    fclose(in);
    if (line)
        free(line);
    printf("Sum: %d\n", sum);
}
