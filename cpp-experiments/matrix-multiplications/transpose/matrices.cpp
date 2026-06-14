#include <stdio.h>

void transpose(const float *B, float *B_T, int K, int N)
{
    for (int k = 0; k < K; k++)
    {
        for (int n = 0; n < N; n++)
        {
            B_T[n * K + k] = B[k * N + n];
        }
    }
}

void matmul_naive(const float *A, const float *B, float *C, int M, int K, int N)
{
    for (int i = 0; i < M * N; ++i)
        C[i] = 0.0f;
    for (int i = 0; i < M; ++i)
        for (int j = 0; j < N; ++j)
            for (int k = 0; k < K; ++k)
                C[i * N + j] += A[i * K + k] * B[k * N + j];
}


void matmul_transpose(const float *A, const float *B, float *C, int M, int K, int N)
{
    if (!A || !B || !C)
        return;

    // allocate and compute B_T
    float *B_T = new float[N * K];
    transpose(B, B_T, K, N);

    // zero output
    for (int i = 0; i < M * N; ++i)
        C[i] = 0.0f;

    for (int i = 0; i < M; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            for (int k = 0; k < K; ++k)
            {
                C[i * N + j] += A[i * K + k] * B_T[j * K + k]; // both sequential ✅
            }
        }
    }

    delete[] B_T;
}