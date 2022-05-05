#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

void showTimeSeq();
void showTimePrl();

void main(){

  omp_set_num_threads(omp_get_num_procs()); //Setea la cantidad de Threads a usar. No debe superar a la cantidad física de cores
  if (1 == 0) //Se controla el argumento del programa. Con : a.exe 0 => Secuencial ; a.exe 1 => Paralelo
    showTimeSeq();
  else
    showTimePrl();
  printf("%lf",omp_get_wtime());
}

void showTimeSeq(){
  //Se imprimen dos mensajes de forma secuencial, mostrando el tiempo que le llevó.
  printf("Hello World from Thread number %i \n",omp_get_thread_num());
  printf("Hello World from Thread number %i \n",omp_get_thread_num());
  printf("Hello World from Thread number %i \n",omp_get_thread_num());
  printf("Hello World from Thread number %i \n",omp_get_thread_num());
  printf("Hello World from Thread number %i \n",omp_get_thread_num());
  printf("Hello World from Thread number %i \n",omp_get_thread_num());
  //printf("%lf",omp_get_wtime());
}

void showTimePrl(){
  //Se imprime un mensaje por cada Thread, además de mostrar el tiempo que llevó esto luego del fork
  //Entrando a la zona de Fork
  #pragma omp parallel
  {
     printf("Hello World from Thread number %i \n",omp_get_thread_num());
     printf("Hello World from Thread number %i \n",omp_get_thread_num());
     printf("Hello World from Thread number %i \n",omp_get_thread_num());
  }
  //Entrando a la zona de Join
  //printf("%lf",omp_get_wtime());
}


