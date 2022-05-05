#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

static long num_steps = 100000;
double step;

void generatorPI(int flowType);

void main(int argc , char*argv[]){
  generatorPI(atoi(argv[1]));

}


void generatorPI(int flowType){

   double x, pi , sum = 0.0;
   step = 1.0 / (double) num_steps;
   //#pragma omp parallel
   {

      for(int i = 0 ; i < num_steps ; i++){
           if(flowType == 0)
             x = (i+0.5)*step;
           else {
             #pragma omp parallel
             {
               x = (i+0.5)*step;
             }
           }
           sum += 4.0/(1.0+x*x);
      }

   }
   pi = step * sum;
   printf("The pi's valor : %lf",step);
   printf("The pi's valor : %lf",sum);
   printf("The pi's valor : %lf",pi);
}
