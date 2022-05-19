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


  double*times_1 = (double*)malloc(N*sizeof(double)); //Se genera la estructura donde se va a guardar los tiempos usando atomic
  double*times_2 = (double*)malloc(N*sizeof(double)); //Se genera la estructura donde se va a guardar los tiempos usando critical
  double*times_3 = (double*)malloc(N*sizeof(double)); //Se genera la estructura donde se va a guardar los tiempos usando atomic
  double*times_4 = (double*)malloc(N*sizeof(double)); //Se genera la estructura donde se va a guardar los tiempos usando critical
  
  double*times_p = (double*)malloc(N*sizeof(double)); //Se genera la estructura donde se va a guardar los tiempos usando critical



  double*promedio_1 = (double*)malloc(omp_get_num_procs()*sizeof(double));
  double*devioEstandar_1 = (double*)malloc(omp_get_num_procs()*sizeof(double));

  double*promedio_2 = (double*)malloc(omp_get_num_procs()*sizeof(double));
  double*devioEstandar_2 = (double*)malloc(omp_get_num_procs()*sizeof(double));

  double*promedio_3 = (double*)malloc(omp_get_num_procs()*sizeof(double));
  double*devioEstandar_3 = (double*)malloc(omp_get_num_procs()*sizeof(double));

  double*promedio_4 = (double*)malloc(omp_get_num_procs()*sizeof(double));
  double*devioEstandar_4 = (double*)malloc(omp_get_num_procs()*sizeof(double));

  
  printf("\n\t\tEjecución del algoritmo para el \e[38;2;128;0;255m \e[48;2;0;0;0mcalculo de PI con un numero de pasos de %d \e[0m, se obtiene: \n\n" , n_steps);

  printf("\n\e[38;2;0;255;0m \e[48;2;0;0;0m Algoritmo sin pragmas usando 1 procesador/es: \e[0m\n\n");
  for(int j = 0 ; j < N ; j++){
        times_p[j] = pickerPi(5,1,n_steps);
    }
  double avg_p = getAverage(times_p,N); 
  double sd_p = getStdDeviation(times_p,avg_p,N);
  printf(" El\e[38;2;0;0;255m \e[48;2;0;0;0m \e[3mdesvio estandar \e[0m sin pragma con 1 procesador: \e[38;2;0;0;255m \e[48;2;0;0;0m %lf \e[0m segundos\t\t", sd_p);
  printf("\e[38;5;196m \e[48;2;0;0;0m\e[3m Promedio \e[0m de tiempo sin pragma con 1 procesador: \e[38;5;196m \e[48;2;0;0;0m %lf \e[0m segundos\n\n", avg_p);
  
  
  for(int i = 1 ; i <= omp_get_num_procs() ; i++){
    sleep(4);  
    printf("\n\e[38;2;0;255;0m \e[48;2;0;0;0m Algoritmo con pragmas usando %d procesador/es: \e[0m\n\n", (i));
    if(option==1){
      for(int j = 0 ; j < N ; j++){
          times_1[j] = pickerPi(option,i,n_steps);
          times_2[j] = pickerPi(option+2,i,n_steps);
      }
    }
    else{
         for(int j = 0 ; j < N ; j++){
          times_1[j] = pickerPi(option,i,n_steps);
          times_2[j] = pickerPi(option+2,i,n_steps); 
          times_3[j] = pickerPi(option+4,i,n_steps);
          times_4[j] = pickerPi(option+5,i,n_steps);  
          }
    }

    //printf("\n");
    double avg_1 = getAverage(times_1,N); 
    double avg_2 = getAverage(times_2,N); 
    double avg_3 = getAverage(times_3,N); 
    double avg_4 = getAverage(times_4,N); 

    //printf("El promedio de los tiempos es de: %lf\n\n", avg);
    promedio_1[i]=avg_1;
    devioEstandar_1[i]=getStdDeviation(times_1,avg_1,N);

    promedio_2[i]=avg_2;
    devioEstandar_2[i]=getStdDeviation(times_2,avg_2,N);

    promedio_3[i]=avg_3;
    devioEstandar_3[i]=getStdDeviation(times_3,avg_3,N);
    
    promedio_4[i]=avg_4;
    devioEstandar_4[i]=getStdDeviation(times_4,avg_4,N);

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

    printf(" El \e[38;2;0;0;255m\e[48;2;0;0;0m\e[3m desvio estandar \e[0m para el Reduction guided con %d procesador: \e[38;2;0;0;255m \e[48;2;0;0;0m %lf \e[0m seg  ", (i), devioEstandar_3[i]);
    printf("\e[38;5;196m \e[48;2;0;0;0m\e[3m Promedio \e[0m de tiempo para el Rduction guided con %d procesador:\e[38;5;196m \e[48;2;0;0;0m %lf \e[0m seg\n\n", (i), promedio_3[i]);
    printf(" El \e[38;2;0;0;255m\e[48;2;0;0;0m\e[3m desvio estandar \e[0m para Reduc con Plan static con %d procesador:\e[38;2;0;0;255m \e[48;2;0;0;0m %lf \e[0m seg  ", (i), devioEstandar_4[i]);
    printf("\e[38;5;196m \e[48;2;0;0;0m\e[3m Promedio \e[0m de tiempo para Reduc con Plan static con %d procesador:\e[38;5;196m \e[48;2;0;0;0m %lf \e[0m seg\n\n", (i), promedio_4[i]);
 
    }
    
  }

  printf("\n");

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
                    return generatorPInrc(i,n_steps);
                    break;
                case 4:
                    return pruebaDynamic(i,5,n_steps);
                    break;
                case 5:
                    return generatorPI(i,n_steps);
                    break;
                case 6:
                    return pruebaGuided(i,8,n_steps);
                    break;
                case 7:
                    return pruebaStatic(i,2,n_steps);
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
  printf("\n\t\e[48;2;255;255;0m\e[38;5;196m\e[1m Reduction  Normal \e[0m\e[38;2;0;255;0m\e[48;2;0;0;0m %lf \e[0m seg\t",total_time);
  
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
  printf("\t No reduction \e[48;2;255;255;0m\e[38;5;196m\e[1m Critical \e[0m \e[38;2;0;255;0m \e[48;2;0;0;0m %lf \e[0m seg \n",total_time);
  
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
   printf("\n\t No reduction \e[48;2;255;255;0m\e[38;5;196m\e[1m Atomic \e[0m\e[38;2;0;255;0m \e[48;2;0;0;0m %lf \e[0m seg \t",total_time);
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
    printf("\n\t \e[48;2;255;255;0m\e[38;5;196m\e[1m Secuencial sin pragma \e[0m \e[38;2;0;255;0m \e[48;2;0;0;0m %lf \e[0m seg \n",total_time);

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
  printf("\t Reduction con \e[48;2;255;255;0m\e[38;5;196m\e[1m Planificación Dinamica \e[0m \e[38;2;0;255;0m \e[48;2;0;0;0m %lf \e[0m seg \n" ,  total_time);

  return total_time;
}

