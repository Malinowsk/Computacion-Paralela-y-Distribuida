#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <stdbool.h>
#include <time.h>

#define RAND_MAX 10
#define N 5

int**generateMatrix(int n, bool is_out);
void showMatrix(int**matrix , int n);
int** multMatrix(int**matrix_A , int**matrix_B , int n);


int main(int argc , char*argv[]){
    srand(time(NULL));
    int**matrix_A = generateMatrix(N,0); //declaracion e inicialización de matriz A
    int**matrix_B = generateMatrix(N,0); //declaracion e inicialización de matriz B
    int**matrix_Out = generateMatrix(N,1); //declaracion de matriz salida
    showMatrix(matrix_A , N);  //imprimir matriz A

    showMatrix(matrix_B , N);  //imprimir matriz B

    matrix_Out = multMatrix(matrix_A , matrix_B , N);

    showMatrix(matrix_Out , N);

    return 0;

}

void showMatrix(int**matrix , int n){

   for (int i = 0 ; i < n ; i++){
     for(int j = 0 ; j < n ; j++)
        printf("%i  ",matrix[i][j]);
     printf("\n");
   }
   printf("\n");

}

int*generateRow(int n, bool is_out){

  int*row = (int*)malloc(n*sizeof(int));
  if(!is_out){
    for(int i = 0 ; i < n ; i++)
      row[i] = rand()%RAND_MAX;//Luego ver de agregar un random
  }
  return row;
}

int**generateMatrix(int n,bool is_out){

  int ** matrix= (int**)malloc(n*sizeof(int*));
  for(int i = 0 ; i < n ; i++) {
     matrix[i]= generateRow(n,is_out);
  }
  return matrix;
}


int** multMatrix(int**matrix_A , int**matrix_B ,  int n){

    int**matrix_Out = generateMatrix(N,1);
    for (int a = 0; a < n; a++) {
    // Dentro recorremos las filas de la primera (A)
        for (int i = 0; i < n; i++) {
            int adder = 0;
            // Y cada columna de la primera (A)
                for (int j = 0; j < n; j++) {
                // Multiplicamos y sumamos resultado
                    adder += matrix_A[i][j] * matrix_B[j][a];
                }
            // Lo acomodamos dentro del producto
            matrix_Out[i][a] = adder;
        }
    }
    return matrix_Out;
}

