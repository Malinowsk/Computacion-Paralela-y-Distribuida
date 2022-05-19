#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <stdbool.h>
#include <unistd.h>  //  Para usar el sleep
#include <time.h>
#include "matrix.h"
#include "metrics.h"

#define RAND_MATRIX 10
#define N 8 


void matrix(int size_matrix , int option){

  double*times_1 = (double*)malloc(N*sizeof(double)); //Se genera la estructura donde se va a guardar los tiempos usando atomic
  double*times_2 = (double*)malloc(N*sizeof(double)); //Se genera la estructura donde se va a guardar los tiempos usando critical
  double*times_p = (double*)malloc(N*sizeof(double)); //Se genera la estructura donde se va a guardar los tiempos usando critical

  double*promedio_1 = (double*)malloc(omp_get_num_procs()*sizeof(double));
  double*devioEstandar_1 = (double*)malloc(omp_get_num_procs()*sizeof(double));

  double*promedio_2 = (double*)malloc(omp_get_num_procs()*sizeof(double));
  double*devioEstandar_2 = (double*)malloc(omp_get_num_procs()*sizeof(double));

  int**matrix_A = generateMatrix(size_matrix,0); //declaracion e inicialización de matriz A
  int**matrix_B = generateMatrix(size_matrix,0); //declaracion e inicialización de matriz B

  printf("\n\t\tEjecución del algoritmo para el \e[38;2;128;0;255m \e[48;2;0;0;0mcalculo de mult de matrices con un tamaño n de %d \e[0m, se obtiene: \n\n" , size_matrix);

  printf("\n\e[38;2;0;255;0m \e[48;2;0;0;0m Algoritmo sin pragmas usando 1 procesador/es: \e[0m\n\n");
  
  for(int j = 0 ; j < N ; j++){
    times_p[j] = pickerMatrix(5,1,size_matrix,matrix_A,matrix_B); 
  }


  double avg_p = getAverage(times_p,N); 
  double sd_p = getStdDeviation(times_p,avg_p,N);
  printf(" El\e[38;2;0;0;255m \e[48;2;0;0;0m \e[3mdesvio estandar \e[0m sin pragma con 1 procesador: \e[38;2;0;0;255m \e[48;2;0;0;0m %lf \e[0m segundos\t\t", sd_p);
  printf("\e[38;5;196m \e[48;2;0;0;0m\e[3m Promedio \e[0m de tiempo sin pragma con 1 procesador: \e[38;5;196m \e[48;2;0;0;0m %lf \e[0m segundos\n\n", avg_p);
    
  for(int i = 1 ; i <= omp_get_num_procs() ; i++){
    sleep(4);  
    printf("\n\e[38;2;0;255;0m \e[48;2;0;0;0m Algoritmo con pragmas usando %d procesador/es: \e[0m\n\n", (i));
    for(int j = 0 ; j < N ; j++){
        times_1[j] = pickerMatrix(option,i,size_matrix,matrix_A,matrix_B);
        times_2[j] = pickerMatrix(option+2,i,size_matrix,matrix_A,matrix_B);
    }

    double avg_1 = getAverage(times_1,N); 
    double avg_2 = getAverage(times_2,N); 

    promedio_1[i]=avg_1;
    devioEstandar_1[i]=getStdDeviation(times_1,avg_1,N);

    promedio_2[i]=avg_2;
    devioEstandar_2[i]=getStdDeviation(times_2,avg_2,N);
    
    if(option==1){
    printf(" El\e[38;2;0;0;255m \e[48;2;0;0;0m \e[3mdesvio estandar \e[0m para el  atomic con %d procesador: \e[38;2;0;0;255m \e[48;2;0;0;0m %lf \e[0m segundos\t\t", (i), devioEstandar_1[i]);
    printf("\e[38;5;196m \e[48;2;0;0;0m\e[3m Promedio \e[0m de tiempo para el  atomic con %d procesador: \e[38;5;196m \e[48;2;0;0;0m %lf \e[0m segundos\n\n", (i), promedio_1[i]);
    printf(" El\e[38;2;0;0;255m \e[48;2;0;0;0m \e[3mdesvio estandar \e[0m para el critical con %d procesador:\e[38;2;0;0;255m \e[48;2;0;0;0m %lf \e[0m segundos\t\t", (i), devioEstandar_2[i]);
    printf("\e[38;5;196m \e[48;2;0;0;0m\e[3m Promedio \e[0m de tiempo para el critical con %d procesador:\e[38;5;196m \e[48;2;0;0;0m %lf \e[0m segundos\n\n", (i), promedio_2[i]);
    }
    else
    {
    printf(" El \e[38;2;0;0;255m\e[48;2;0;0;0m\e[3m desvio estandar \e[0m para el Reduction Normal con %d procesador: \e[38;2;0;0;255m \e[48;2;0;0;0m %lf \e[0m seg  ", (i), devioEstandar_1[i]);
    printf("\e[38;5;196m \e[48;2;0;0;0m\e[3m Promedio \e[0m de tiempo para el Rduction Normal con %d procesador:\e[38;5;196m \e[48;2;0;0;0m %lf \e[0m seg\n\n", (i), promedio_1[i]);
    printf(" El \e[38;2;0;0;255m\e[48;2;0;0;0m\e[3m desvio estandar \e[0m para Reduc con Plan Dinamica con %d procesador:\e[38;2;0;0;255m \e[48;2;0;0;0m %lf \e[0m seg  ", (i), devioEstandar_2[i]);
    printf("\e[38;5;196m \e[48;2;0;0;0m\e[3m Promedio \e[0m de tiempo para Reduc con Plan Dinamica con %d procesador:\e[38;5;196m \e[48;2;0;0;0m %lf \e[0m seg\n\n", (i), promedio_2[i]);
    }
    
  }

  printf("\n");

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
                    return multMatrixnrc(matrix_A,matrix_B,p,size_matrix);
                    break;
                case 4:
                    return multMatrixrD(matrix_A,matrix_B,p,size_matrix);
                    break;
                case 5:
                    return multMatrix(matrix_A,matrix_B,p,size_matrix);
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
  int**matrix_Out = generateMatrix(size_matrix,1); //declaracion de matriz salida

  for (int a = 0; a < size_matrix; a++) {
  // Dentro recorremos las filas de la primera (A)
      for (int i = 0; i < size_matrix; i++) {
          int adder = 0;
          // Y cada columna de la primera (A)
              for (int j = 0; j < size_matrix; j++) {
              // Multiplicamos y sumamos resultado
                  adder += matrix_A[i][j] * matrix_B[j][a];
              }
          // Lo acomodamos dentro del producto
          matrix_Out[i][a] = adder;
      }
  }

  double time_end= omp_get_wtime();
  //printf("La matriz de salida es :\n");
  /*showMatrix(matrix_Out , size_matrix);
  printf("\n\n");
  */    
  double total_time = time_end-time_start ; //Calcula el tiempo total de la diferencia entre el tiempo final y el inicial
  printf("\n\t \e[48;2;255;255;0m\e[38;5;196m\e[1m Secuencial sin pragma \e[0m \e[38;2;0;255;0m \e[48;2;0;0;0m %lf \e[0m seg \n",total_time);

  return total_time;
}


 double multMatrixr(int**matrix_A , int**matrix_B , int p, int size_matrix){
    double time_start= omp_get_wtime();
    omp_set_num_threads(p);
    int**matrix_Out = generateMatrix(size_matrix,1); //declaracion de matriz salida

    //Estas impresiones, junto con la de pi que no está agregada, discutir si mostrar o no
    /*printf("Matriz A :\n");
    showMatrix(matrix_A , size_matrix);  //imprimir matriz A
    printf("Matriz A :\n");
    showMatrix(matrix_B , size_matrix);  //imprimir matriz B
    */
    //Aquí se va a ejecutar el código de la multiplicación

    #pragma omp parallel for
        for (int a = 0; a < size_matrix; a++) {
          #pragma omp parallel for
              for (int i = 0; i < size_matrix; i++) {
                  int adder = 0;
                      #pragma omp parallel for reduction(+:adder) 
                          for (int j = 0; j < size_matrix; j++) {
                          // Multiplicamos y sumamos resultado
                              adder += matrix_A[i][j] * matrix_B[j][a];
                          }
                  // Lo acomodamos dentro del producto
                  matrix_Out[i][a] = adder;
              }
        }
    
    double time_end= omp_get_wtime();
    /*printf("La matriz de salida es :\n");
    showMatrix(matrix_Out , size_matrix);
    */
    double total_time = time_end-time_start ; //Calcula el tiempo total de la diferencia entre el tiempo final y el inicial
    printf("\n Reduction %lf \n",total_time);
  
    return total_time;
  
}


