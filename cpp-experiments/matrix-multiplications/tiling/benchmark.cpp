#include <stdio.h>
#include <stdlib.h>
#include "matrices.h"

#define N 1000

          void fill(float *M, int size, float val)
{
    for (int i = 0; i < size; ++i)
        M[i] = val;
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: %s <1=naive, 2=tiled>\n", argv[0]);
        return 1;
    }

    float *A = (float *)malloc(N * N * sizeof(float));
    float *B = (float *)malloc(N * N * sizeof(float));
    float *C = (float *)calloc(N * N, sizeof(float));

    fill(A, N * N, 1.0f);
    fill(B, N * N, 2.0f);

    int mode = atoi(argv[1]);
    if (mode == 1)
    {
        printf("Running naive...\n");
        matmul_naive(A, B, C, N, N, N);
    }
    else if (mode == 2)
    {
        printf("Running tiled...\n");
        matmul_tiled(A, B, C, N, N, N);
    }

    printf("C[0] = %f\n", C[0]);
    free(A);
    free(B);
    free(C);
    return 0;
}