#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>  // para usar el system

//principal
void matrix(int size_matrix,int option);

//imprimir,crear matriz, multiplicar matrices
void showMatrix(int**matrix , int n);
int**generateMatrix(int n, bool is_out);
double multMatrix(int**matrix_A , int**matrix_B , int p , int size_matrix); 

//selector
double pickerMatrix(int num, int p , int size_matrix , int**matrix_A , int**matrix_B);

//sin reduction
double multMatrixnra(int**matrix_A , int**matrix_B , int p , int size_matrix); 
double multMatrixnrc(int**matrix_A , int**matrix_B , int p , int size_matrix);

//reduction
double multMatrixr(int**matrix_A , int**matrix_B , int p , int size_matrix);
double multMatrixrS(int**matrix_A , int**matrix_B , int p , int size_matrix ,  int percen );
double multMatrixrD(int**matrix_A , int**matrix_B , int p , int size_matrix ,  int percen );
double multMatrixrG(int**matrix_A , int**matrix_B , int p , int size_matrix, int percen );
