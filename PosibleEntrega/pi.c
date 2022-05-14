#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <unistd.h>  //  Para usar el sleep
#include <math.h>
#include <time.h>
#include "pi.h"
#include "metrics.h" // Incluye el encabezado para el desvío y la media

#define N 8 //La cantidad de muestras(tiempos)
 
double step;


void pi(int n_steps,int option){


  double*nums = (double*)malloc(N*sizeof(double)); //Se genera la estructura donde se va a guardar los tiempos
  double*promedios = (double*)malloc(omp_get_num_procs()*sizeof(double));
  double*devioEstandar = (double*)malloc(omp_get_num_procs()*sizeof(double));

  printf("\nCon un numero de pasos de %d , se obtiene: \n\n" , n_steps);


  for(int i = 0 ; i < omp_get_num_procs() ; i++){
    sleep(4);  
    printf("\nUsando %d procesador/es: \n\n", (i+1));
    for(int j = 0 ; j < N ; j++){
        nums[j] = pickerPi(option,i+1,n_steps);
    }

    //printf("\n");
    double avg = getAverage(nums,N); 
    //printf("El promedio de los tiempos es de: %lf\n\n", avg);
    promedios[i]=avg;
    devioEstandar[i]=getStdDeviation(nums,avg,N);
    
    
  }

  for(int i = 0 ; i < omp_get_num_procs() ; i++){
    printf("El desvio estandar con %d procesador: %lf segundos\t\t", (i+1), devioEstandar[i]);
    printf("Promedio de tiempo con %d procesador: %lf segundos\n\n", (i+1), promedios[i]);
  }
  printf("Continuar");
  sleep(2);
  getchar();

}

double pickerPi(int num, int i , int n_steps){
     
     switch (num)
                {
                case 1:
                    return generatorPInra(i,n_steps);
                    break;
                case 2:
                    return generatorPIr(i,n_steps);
                    break;
                case 3:
                    return generatorPIr(i,n_steps);
                    break;
                case 4:
                    return generatorPIrD(i,n_steps);
                    break;
                default:
                    return 1.00;
                }
         return 1.00;
}


double generatorPIr(int n , int n_steps){
  double time_start= omp_get_wtime(); //Setea el tiempo inicial para medir el tiempo total
  double x, pi , sum = 0.0;
  step = 1.0 / (double) n_steps;
  omp_set_num_threads(n); //Setea la cantidad de Threads a usar. No debe superar a la cantidad física de cores

  #pragma omp parallel for reduction(+:sum) private(x)
  for(int i = 0 ; i < n_steps ; i++){
    x = (i+0.5)*step;
    sum += 4.0/(1.0+x*x);
  }
  pi = step * sum;

  double time_end= omp_get_wtime(); //Setea el tiempo final para medir el tiempo total
  double total_time = time_end-time_start ; //Calcula el tiempo total de la diferencia entre el tiempo final y el inicial
  printf("\n Reduction %lf seg \n",total_time);
  
  return total_time;
}


double generatorPInrc(int n , int n_steps){
  double time_start= omp_get_wtime(); //Setea el tiempo inicial para medir el tiempo total

  double x, pi , sum= 0.0;
  step = 1.0 / (double) n_steps;
  
  omp_set_num_threads(n); //Setea la cantidad de Threads a usar. No debe superar a la cantidad física de cores
 
  #pragma omp parallel for
   for(int i = 0 ; i < n_steps ; i++){
     double x = 4.0/(1.0+(((i+0.5)*step)*((i+0.5)*step)));
     #pragma omp critical
        sum = sum + x;
   }

  pi = step * sum;

  double time_end= omp_get_wtime(); //Setea el tiempo final para medir el tiempo total
  double total_time = time_end-time_start ; //Calcula el tiempo total de la diferencia entre el tiempo final y el inicial
  printf("\n No reduction Critical %lf \n",total_time);
  
  return total_time;

  }



double generatorPInra(int n , int n_steps){
   
   double time_start= omp_get_wtime(); //Setea el tiempo inicial para medir el tiempo total

   double pi , sum = 0.0;
   step = 1.0 / (double) n_steps;
  
   omp_set_num_threads(n); //Setea la cantidad de Threads a usar. No debe superar a la cantidad física de cores
 
   #pragma omp parallel for
   for(int i = 0 ; i < n_steps ; i++){
     double x = 4.0/(1.0+(((i+0.5)*step)*((i+0.5)*step)));
     #pragma omp atomic
        sum = sum + x;
   }
   pi = step * sum;
   
   double time_end= omp_get_wtime(); //Setea el tiempo final para medir el tiempo total
   double total_time = time_end-time_start ; //Calcula el tiempo total de la diferencia entre el tiempo final y el inicial
   printf("\n No reduction Atomic %lf seg \n",total_time);
   return total_time;
}


double generatorPI(int n , int n_steps){
   
    double time_start= omp_get_wtime(); //Setea el tiempo inicial para medir el tiempo total

    double x, pi , sum = 0.0;
    step = 1.0 / (double) n_steps;
    for(int i = 0 ; i < n_steps ; i++){
     
      x = (i+0.5)*step;
      sum += 4.0/(1.0+x*x);
    }
    pi = step * sum;
  
    double time_end= omp_get_wtime(); //Setea el tiempo final para medir el tiempo total
    double total_time = time_end-time_start ; //Calcula el tiempo total de la diferencia entre el tiempo final y el inicial
    printf("\n Secuencial %lf \n",total_time);

   return total_time;
  
    
}

/*

void generatorPIr2(int n){
  float tiempo_inicial= omp_get_wtime();
  double pi , sum = 0.0;
  step = 1.0 / (double) n_steps;
  omp_set_num_threads(n); //Setea la cantidad de Threads a usar. No debe superar a la cantidad física de cores
  
    #pragma omp parallel for reduction(+:sum)
    for(int i = 0 ; i < n_steps ; i++){
      double x = 4.0/(1.0+(((i+0.5)*step)*((i+0.5)*step)));
      sum = sum + x;
    }
    pi = step * sum;

    float tiempo_final= omp_get_wtime();

    printf(" reduccion2 %f  The pi's valor : %lf\n",tiempo_final-tiempo_inicial , pi);
}*/



double generatorPIrD(int n , int n_steps){
  double time_start= omp_get_wtime(); //Setea el tiempo inicial para medir el tiempo total
  double x, pi , sum = 0.0;
  step = 1.0 / (double) n_steps;
  omp_set_num_threads(n); //Setea la cantidad de Threads a usar. No debe superar a la cantidad física de cores

  #pragma omp parallel for schedule(guided , 200000) reduction(+:sum) private(x) 
  for(int i = 0 ; i < n_steps ; i++){
    x = (i+0.5)*step;
    sum += 4.0/(1.0+x*x);
  }
  pi = step * sum;

  double time_end= omp_get_wtime(); //Setea el tiempo final para medir el tiempo total
  double total_time = time_end-time_start ; //Calcula el tiempo total de la diferencia entre el tiempo final y el inicial
  printf("\n Reduction con Planificación Dinamica %lf \n",total_time);

   return total_time;
}