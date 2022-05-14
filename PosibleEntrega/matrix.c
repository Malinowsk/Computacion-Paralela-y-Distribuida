#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <stdbool.h>
#include <unistd.h>  //  Para usar el sleep
#include <time.h>
#include "matrix.h"
#include "metrics.h"

#define RAND_MATRIX 10
#define N 8 //La cantidad de muestras(tiempos)


void matrix(int size_matrix , int option){

    srand(time(NULL));
    double*nums = (double*)malloc(N*sizeof(double)); //Se genera la estructura donde se va a guardar los tiempos
    double*promedios = (double*)malloc(omp_get_num_procs()*sizeof(double));
    int**matrix_A = generateMatrix(size_matrix,0); //declaracion e inicialización de matriz A
    int**matrix_B = generateMatrix(size_matrix,0); //declaracion e inicialización de matriz B

    printf("\nCon un tamaño de matriz de %ld , se obtiene: \n\n" , size_matrix);

    
    for(int i = 0 ; i < omp_get_num_procs() ; i++){
      sleep(4);  
      printf("\nUsando %d procesador/es: \n\n", (i+1));
      for(int j = 0 ; j < N ; j++)
        nums[j] = pickerMatrix(option,i+1,size_matrix,matrix_A,matrix_B);
    
    printf("\n");
    double avg = getAverage(nums,N); 
    //printf("El promedio de los tiempos es de: %lf\n\n", avg);
    promedios[i]=avg;

    printf("El desvio estandar de los tiempos es de: %f\n ", getStdDeviation(nums,avg,N));
    
    
    }

  	for(int i = 0 ; i < omp_get_num_procs() ; i++)
       printf("Promedio de tiempo con %d procesador: %lf segundos\n\n", (i+1), promedios[i]);

  
	  printf("Continuar");
	  sleep(2);
	  getchar();

}

double pickerMatrix(int num, int p , int size_matrix , int**matrix_A , int**matrix_B){
     
     switch (num)
                {
                case 1:
                    return multMatrixnra(matrix_A,matrix_B,p,size_matrix);
                    break;
                case 2:
                    return multMatrixr(matrix_A,matrix_B,p,size_matrix);
                    break;
                case 3:
                    return multMatrixr(matrix_A,matrix_B,p,size_matrix);
                    break;
                case 4:
                    return multMatrixrD(matrix_A,matrix_B,p,size_matrix);
                    break;
                default:
                    return 1.00;
                }
         return 1.00;
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
      row[i] = rand()%RAND_MATRIX;//Luego ver de agregar un random
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





double multMatrix(int**matrix_A , int**matrix_B , int p, int size_matrix){

  double time_start= omp_get_wtime();
  omp_set_num_threads(p);
  int**matrix_Out = generateMatrix(N,1); //declaracion de matriz salida

  //Estas impresiones, junto con la de pi que no está agregada, discutir si mostrar o no
  printf("Matriz A :\n");
  showMatrix(matrix_A , N);  //imprimir matriz A
  printf("Matriz A :\n");
  showMatrix(matrix_B , N);  //imprimir matriz B

  //Aquí se va a ejecutar el código de la multiplicación

  /*for (int a = 0; a < n; a++) {
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
  }*/

  double time_end= omp_get_wtime();
  printf("La matriz de salida es :\n");
  showMatrix(matrix_Out , N);

  double total_time = time_end-time_start ; //Calcula el tiempo total de la diferencia entre el tiempo final y el inicial
  printf("\n Secuencial %lf \n",total_time);

  return total_time;
}


 double multMatrixr(int**matrix_A , int**matrix_B , int p, int size_matrix){
    double time_start= omp_get_wtime();
    omp_set_num_threads(p);
    int**matrix_Out = generateMatrix(N,1); //declaracion de matriz salida

    //Estas impresiones, junto con la de pi que no está agregada, discutir si mostrar o no
    printf("Matriz A :\n");
    showMatrix(matrix_A , N);  //imprimir matriz A
    printf("Matriz A :\n");
    showMatrix(matrix_B , N);  //imprimir matriz B

    //Aquí se va a ejecutar el código de la multiplicación

    /*pragma omp parallel for
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
    */
    double time_end= omp_get_wtime();
    printf("La matriz de salida es :\n");
    showMatrix(matrix_Out , N);

    double total_time = time_end-time_start ; //Calcula el tiempo total de la diferencia entre el tiempo final y el inicial
    printf("\n Reduction %lf \n",total_time);
  
    return total_time;
  
}


double multMatrixnra(int**matrix_A , int**matrix_B , int p, int size_matrix){
    double time_start= omp_get_wtime();
    omp_set_num_threads(p);
    int**matrix_Out = generateMatrix(N,1); //declaracion de matriz salida

    //Estas impresiones, junto con la de pi que no está agregada, discutir si mostrar o no
    printf("Matriz A :\n");
    showMatrix(matrix_A , N);  //imprimir matriz A
    printf("Matriz A :\n");
    showMatrix(matrix_B , N);  //imprimir matriz B

    //Aquí se va a ejecutar el código de la multiplicación

    /*
    */

    double time_end= omp_get_wtime();
    printf("La matriz de salida es :\n");
    showMatrix(matrix_Out , N);

    double total_time = time_end-time_start ; //Calcula el tiempo total de la diferencia entre el tiempo final y el inicial
    printf("\n No Reduction Atomic%lf \n",total_time);
  
    return total_time;

  }

double multMatrixnrc(int**matrix_A , int**matrix_B , int p, int size_matrix){
    double time_start= omp_get_wtime();
    omp_set_num_threads(p);
    int**matrix_Out = generateMatrix(N,1); //declaracion de matriz salida

    //Estas impresiones, junto con la de pi que no está agregada, discutir si mostrar o no
    printf("Matriz A :\n");
    showMatrix(matrix_A , N);  //imprimir matriz A
    printf("Matriz A :\n");
    showMatrix(matrix_B , N);  //imprimir matriz B

    //Aquí se va a ejecutar el código de la multiplicación

    /*
    */

    double time_end= omp_get_wtime();
    printf("La matriz de salida es :\n");
    showMatrix(matrix_Out , N);

    double total_time = time_end-time_start ; //Calcula el tiempo total de la diferencia entre el tiempo final y el inicial
    printf("\n No Reduction Critical%lf \n",total_time);
  
    return total_time;

  }

double multMatrixrD(int**matrix_A , int**matrix_B , int p, int size_matrix){
    double time_start= omp_get_wtime();
    omp_set_num_threads(p);
    int**matrix_Out = generateMatrix(N,1); //declaracion de matriz salida

    //Estas impresiones, junto con la de pi que no está agregada, discutir si mostrar o no
    printf("Matriz A :\n");
    showMatrix(matrix_A , N);  //imprimir matriz A
    printf("Matriz A :\n");
    showMatrix(matrix_B , N);  //imprimir matriz B

    //Aquí se va a ejecutar el código de la multiplicación

    /*
    */

    double time_end= omp_get_wtime();
    printf("La matriz de salida es :\n");
    showMatrix(matrix_Out , N);

    double total_time = time_end-time_start ; //Calcula el tiempo total de la diferencia entre el tiempo final y el inicial
    printf("\n Reduction Dynamic%lf \n",total_time);
  
    return total_time;

  }  