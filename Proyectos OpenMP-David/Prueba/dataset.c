#include <stdio.h>
#include <stdlib.h>
#define TAM_REG 100

//Investigar como agregar al final en archivos de lectura y escritura


int main (){
    FILE * arch = fopen("dataset.txt","a+"); // abre el archiv si no existe lo crea , la a es para escribir en la ultima linea , el + para que tambien sea lectura

    fputs("\nchau", arch); // escribo en la ultima linea del archivo "chau"

    fseek (arch, 0, 0);   // ubico el puntero al principio del archivo

    char get [TAM_REG];  // creo un arrreglo de char (string)

    while (feof(arch)==0){      // leo todas las lineas, incluso la ultima la lee dos veces
      fgets(get,TAM_REG,arch);  // guarda en get toda la linea del archivo donde se encuentra parado el puntero, el puntero avanza en uno
      printf("%s", get); // imprime get , o sea la linea que se capturo
    }

    fclose(arch); // cierra el archivo.

    return 0;
}
