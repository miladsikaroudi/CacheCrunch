#pragma once


void transpose(const float* A, float* A_T, int K, int N);
/// @brief 
/// @param A : first matrix
/// @param B : second matrix
/// @param C : the result
/// @param M : #of rows of A
/// @param K : #of cols of A and rows of B
/// @param N : #of cols of B
void matmul_transpose(const float* A, const float* B, float* C, int M, int K, int N);


