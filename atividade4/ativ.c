#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 1000000
#define M 3000

void convolve(float *a, float *b, float *c) {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            c[i + j] += a[i] * b[j];
}

void print_array(float *a, int size) {
    for (int i = 0; i < size; i++)
        printf("%.2lf ", a[i]);

    printf("\n");
}

int main() {
    float *a = malloc(N * sizeof(float));
    float *b = malloc(M * sizeof(float));
    float *c = calloc(N + M - 1, sizeof(float));

    for (int i = 0; i < N; i++)
        a[i] = rand() % 10;
    
    for (int i = 0; i < M; i++)
        b[i] = rand() % 10;
    
    // print_array(a, N);
    // print_array(b, M);

    clock_t start = clock();

    convolve(a, b, c);

    clock_t end = clock();

    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Time spent: %f\n", time_spent);

    // print_array(c, N + M -1);

    free(a);
    free(b);
    free(c);
}