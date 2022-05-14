#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "metrics.h"

#define SQUARE 2

double getStdDeviation(double*nums, double avg , int cant_muestras){

	double add_variance = 0; //Aca se va sumando los cuadrados de la diferencia del num actual y avg
	for (int i = 0 ; i < cant_muestras ; i++) 
		add_variance += pow(nums[i]-avg,SQUARE); //Se eleva al cuadrado la resta del numero actual y avg
	
	return sqrt(add_variance/cant_muestras); //Se retorna la raiz cuadrada del cociente entre la suma acumulada y N

}

double getAverage(double*nums , int cant_muestras) {

	double adder = 0; //Aca se va guardando la suma actual
	for (int i = 0 ; i < cant_muestras ; i++)
		adder+= nums[i]; //Se va sumando todos los tiempos presentes en la estructura
	printf("\n");
	return adder / cant_muestras ; //Se retorna efectivamente el promedio (cociente entre la suma y N)
}