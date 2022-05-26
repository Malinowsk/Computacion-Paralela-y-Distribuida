#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>  // para usar el system

void matrix(int size_matrix,int option);
int**generateMatrix(int n, bool is_out);
void showMatrix(int**matrix , int n);
double pickerMatrix(int num, int p , int size_matrix , int**matrix_A , int**matrix_B);
double multMatrix(int**matrix_A , int**matrix_B , int p , int size_matrix); //Funciona
double multMatrixnra(int**matrix_A , int**matrix_B , int p , int size_matrix); //Funciona. Era el atomic 3, que fue el mejor
double multMatrixr(int**matrix_A , int**matrix_B , int p , int size_matrix);
double multMatrixnrc(int**matrix_A , int**matrix_B , int p , int size_matrix); //Funciona pero es muy lento
double multMatrixrS(int**matrix_A , int**matrix_B , int p , int size_matrix ,  int percen );
double multMatrixrD(int**matrix_A , int**matrix_B , int p , int size_matrix ,  int percen );
double multMatrixrG(int**matrix_A , int**matrix_B , int p , int size_matrix, int percen );
