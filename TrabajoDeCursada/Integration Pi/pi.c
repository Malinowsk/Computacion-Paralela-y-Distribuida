#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define SECUENCIAL 1


static long num_steps = 200000000;
double step;

void generatorPI();
void generatorPIr(int n);
void generatorPInra(int n);
void generatorPInrc(int n);

int main(){   // DESDE DONDE DEEBERIAMOS CONTAR EL TIEMPO?


  printf("secuencial sin pragmas (normal)\n");
   
  /*if(SECUENCIAL != 1)
  else*/
  generatorPI();

  printf("secuencial\n");
   
  /*if(SECUENCIAL != 1)
  else*/
  generatorPIr(1);
  generatorPInra(1);  // SE PARALELIZA TODO EL PROGRAMA?
  generatorPInrc(1);  // SE PARALELIZA TODO EL PROGRAMA?

  printf("\nparalelo\n");

  /*if(SECUENCIAL != 1)
  else*/
  generatorPIr(2);
  generatorPInra(2);  // SE PARALELIZA TODO EL PROGRAMA?
  generatorPInrc(2);  // SE PARALELIZA TODO EL PROGRAMA?
  return 0;
}


void generatorPIr(int n){
  omp_set_num_threads(n); //Setea la cantidad de Threads a usar. No debe superar a la cantidad física de cores
  
  float tiempo_inicial= omp_get_wtime();
    double x, pi , sum = 0.0;
    step = 1.0 / (double) num_steps;
    #pragma omp parallel for reduction(+:sum) private(x)
    for(int i = 0 ; i < num_steps ; i++){
      x = (i+0.5)*step;
      sum += 4.0/(1.0+x*x);
    }
    pi = step * sum;
    //printf("The pi's valor : %lf \n",pi);

    float tiempo_final= omp_get_wtime();
    //printf("%lf \n",tiempo_inicial);
    //printf("%lf \n",tiempo_final);
    printf(" reduccion %lf  The pi's valor : %lf\n",tiempo_final-tiempo_inicial,pi);
}


void generatorPInrc(int n){
  omp_set_num_threads(n); //Setea la cantidad de Threads a usar. No debe superar a la cantidad física de cores
 
  float tiempo_inicial= omp_get_wtime();


   double x, pi , sum = 0.0;
   step = 1.0 / (double) num_steps;
   #pragma omp parallel for private(x)
   for(int i = 0 ; i < num_steps ; i++){
     x = (i+0.5)*step;
    // #pragma omp critical
    {
      sum += 4.0/(1.0+x*x);
    }
   }
   pi = step * sum;
   //printf("The pi's valor : %lf",step);
   //printf("The pi's valor : %lf",sum);
   //printf("The pi's valor : %lf",pi);

   float tiempo_final= omp_get_wtime();
  //printf("%lf \n",tiempo_inicial);
  //printf("%lf \n",tiempo_final);
  printf("no reduccion %lf critical The pi's valor : %lf\n",tiempo_final-tiempo_inicial,pi);
}



void generatorPInra(int n){
  omp_set_num_threads(n); //Setea la cantidad de Threads a usar. No debe superar a la cantidad física de cores
 
  float tiempo_inicial= omp_get_wtime();


   double x, pi , sum = 0.0;
   step = 1.0 / (double) num_steps;
   #pragma omp parallel for private(x)
   for(int i = 0 ; i < num_steps ; i++){
     x = (i+0.5)*step;
     #pragma omp private(x) atomic(sum)
      sum += 4.0/(1.0+x*x);
   }
   pi = step * sum;
   //printf("The pi's valor : %lf",step);
   //printf("The pi's valor : %lf",sum);
   //printf("The pi's valor : %lf",pi);

   float tiempo_final= omp_get_wtime();
  //printf("%lf \n",tiempo_inicial);
  //printf("%lf \n",tiempo_final);
  printf("no reduccion %lf atomic      The pi's valor : %lf\n",tiempo_final-tiempo_inicial,pi);
}


void generatorPI(){
    //omp_set_num_threads(n); //Setea la cantidad de Threads a usar. No debe superar a la cantidad física de cores
  
    float tiempo_inicial= omp_get_wtime();
    double x, pi , sum = 0.0;
    step = 1.0 / (double) num_steps;
    for(int i = 0 ; i < num_steps ; i++){
      x = (i+0.5)*step;
      sum += 4.0/(1.0+x*x);
    }
    pi = step * sum;
    //printf("The pi's valor : %lf \n",pi);

    float tiempo_final= omp_get_wtime();
    //printf("%lf \n",tiempo_inicial);
    //printf("%lf \n",tiempo_final);
    printf(" reduccion %lf  The pi's valor : %lf\n",tiempo_final-tiempo_inicial,pi);
}
