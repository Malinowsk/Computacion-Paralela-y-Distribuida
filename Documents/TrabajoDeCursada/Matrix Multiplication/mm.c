#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <stdbool.h>
#include <time.h>

#define N 5
#define RAND_MAX 10

int**generateMatrix(int n, bool is_out);
void showMatrix(int**matrix , int n);
int** multMatrix(int**matrix_A , int**matrix_B , int n, int p);
void generadorMultiplicadorDeMatrix(int p);

int main(){

    generadorMultiplicadorDeMatrix(1);

    return 0;

}

void generadorMultiplicadorDeMatrix(int p){
    float tiempo_inicial= omp_get_wtime();
    //omp_set_num_threads(p);

    srand(time(NULL));
    int**matrix_A = generateMatrix(N,0); //declaracion e inicialización de matriz A
    int**matrix_B = generateMatrix(N,0); //declaracion e inicialización de matriz B
    int**matrix_Out = generateMatrix(N,1); //declaracion de matriz salida
    
    showMatrix(matrix_A , N);  //imprimir matriz A

    showMatrix(matrix_B , N);  //imprimir matriz B

    matrix_Out = multMatrix(matrix_A , matrix_B , N, p);

    showMatrix(matrix_Out , N);

    float tiempo_final= omp_get_wtime();
  
    printf(" %f \n",tiempo_final-tiempo_inicial);

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
      row[i] = rand()%10;//Luego ver de agregar un random
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


int** multMatrix(int**matrix_A , int**matrix_B ,  int n, int p){

    omp_set_num_threads(p);
  
    int**matrix_Out = generateMatrix(N,1);

    #pragma omp parallel for
    for (int a = 0; a < n; a++) {
      //#pragma omp parallel for
      for (int i = 0; i < n; i++) {
          int adder = 0;
              #pragma omp parallel for reduction(+:adder) 
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

/*
int** multMatrix(int**matrix_A , int**matrix_B ,  int n, int p){

  float tiempo_inicial= omp_get_wtime();
  omp_set_num_threads(p);

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

*/