double multMatrixnra(int**matrix_A , int**matrix_B , int p, int size_matrix){
  
  double time_start= omp_get_wtime();
  omp_set_num_threads(p);
  int**matrix_Out = generateMatrix(size_matrix,1); //declaracion de matriz salida

  //Aquí se va a ejecutar el código de la multiplicación

  #pragma omp parallel for 
      for (int a = 0; a < size_matrix; a++) {
      // Dentro recorremos las filas de la primera (A)
        #pragma omp parallel for 
          for (int i = 0; i < size_matrix; i++) {
              int adder = 0;
              // Y cada columna de la primera (A)
                      for (int j = 0; j < size_matrix; j++) {
                      // Multiplicamos y sumamos resultado
                          #pragma omp atomic 
                            adder += matrix_A[i][j] * matrix_B[j][a];                      }
              // Lo acomodamos dentro del producto
              matrix_Out[i][a] = adder;
          }
      }
  double time_end= omp_get_wtime();
  double total_time = time_end-time_start ; //Calcula el tiempo total de la diferencia entre el tiempo final y el inicial
  printf("\n\t No reduction \e[48;2;255;255;0m\e[38;5;196m\e[1m Atomic \e[0m\e[38;2;0;255;0m \e[48;2;0;0;0m %lf \e[0m seg \t",total_time);
  /*
  printf("La matriz de salida es :\n");
  showMatrix(matrix_Out , size_matrix); 
  */
  return total_time;

  }


