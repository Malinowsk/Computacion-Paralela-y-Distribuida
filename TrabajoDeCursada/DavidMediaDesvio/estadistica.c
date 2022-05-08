#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#define N 5 //La cantidad de muestras(tiempos)
#define RANDOM 100000
#define SQUARE 2


void generateSamples(double*nums); //Inserta en la estructura los tiempos
double getAverage(double*nums); //Se obtiene la media aritmetica a partir de los tiempos que estan en la estructura
double getStdDeviation(double*nums, double avg); //Se obtiene el desvio estandar a traves de la muestra y la media

int main() {
	srand(time(NULL)); //Tratamiento del seed para el random
	double*nums = (double*)malloc(N*sizeof(double)); //Se genera la estructura donde se va a guardar los tiempos
	double avg; //Se cuenta con una variable para la media aritmetica, porque es necesaria para calcular el desvio

	generateSamples(nums);
	avg = getAverage(nums); 

	printf("El promedio de los tiempos es de: %f\n", avg);
	printf("El desvio estandar de los tiempos es de: %f\n ", getStdDeviation(nums,avg));

}

void generateSamples(double*nums) {

	for (int i = 0 ; i < N ; i++) {
    	nums[i]= (double) (rand() % RANDOM) / (double) RANDOM; //Se genera el numero aleatorio
    	printf("%f,",nums[i]);
    }
    printf("\n");
}


double getAverage(double*nums) {

	double adder = 0; //Aca se va guardando la suma actual
	for (int i = 0 ; i < N ; i++)
		adder+= nums[i]; //Se va sumando todos los tiempos presentes en la estructura
	printf("\n");
	return adder / N ; //Se retorna efectivamente el promedio (cociente entre la suma y N)
}

double getStdDeviation(double*nums, double avg){

	double add_variance = 0; //Aca se va sumando los cuadrados de la diferencia del num actual y avg
	for (int i = 0 ; i < N ; i++) 
		add_variance += pow(nums[i]-avg,SQUARE); //Se eleva al cuadrado la resta del numero actual y avg
	
	return sqrt(add_variance/N); //Se retorna la raiz cuadrada del cociente entre la suma acumulada y N

}