#include <stdio.h>

// prinicipal
void pi(int n_steps , int option); 

//selector
double pickerPi (int num, int i , int n_steps);

//secuencial
double generatorPI(int n , int n_steps); //  

// sin reduction
double generatorPInra(int n , int n_steps);
double generatorPInrc(int n , int n_steps);

//reduction
double generatorPIr(int n , int n_steps);
double pruebaGuided(int n ,int percen , int n_steps);
double pruebaDynamic(int n ,int percen , int n_steps);
double pruebaStatic(int n ,int percen , int n_steps);


