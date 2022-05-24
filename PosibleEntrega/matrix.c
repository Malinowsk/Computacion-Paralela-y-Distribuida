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

  double*times_1 = (double*)malloc(N*sizeof(double)); //Se genera la estructura donde se va a guardar los tiempos usando atomic/red normal
  double*times_2 = (double*)malloc(N*sizeof(double)); //Se genera la estructura donde se va a guardar los tiempos usando critical/dinamic
  double*times_3 = (double*)malloc(N*sizeof(double)); //Se genera la estructura donde se va a guardar los tiempos usando red guided
  double*times_4 = (double*)malloc(N*sizeof(double)); //Se genera la estructura donde se va a guardar los tiempos usando red static
  
  double*times_p = (double*)malloc(N*sizeof(double)); //Se genera la estructura donde se va a guardar los tiempos usando el algoritmo secuencial básico sin pragmas

  // se generan las estructuras donde se usan para guardar los promedios y desvios estandar de los algoritmos concurrentes
  double*promedio_1 = (double*)malloc(omp_get_num_procs()*sizeof(double));
  double*devioEstandar_1 = (double*)malloc(omp_get_num_procs()*sizeof(double));

  double*promedio_2 = (double*)malloc(omp_get_num_procs()*sizeof(double));
  double*devioEstandar_2 = (double*)malloc(omp_get_num_procs()*sizeof(double));

  double*promedio_3 = (double*)malloc(omp_get_num_procs()*sizeof(double));
  double*devioEstandar_3 = (double*)malloc(omp_get_num_procs()*sizeof(double));

  double*promedio_4 = (double*)malloc(omp_get_num_procs()*sizeof(double));
  double*devioEstandar_4 = (double*)malloc(omp_get_num_procs()*sizeof(double));

  int**matrix_A = generateMatrix(size_matrix,0); //declaracion e inicialización de matriz A
  int**matrix_B = generateMatrix(size_matrix,0); //declaracion e inicialización de matriz B

  printf("\n\t\tEjecución del algoritmo para el \e[38;2;128;0;255m \e[48;2;0;0;0mcalculo de mult de matrices con un tamaño n de %d \e[0m, se obtiene: \n\n" , size_matrix);

  //calculo secuencial sin pragmas

  printf("\n\e[38;2;0;255;0m \e[48;2;0;0;0m Algoritmo sin pragmas usando 1 procesador/es: \e[0m\n\n");
  
  for(int j = 0 ; j < N ; j++){ // se calcula un promedio de tiempo para algoritmo secuencial básico sin pragmas
    times_p[j] = pickerMatrix(5,1,size_matrix,matrix_A,matrix_B); 
  }
  // calculo del promedio, desvio estandar y se muestra por pantalla (tiempo secuancial sin pragma) 
  double avg_p = getAverage(times_p,N); 
  double sd_p = getStdDeviation(times_p,avg_p,N);
  printf(" El\e[38;2;0;0;255m \e[48;2;0;0;0m \e[3mdesvio estandar \e[0m sin pragma con 1 procesador: \e[38;2;0;0;255m \e[48;2;0;0;0m %lf \e[0m segundos\t", sd_p);
  printf("\e[38;5;196m \e[48;2;0;0;0m\e[3m Promedio \e[0m de tiempo sin pragma con 1 procesador: \e[38;5;196m \e[48;2;0;0;0m %lf \e[0m segundos\n\n", avg_p);
    
  //calculo utilizando pragmas

  //iteracion de tanto procesadores como tenga la cpu en la cual se ejecuta el programa
  for(int i = 1 ; i <= omp_get_num_procs() ; i++){
    sleep(4);  
    printf("\n\e[38;2;0;255;0m \e[48;2;0;0;0m Algoritmo con pragmas usando %d procesador/es: \e[0m\n\n", (i));
    for(int j = 0 ; j < N ; j++){
        times_1[j] = pickerMatrix(option,i,size_matrix,matrix_A,matrix_B);
        times_2[j] = pickerMatrix(option+2,i,size_matrix,matrix_A,matrix_B);
        if(option==2){ // Entra con la opcion reduccion
          times_3[j] = pickerMatrix(option+4,i,size_matrix,matrix_A,matrix_B);
          times_4[j] = pickerMatrix(option+5,i,size_matrix,matrix_A,matrix_B);
        } 
    }

///////////////////////////////calculo de promedios y desvio estandar///////////////////////////////////////// 

    double avg_1 = getAverage(times_1,N); 
    double avg_2 = getAverage(times_2,N); 

    promedio_1[i]=avg_1;
    devioEstandar_1[i]=getStdDeviation(times_1,avg_1,N);
    promedio_2[i]=avg_2;
    devioEstandar_2[i]=getStdDeviation(times_2,avg_2,N);
    
    // Entra con la opcion reduccion
    if(option==2){ 
      double avg_3 = getAverage(times_3,N); 
      double avg_4 = getAverage(times_4,N); 
      promedio_3[i]=avg_3;
      devioEstandar_3[i]=getStdDeviation(times_3,avg_3,N);
      promedio_4[i]=avg_4;
      devioEstandar_4[i]=getStdDeviation(times_4,avg_4,N);
    }

/////////////////////////// Muestra por pantalla promedios y desvios estandar///////////////////////////////////////////////
    

    if(option==1){ // Entra con la opcion no reduccion
    printf(" El\e[38;2;0;0;255m \e[48;2;0;0;0m \e[3mdesvio estandar \e[0m para el  atomic con %d proc: \e[38;2;0;0;255m \e[48;2;0;0;0m %lf \e[0m segundos\t", (i), devioEstandar_1[i]);
    printf("\e[38;5;196m \e[48;2;0;0;0m\e[3m Promedio \e[0m de tiempo para el  atomic con %d proc: \e[38;5;196m \e[48;2;0;0;0m %lf \e[0m segundos\n\n", (i), promedio_1[i]);
    
    printf(" El\e[38;2;0;0;255m \e[48;2;0;0;0m \e[3mdesvio estandar \e[0m para el critical con %d proc:\e[38;2;0;0;255m \e[48;2;0;0;0m %lf \e[0m segundos\t", (i), devioEstandar_2[i]);
    printf("\e[38;5;196m \e[48;2;0;0;0m\e[3m Promedio \e[0m de tiempo para el critical con %d proc:\e[38;5;196m \e[48;2;0;0;0m %lf \e[0m segundos\n\n", (i), promedio_2[i]);
    }
    else // Entra con la opcion reduccion
    {
    printf(" El \e[38;2;0;0;255m\e[48;2;0;0;0m\e[3m desvio estandar \e[0m para el Reduction con %d proc: \e[38;2;0;0;255m \e[48;2;0;0;0m %lf \e[0m seg\t", (i), devioEstandar_1[i]);
    printf("\e[38;5;196m \e[48;2;0;0;0m\e[3m Promedio \e[0m de tiempo para el Reduction con %d proc:\e[38;5;196m \e[48;2;0;0;0m %lf \e[0m seg\n\n", (i), promedio_1[i]);
    
    printf(" El \e[38;2;0;0;255m\e[48;2;0;0;0m\e[3m desvio estandar \e[0m para Dynamic con %d proc:\e[38;2;0;0;255m \e[48;2;0;0;0m %lf \e[0m seg\t\t", (i), devioEstandar_2[i]);
    printf("\e[38;5;196m \e[48;2;0;0;0m\e[3m Promedio \e[0m de tiempo para Dynamic con %d proc:\e[38;5;196m \e[48;2;0;0;0m %lf \e[0m seg\n\n", (i), promedio_2[i]);
    
    printf(" El \e[38;2;0;0;255m\e[48;2;0;0;0m\e[3m desvio estandar \e[0m para el Guided con %d proc: \e[38;2;0;0;255m \e[48;2;0;0;0m %lf \e[0m seg\t", (i), devioEstandar_3[i]);
    printf("\e[38;5;196m \e[48;2;0;0;0m\e[3m Promedio \e[0m de tiempo para el Guided con %d proc:\e[38;5;196m \e[48;2;0;0;0m %lf \e[0m seg\n\n", (i), promedio_3[i]);
    
    printf(" El \e[38;2;0;0;255m\e[48;2;0;0;0m\e[3m desvio estandar \e[0m para Static con %d proc:\e[38;2;0;0;255m \e[48;2;0;0;0m %lf \e[0m seg\t\t", (i), devioEstandar_4[i]);
    printf("\e[38;5;196m \e[48;2;0;0;0m\e[3m Promedio \e[0m de tiempo para Static con %d proc:\e[38;5;196m \e[48;2;0;0;0m %lf \e[0m seg\n\n", (i), promedio_4[i]);
    }
    
  }

  printf("\n");

  printf("Continuar");
  sleep(2);
  getchar(); // presionar una tecla para continuar

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
                    return multMatrixrD(matrix_A,matrix_B,p,size_matrix,4);
                    break;
                case 5:
                    return multMatrix(matrix_A,matrix_B,p,size_matrix);
                    break;
                case 6:
                    return multMatrixrG(matrix_A,matrix_B,p,size_matrix,4);
                    break;
                case 7:
                    return multMatrixrS(matrix_A,matrix_B,p,size_matrix,4);
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
    printf("\n\e[48;2;255;255;0m\e[38;5;196m\e[1m Reduction  Normal \e[0m\e[38;2;0;255;0m\e[48;2;0;0;0m %lf \e[0m seg",total_time);
  
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


