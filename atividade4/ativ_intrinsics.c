#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <x86intrin.h>
#include <string.h>

#define N 1000000
#define M 3000

void convolve_avx(float* in, float* kernel, float* out) {
	float* in_padded = (float*)(alloca(sizeof(float) * (N + 16)));

	__m256* kernel_many = (__m256*)(alloca(sizeof(__m256) * M));

	__m256 block;
	__m256 prod;
	__m256 acc;

	int i;
	for (i = 0; i < M; i++) {
		kernel_many[i] = _mm256_broadcast_ss(&kernel[i]);
	}

	block = _mm256_setzero_ps();
	_mm256_storeu_ps(in_padded, block);
	memcpy(&(in_padded[8]), in, N * sizeof(float));
	_mm256_storeu_ps(in_padded + N + 8, block);

	for (i = 0; i < N + M - 8; i += 8) {
		acc = _mm256_setzero_ps();

		int startk = i >(N - 1) ? i - (N - 1) : 0;
		int endk = (i + 7) < M ? (i + 7) : M - 1;

		int k = startk;

		for (; k + 3 <= endk; k += 4) {
			block = _mm256_loadu_ps(in_padded + 8 + i - k);
			prod = _mm256_mul_ps(block, kernel_many[k]);
			acc = _mm256_add_ps(acc, prod);

			block = _mm256_loadu_ps(in_padded + 7 + i - k);
			prod = _mm256_mul_ps(block, kernel_many[k + 1]);
			acc = _mm256_add_ps(acc, prod);

			block = _mm256_loadu_ps(in_padded + 6 + i - k);
			prod = _mm256_mul_ps(block, kernel_many[k + 2]);
			acc = _mm256_add_ps(acc, prod);

			block = _mm256_loadu_ps(in_padded + 5 + i - k);
			prod = _mm256_mul_ps(block, kernel_many[k + 3]);
			acc = _mm256_add_ps(acc, prod);
		}

		for (; k <= endk; k++) {
			block = _mm256_loadu_ps(in_padded + 8 + i - k);
			prod = _mm256_mul_ps(block, kernel_many[k]);
			acc = _mm256_add_ps(acc, prod);
		}

		_mm256_storeu_ps(out + i, acc);
	}

	for (; i < N + M - 1; i++) {
		out[i] = 0.0;
		int startk = i >= N ? i - N + 1 : 0;
		int endk = i < M ? i : M - 1;
		for (int k = startk; k <= endk; k++) {
			out[i] += in[i - k] * kernel[k];
		}
	}
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
    convolve_avx(a, b, c);
    clock_t end = clock();

    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Time spent: %f\n", time_spent);

    // print_array(c, N + M -1);

    free(a);
    free(b);
    free(c);
}