// igual que el dinamic (le da mientras va terminando lo que tiene), pero en cada vuelta el conjunto de iteraciones que el so le da es menor (ej: le da 100 , la proxima le da 40 , la prox 10 ,5, ect ) 
double pruebaGuided(int n , int percen , int n_steps){
  int percentaje_local = percentage(n_steps,percen);
  if(percentaje_local==0){
    percentaje_local= percentaje_local+1;
  }
  double time_start= omp_get_wtime(); //Setea el tiempo inicial para medir el tiempo total
  double x, pi , sum = 0.0;
  step = 1.0 / (double) n_steps;
  omp_set_num_threads(n); //Setea la cantidad de Threads a usar. No debe superar a la cantidad física de cores

  #pragma omp parallel for schedule(guided , percentaje_local) reduction(+:sum) private(x) 
  for(int i = 0 ; i < n_steps ; i++){
    x = (i+0.5)*step;
    sum += 4.0/(1.0+x*x);
  }
  pi = step * sum;

  double time_end= omp_get_wtime(); //Setea el tiempo final para medir el tiempo total
  double total_time = time_end-time_start ; //Calcula el tiempo total de la diferencia entre el tiempo final y el inicial
  printf("\e[48;2;255;255;0m\e[38;5;196m\e[1m Planificación Guided \e[0m\e[38;2;0;255;0m\e[48;2;0;0;0m %lf \e[0m seg\t" ,  total_time);

  return total_time;
}

    // el so le asigna a cada hilo dinamicamente unas cierca cantidad de iteraciones (mientras van terminando le va dando hilos de los que quede )
double pruebaDynamic(int n , int percen, int n_steps){
  unsigned long int percentaje_local = percentage(n_steps,percen);
  if(percentaje_local==0){
    percentaje_local= percentaje_local+1;
  }
  double time_start= omp_get_wtime(); //Setea el tiempo inicial para medir el tiempo total
  double x, pi , sum = 0.0;
  step = 1.0 / (double) n_steps;
  omp_set_num_threads(n); //Setea la cantidad de Threads a usar. No debe superar a la cantidad física de cores

  #pragma omp parallel for schedule(dynamic, percentaje_local) reduction(+:sum) private(x) 
  for(int i = 0 ; i < n_steps ; i++){
    x = (i+0.5)*step;
    sum += 4.0/(1.0+x*x);
  }
  pi = step * sum;

  double time_end= omp_get_wtime(); //Setea el tiempo final para medir el tiempo total
  double total_time = time_end-time_start ; //Calcula el tiempo total de la diferencia entre el tiempo final y el inicial
  printf("\e[48;2;255;255;0m\e[38;5;196m\e[1m Planificación Dinamica \e[0m\e[38;2;0;255;0m\e[48;2;0;0;0m %lf \e[0mseg\t" ,  total_time);

  return total_time;
}

// el so le asigna a cada hilo estaticmaente unas cierca cantidad de iteraciones, y prepara las proximas iteracciones especificas para cada hilo (n espera q termine la que tiene para asignarle otra ya lo define de antemano)
double pruebaStatic(int n , int percen, int n_steps){
  unsigned long int percentaje_local = percentage((unsigned long int)n_steps,(unsigned long int)percen);
  if(percentaje_local==0){
    percentaje_local= percentaje_local+1;
  }
  double time_start= omp_get_wtime(); //Setea el tiempo inicial para medir el tiempo total
  double x, pi , sum = 0.0;
  step = 1.0 / (double) n_steps;
  omp_set_num_threads(n); //Setea la cantidad de Threads a usar. No debe superar a la cantidad física de cores

  #pragma omp parallel for schedule(static, percentaje_local) reduction(+:sum) private(x) 
  for(int i = 0 ; i < n_steps ; i++){
    x = (i+0.5)*step;
    sum += 4.0/(1.0+x*x);
  }
  pi = step * sum;

  double time_end= omp_get_wtime(); //Setea el tiempo final para medir el tiempo total
  double total_time = time_end-time_start ; //Calcula el tiempo total de la diferencia entre el tiempo final y el inicial
  printf("\e[48;2;255;255;0m\e[38;5;196m\e[1m Planificación Estatica \e[0m\e[38;2;0;255;0m\e[48;2;0;0;0m %lf \e[0m seg\n" ,  total_time);

  return total_time;
}