double multMatrixnrc(int**matrix_A , int**matrix_B , int p, int size_matrix ){
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

double multMatrixrD(int**matrix_A , int**matrix_B , int p, int size_matrix , int percen ){
    int percentaje_local = percentage(size_matrix,percen);
    if(percentaje_local==0){
    percentaje_local= percentaje_local+1;
    }
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
                      #pragma omp parallel for schedule(dynamic , percentaje_local) reduction(+:adder) 
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

    printf("\e[48;2;255;255;0m\e[38;5;196m\e[1m Planificación Dinamica \e[0m\e[38;2;0;255;0m\e[48;2;0;0;0m %lf \e[0mseg\t" ,  total_time);
  
    return total_time;

  }  

  
double multMatrixrG(int**matrix_A , int**matrix_B , int p, int size_matrix,  int percen ){
    int percentaje_local = percentage(size_matrix,percen);
    if(percentaje_local==0){
    percentaje_local= percentaje_local+1;
    }
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
                      #pragma omp parallel for schedule(guided , percentaje_local) reduction(+:adder) 
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
    printf("\e[48;2;255;255;0m\e[38;5;196m\e[1m Planificación Guided \e[0m\e[38;2;0;255;0m\e[48;2;0;0;0m %lf \e[0m seg\t" ,  total_time);
  
    return total_time;

  }  

  
double multMatrixrS(int**matrix_A , int**matrix_B , int p, int size_matrix,  int percen ){
    int percentaje_local = percentage(size_matrix,percen);
    if(percentaje_local==0){
    percentaje_local= percentaje_local+1;
    }
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
                      #pragma omp parallel for schedule(static , percentaje_local) reduction(+:adder) 
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
    printf("\e[48;2;255;255;0m\e[38;5;196m\e[1m Planificación Estatica \e[0m\e[38;2;0;255;0m\e[48;2;0;0;0m %lf \e[0m seg\n" ,  total_time);
  
    return total_time;

  }  
