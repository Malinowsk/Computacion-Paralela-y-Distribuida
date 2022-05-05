#include <stdio.h>
#include <stdlib.h>
#define TAM_REG 10

//Investigar como agregar al final en archivos de lectura y escritura


int main (){
    FILE * arch = fopen("dataset.txt","r+");
    fputs("chau \n", arch);
    char get[10];
    while (feof(arch) == 0){
      fgets(get,TAM_REG,arch);
      printf("%s \n", get);
      //printf("Entra");
      //printf("Entra");
    }
    fclose(arch);
}
