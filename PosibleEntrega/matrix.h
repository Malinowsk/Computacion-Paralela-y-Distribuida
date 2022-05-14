#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>  // para usar el system

void matrix(int size_matrix,int option);
int**generateMatrix(int n, bool is_out);
void showMatrix(int**matrix , int n);
double pickerMatrix(int num, int p , int size_matrix , int**matrix_A , int**matrix_B);
double multMatrix(int**matrix_A , int**matrix_B , int p , int size_matrix);
double multMatrixr(int**matrix_A , int**matrix_B , int p , int size_matrix);
double multMatrixnrc(int**matrix_A , int**matrix_B , int p , int size_matrix);
double multMatrixnra(int**matrix_A , int**matrix_B , int p , int size_matrix);
double multMatrixrD(int**matrix_A , int**matrix_B , int p , int size_matrix);


