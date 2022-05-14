#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <unistd.h>  //  para usar el sleep

static long num_steps = 100000; //400000000
double step;

void generatorPI();
void generatorPIr(int n);
void generatorPInra(int n);
void generatorPInrc(int n);
void generatorPIr2(int n);
void generatorPIrD(int n);

int main(){

  printf("\ncon un num_step de %d \n" , num_steps);
  
  printf("\nsecuencial sin pragmas (normal)\n");
  printf("\n");
   
  generatorPI();


  printf("\nsecuencial con pragmas\n");
  printf("\n");
  
  sleep(4);
  generatorPInrc(1);  
  printf("\n");
  sleep(4);
  generatorPInra(1); 
  printf("\n");
  sleep(4);
  generatorPIr(1);


  printf("\nparalelo 2 proc\n");

  sleep(4);
  printf("\n");
  generatorPInrc(2);
  printf("\n");
  sleep(4);  
  generatorPInra(2);
  
  printf("\n");
  sleep(4);  
  generatorPIr(2);
  printf("\n");
  sleep(4);  
  generatorPIrD(2);

  printf("\nparalelo 3 proc\n");

  sleep(4);
  printf("\n");
  generatorPInrc(3);
  printf("\n");
  sleep(4);  
  generatorPInra(3);
  
  printf("\n");
  sleep(4);  
  generatorPIr(3);
  printf("\n");
  sleep(4);  
  generatorPIrD(3);

 printf("\nparalelo 4 proc\n");

  sleep(4);
  printf("\n");
  generatorPInrc(4);
  printf("\n");
  sleep(4);  
  generatorPInra(4);
  
  printf("\n");
  sleep(4);  
  generatorPIr(4);
  printf("\n");
  sleep(4);  
  generatorPIrD(4);


  return 0;
}


void generatorPIr(int n){
  float tiempo_inicial= omp_get_wtime();
  double x, pi , sum = 0.0;
  step = 1.0 / (double) num_steps;
  omp_set_num_threads(n); //Setea la cantidad de Threads a usar. No debe superar a la cantidad física de cores

  #pragma omp parallel for reduction(+:sum) private(x)
  for(int i = 0 ; i < num_steps ; i++){
    x = (i+0.5)*step;
    sum += 4.0/(1.0+x*x);
  }
  pi = step * sum;

  float tiempo_final= omp_get_wtime();
  
  printf(" reduccion %f  The pi's valor : %lf\n",tiempo_final-tiempo_inicial , pi);
}


void generatorPInrc(int n){
  float tiempo_inicial= omp_get_wtime();

  double x, pi , sum= 0.0;
  step = 1.0 / (double) num_steps;
  
  omp_set_num_threads(n); //Setea la cantidad de Threads a usar. No debe superar a la cantidad física de cores
 
  #pragma omp parallel for
   for(int i = 0 ; i < num_steps ; i++){
     double x = 4.0/(1.0+(((i+0.5)*step)*((i+0.5)*step)));
     #pragma omp critical
        sum = sum + x;
   }

  pi = step * sum;

  float tiempo_final= omp_get_wtime();
 
  printf("no reduccion %f critical The pi's valor : %lf \n",tiempo_final-tiempo_inicial,pi);
  }



void generatorPInra(int n){
  float tiempo_inicial= omp_get_wtime();


   double pi , sum = 0.0;
   step = 1.0 / (double) num_steps;
  
   omp_set_num_threads(n); //Setea la cantidad de Threads a usar. No debe superar a la cantidad física de cores
 
   #pragma omp parallel for
   for(int i = 0 ; i < num_steps ; i++){
     double x = 4.0/(1.0+(((i+0.5)*step)*((i+0.5)*step)));
     #pragma omp atomic
        sum = sum + x;
   }
   pi = step * sum;
   float tiempo_final= omp_get_wtime();
  printf("no reduccion %f atomic      The pi's valor : %lf\n",tiempo_final-tiempo_inicial,pi);
}


void generatorPI(){
   
    float tiempo_inicial= omp_get_wtime();
    double x, pi , sum = 0.0;
    step = 1.0 / (double) num_steps;
    for(int i = 0 ; i < num_steps ; i++){
     
      x = (i+0.5)*step;
      sum += 4.0/(1.0+x*x);
    }
    pi = step * sum;
  
    float tiempo_final= omp_get_wtime();
  
    printf("comun-seq %f  The pi's valor : %lf\n",tiempo_final-tiempo_inicial,pi);
}

/*

void generatorPIr2(int n){
  float tiempo_inicial= omp_get_wtime();
  double pi , sum = 0.0;
  step = 1.0 / (double) num_steps;
  omp_set_num_threads(n); //Setea la cantidad de Threads a usar. No debe superar a la cantidad física de cores
  
    #pragma omp parallel for reduction(+:sum)
    for(int i = 0 ; i < num_steps ; i++){
      double x = 4.0/(1.0+(((i+0.5)*step)*((i+0.5)*step)));
      sum = sum + x;
    }
    pi = step * sum;

    float tiempo_final= omp_get_wtime();

    printf(" reduccion2 %f  The pi's valor : %lf\n",tiempo_final-tiempo_inicial , pi);
}*/



void generatorPIrD(int n){
  float tiempo_inicial= omp_get_wtime();
  double x, pi , sum = 0.0;
  step = 1.0 / (double) num_steps;
  omp_set_num_threads(n); //Setea la cantidad de Threads a usar. No debe superar a la cantidad física de cores

  #pragma omp parallel for schedule(guided , 20000) reduction(+:sum) private(x) 
  for(int i = 0 ; i < num_steps ; i++){
    x = (i+0.5)*step;
    sum += 4.0/(1.0+x*x);
  }
  pi = step * sum;

  float tiempo_final= omp_get_wtime();
  
  printf(" reduccion dynamic %f  The pi's valor : %lf\n",tiempo_final-tiempo_inicial , pi);
}