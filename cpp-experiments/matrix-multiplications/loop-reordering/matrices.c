#include <stdio.h>
#include <stdlib.h>

#define N 1000 // A 1000x1000 matrix

// Naive i-j-k (Slow, causes cache misses)
void multiply_ijk(double *A, double *B, double *C)
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            double sum = 0;
            for (int k = 0; k < N; k++)
            {
                // Moving down the column of B (k * N)
                sum += A[i * N + k] * B[k * N + j];
            }
            C[i * N + j] = sum;
        }
    }
}

// Optimized i-k-j (Fast, utilizes L1/L2 cache)
void multiply_ikj(double *A, double *B, double *C)
{
    for (int i = 0; i < N; i++)
    {
        for (int k = 0; k < N; k++)
        {
            double r = A[i * N + k]; // Stored in a register
            for (int j = 0; j < N; j++)
            {
                // Moving across the row of B and C sequentially
                C[i * N + j] += r * B[k * N + j];
            }
        }
    }
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: %s <1 for i-j-k, 2 for i-k-j>\n", argv[0]);
        return 1;
    }

    int mode = atoi(argv[1]);
    size_t bytes = N * N * sizeof(double);

    // Allocate memory on the heap
    double *A = (double *)malloc(bytes);
    double *B = (double *)malloc(bytes);
    double *C = (double *)calloc(N * N, sizeof(double)); // calloc initializes to 0

    // Fill with dummy data
    for (int i = 0; i < N * N; i++)
    {
        A[i] = 1.0;
        B[i] = 2.0;
    }

    if (mode == 1)
    {
        printf("Running naive i-j-k...\n");
        multiply_ijk(A, B, C);
    }
    else if (mode == 2)
    {
        printf("Running optimized i-k-j...\n");
        multiply_ikj(A, B, C);
    }

    free(A);
    free(B);
    free(C);
    return 0;
}