double multMatrixnrc(int**matrix_A , int**matrix_B , int p, int size_matrix){
    double time_start= omp_get_wtime();
    omp_set_num_threads(p);
    int**matrix_Out = generateMatrix(size_matrix,1); //declaracion de matriz salida

    //Aquí se va a ejecutar el código de la multiplicación

    #pragma omp parallel for 
      for (int a = 0; a < size_matrix; a++) {
      // Dentro recorremos las filas de la primera (A)
         #pragma omp parallel for
          for (int i = 0; i < size_matrix; i++) {
              int adder = 0;
              // Y cada columna de la primera (A)
                  
                      for (int j = 0; j < size_matrix; j++) {
                      // Multiplicamos y sumamos resultado
                          #pragma omp critical 
                            adder += matrix_A[i][j] * matrix_B[j][a];
                      }
              // Lo acomodamos dentro del producto
              matrix_Out[i][a] = adder;
          }
      }

    double time_end= omp_get_wtime();
    double total_time = time_end-time_start ; //Calcula el tiempo total de la diferencia entre el tiempo final y el inicial
    printf("\t No reduction \e[48;2;255;255;0m\e[38;5;196m\e[1m Critical \e[0m \e[38;2;0;255;0m \e[48;2;0;0;0m %lf \e[0m seg \n",total_time);
  
    return total_time;

  }  


double multMatrixrD(int**matrix_A , int**matrix_B , int p, int size_matrix){
    double time_start= omp_get_wtime();
    omp_set_num_threads(p);
    int**matrix_Out = generateMatrix(size_matrix,1); //declaracion de matriz salida

    //Estas impresiones, junto con la de pi que no está agregada, discutir si mostrar o no
    /*printf("Matriz A :\n");
    showMatrix(matrix_A , size_matrix);  //imprimir matriz A
    printf("Matriz A :\n");
    showMatrix(matrix_B , size_matrix);  //imprimir matriz B
    */
    //Aquí se va a ejecutar el código de la multiplicación

    #pragma omp parallel for
        for (int a = 0; a < size_matrix; a++) {
          #pragma omp parallel for
              for (int i = 0; i < size_matrix; i++) {
                  int adder = 0;
                      #pragma omp parallel for schedule(guided , 500) reduction(+:adder) 
                          for (int j = 0; j < size_matrix; j++) {
                          // Multiplicamos y sumamos resultado
                              adder += matrix_A[i][j] * matrix_B[j][a];
                          }
                  // Lo acomodamos dentro del producto
                  matrix_Out[i][a] = adder;
              }
        }

    
    double time_end= omp_get_wtime();
    /*printf("La matriz de salida es :\n");
    showMatrix(matrix_Out , size_matrix);
    */
    double total_time = time_end-time_start ; //Calcula el tiempo total de la diferencia entre el tiempo final y el inicial
    printf("\n Reduction Dynamic%lf \n",total_time);
  
    return total_time;

  }  