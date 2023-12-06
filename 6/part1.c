#include <stdio.h>
#include <math.h>

#define LEN 4

int count(int n, int m) { return n - 2*(int)((n - sqrt(n*n - 4*m))/2) - 1; }

int main(int argc, char* argv[]) {
    (void)argc;
    (void)argv;
    int times[] = {53, 91, 67, 68};
    int distances[] = {250, 1330, 1081, 1025};
    int product = 1;
    for (int i = 0; i < LEN; i++)
        product *= count(times[i], distances[i]);
    printf("Product: %d\n", product);
}
