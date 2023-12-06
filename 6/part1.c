#include <stdio.h>
#include <math.h>

#define LEN 4

int main(int argc, char* argv[]) {
    (void)argc;
    (void)argv;
    int times[] = {53, 91, 67, 68};
    int distances[] = {250, 1330, 1081, 1025};
    unsigned long long product = 1;
    for (int i = 0; i < LEN; i++) {
        int n = times[i];
        int m = distances[i];
        double a = sqrt(n*n - 4*m);
        a = n - a;
        a /= 2;
        int b = a + 1;
        product *= n - 2*b + 1;
    }
    printf("Product: %llu\n", product);
}
