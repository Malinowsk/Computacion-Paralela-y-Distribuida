#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define SECUENCIAL 0


static long num_steps = 100000000;
double step;

void generatorPI();

int main(){   // DESDE DONDE DEEBERIAMOS CONTAR EL TIEMPO?
  omp_set_num_threads(omp_get_num_procs()); //Setea la cantidad de Threads a usar. No debe superar a la cantidad física de cores
  float tiempo_inicial= omp_get_wtime();
  if(SECUENCIAL != 1)
    generatorPI();  // SE PARALELIZA TODO EL PROGRAMA?
  else
    generatorPIs();
  float tiempo_final= omp_get_wtime();
  printf("%lf \n",tiempo_inicial);
  printf("%lf \n",tiempo_final);
  printf("%lf \n %i",tiempo_final-tiempo_inicial,SECUENCIAL);
  return 0;
}


void generatorPI(){

   double x, pi , sum = 0.0;
   step = 1.0 / (double) num_steps;
   //#pragma omp parallel
   {
      //#pragma omp for
      for(int i = 0 ; i < num_steps ; i++){
        x = (i+0.5)*step;

        {
           sum += 4.0/(1.0+x*x);
        }
      }

   }

   pi = step * sum;
   printf("The pi's valor : %lf",step);
   printf("The pi's valor : %lf",sum);
   printf("The pi's valor : %lf",pi);
}


void generatorPIs(){

   double x, pi , sum = 0.0;
   step = 1.0 / (double) num_steps;

   for(int i = 0 ; i < num_steps ; i++){
     x = (i+0.5)*step;
     sum += 4.0/(1.0+x*x);
   }

   pi = step * sum;
   printf("The pi's valor : %lf",step);
   printf("The pi's valor : %lf",sum);
   printf("The pi's valor : %lf",pi);
}

