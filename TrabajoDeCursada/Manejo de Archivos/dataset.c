#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define TAM_REG 100
#define RANDOM 10

//Investigar como agregar al final en archivos de lectura y escritura


int main (){
    ///////////////////////////////////////////Apertura del archivo///////////////////////////////////////////////////
    FILE * arch = fopen("dataset.txt","a+");// abre el archiv si no existe lo crea , la a es para escribir en la ultima linea , el + para que tambien sea lectura
    
    

    //////////////////////////////////////////Escritura en el archivo////////////////////////////////////////////////
    
                    //////////////////////////Generación del número/////////////////////////////////////
    srand(time(NULL));
    char reg[10] = "\n"; //Aquí se guarda el salto de línea junto con el tiempo obtenido
    char temp[9] ; // Aquí se guarda el tiempo.
    float num = (float) (rand() % RANDOM) / (float) RANDOM; //Da un float entre 0 y 1 (Simulando que guarda el tiempo)
    
                    /////////////////////////Transformación e inserción del número//////////////////////
    snprintf(temp, 9, "%f", num); //Genera el casteo de float a string
    strcat(reg,temp); //Concateno el salto de línea con el valor obtenido
    fputs(reg, arch); // Escribe en la ultima linea del archivo (por el modo a+)

    //////////////////////////////////////////Lectura en el archivo////////////////////////////////////////////////
    char get [TAM_REG];  // Crea un arreglo de char (string)
    fseek (arch, 0, 0);   // Ubica el puntero al principio del archivo 

    while (feof(arch)==0){      // Lee todas las lineas, incluso la última la lee dos veces (??)
      fgets(get,TAM_REG,arch);  // Guarda en get toda la linea del archivo donde se encuentra parado el puntero, el puntero avanza en uno
      printf("%s", get); // imprime get , o sea la linea que se capturo
    }
    ///////////////////////////////////////////Clausura del archivo///////////////////////////////////////////////////
    fclose(arch); // Cierra el archivo.

    return 0;
}
