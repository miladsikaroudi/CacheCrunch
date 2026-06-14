#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "cpp-experiments/matrix-multiplications/transpose/matrices.h"
#include "cpp-experiments/softmax/simple/softmax.h"

bool matrices_equal(float * A, float* B, int size, float tol=1e-4){
    for (int i; i<size; ++i){
        if (fabsf(A[i]-B[i])>tol){
            return false;
        }
    }
    return true;
}

void fill_random(float* A, int size){

    if (!A){
        return;
    }
    for (int i; i<size; ++i){
        A[i] = (float)rand() / RAND_MAX;

    }
}

void test_transpose()
{
    printf("=== TEST: transpose ===\n");
    float B[] = {7, 8, 9, 10, 11, 12};
    float B_T[6] = {0};
    float expected[] = {7, 9, 11, 8, 10, 12};
    transpose(B, B_T, 3, 2);
    printf("  %s\n\n", matrices_equal(B_T, expected, 6) ? "PASS" : "FAIL");
}

void test_correctness()
{
    printf("=== TEST: naive vs transpose correctness ===\n");
    float A[] = {1, 2, 3, 4, 5, 6};
    float B[] = {7, 8, 9, 10, 11, 12};
    float C_naive[4] = {0};
    float C_trans[4] = {0};
    float expected[] = {58, 64, 139, 154};
    matmul_transpose(A, B, C_trans, 2, 3, 2);
    printf("  naive:     %s\n", matrices_equal(C_naive, expected, 4) ? "PASS" : "FAIL");
    printf("  transpose: %s\n\n", matrices_equal(C_trans, expected, 4) ? "PASS" : "FAIL");
}

void test_large()
{
    printf("=== TEST: 512x512 naive vs transpose ===\n");
    const int M = 512, K = 512, N = 512;
    float *A = new float[M * K];
    float *B = new float[K * N];
    float *C_naive = new float[M * N];
    float *C_trans = new float[M * N];
    srand(42);
    fill_random(A, M * K);
    fill_random(B, K * N);
    matmul_transpose(A, B, C_trans, M, K, N);
    delete[] A;
    delete[] B;
    delete[] C_naive;
    delete[] C_trans;
}

void test_softmax(){
    int size = 5;
    float input[] = {1,2,3,4,5};
    float* output = new float[size];
    softmax(input, output, size);

    float sum = 0;
    for (int i=0; i<size; ++i) {sum += output[i];}
    printf("\n");
    printf("Sum %.6f (should be ~1.0): %s\n", sum, fabsf(sum - 1.0f) <1e-4 ? "PASS": "FAIL");

    bool monotonic = true;
    for (int i=1; i<size; ++i){
        if (output[i]<output[i-1]) monotonic = false;
    }
    printf("Monotonic increasing : %s\n", monotonic ? "PASS": "FAIL");

    delete [] output;

}


int main(){

    printf("⡒·············⢲");
    test_transpose();
    // test_correctness();
    test_large();
    test_softmax();
    printf("Done. \n");
    return 0;
}