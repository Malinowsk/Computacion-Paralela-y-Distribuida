#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define ITERACIONES 2100000000
#define SECUENCIAL 0
void showTimeSeq();
void showTimePrl();


void main(){
  omp_set_num_threads(omp_get_num_procs()); //Setea la cantidad de Threads a usar. No debe superar a la cantidad física de cores
  float tiempo_inicial= omp_get_wtime();
  if (SECUENCIAL == 1) //Se controla el argumento del programa. Con : a.exe 0 => Secuencial ; a.exe 1 => Paralelo
    showTimeSeq();
  else
    showTimePrl();
  float tiempo_final= omp_get_wtime();
  printf("%lf \n",tiempo_inicial);
  printf("%lf \n",tiempo_final);
  printf("%lf \n %i",tiempo_final-tiempo_inicial,SECUENCIAL);
}

void showTimeSeq(){
  //Se imprimen dos mensajes de forma secuencial, mostrando el tiempo que le llevó.
  for(int i = 0; i< ITERACIONES ;i++){
  int a =0;
  //printf("Hello World from Thread number %i \n",omp_get_thread_num());
  //printf("%lf",omp_get_wtime());
  }

}

void showTimePrl(){
  //Se imprime un mensaje por cada Thread, además de mostrar el tiempo que llevó esto luego del fork
  //Entrando a la zona de Fork
     #pragma omp parallel
     for(int i = 0; i< (ITERACIONES/2) ;i++){
     int a =0;
     //printf("Hello World from Thread number %i \n",omp_get_thread_num());
     }
  //Entrando a la zona de Join
  //printf("%lf",omp_get_wtime());
}


