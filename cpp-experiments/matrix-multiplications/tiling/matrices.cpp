#include <stdio.h>
#include <stdlib.h>
#include <algorithm>

#define N 1000


constexpr int TILE_SIZE = 32;

void multiply_naive(float *A, float *B, float *C)
{
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
        {
            float sum = 0.0f;
            for (int k = 0; k < N; ++k)
                sum += A[i * N + k] * B[k * N + j];
            C[i * N + j] = sum;
        }
}

void multiply_tiled(float *A, float *B, float *C)
{
    for (int i = 0; i < N * N; ++i)
        C[i] = 0.0f;
    for (int m = 0; m < N; m += TILE_SIZE)
        for (int k = 0; k < N; k += TILE_SIZE)
            for (int n = 0; n < N; n += TILE_SIZE)
                for (int mm = m; mm < std::min(m + TILE_SIZE, N); ++mm)
                    for (int kk = k; kk < std::min(k + TILE_SIZE, N); ++kk)
                        for (int nn = n; nn < std::min(n + TILE_SIZE, N); ++nn)
                            C[mm * N + nn] += A[mm * N + kk] * B[kk * N + nn];
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: %s <1=naive, 2=tiled>\n", argv[0]);
        return 1;
    }

    size_t bytes = N * N * sizeof(float);
    float *A = (float *)malloc(bytes);
    float *B = (float *)malloc(bytes);
    float *C = (float *)calloc(N * N, sizeof(float));

    for (int i = 0; i < N * N; ++i)
    {
        A[i] = 1.0f;
        B[i] = 2.0f;
    }

    int mode = atoi(argv[1]);
    if (mode == 1)
    {
        printf("Running naive...\n");
        multiply_naive(A, B, C);
    }
    else if (mode == 2)
    {
        printf("Running tiled (TILE=%d)...\n", TILE_SIZE);
        multiply_tiled(A, B, C);
    }

    printf("C[0] = %f\n", C[0]);
    free(A);
    free(B);
    free(C);
    return 0;
}