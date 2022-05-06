#include <stdio.h>
#include <stdlib.h>  // para usar el system
#include <unistd.h>  //  para usar el sleep

void menu();

int main(){

    menu();
    
    return 0;
}

void menu(){

    int opcion ;    
    
    do {
        system("clear"); // limpia la pantalla

        printf("\n");
        printf("Elija una opcion del menu:\n");
        printf("\n");
        printf("    1- pi\n");
        printf("    2- matrix\n");
        printf("    3- hardware\n");
        printf("    4- Salir\n");
        printf("\n");
        printf("Ingrese una opción:  ");
        scanf("%d", &opcion); // pide al usuario que ingrese lo que desea hacer
        printf("\n");

        switch (opcion) {
            case 1:
                printf("Opcion 1\n");
                
                break;
                
            case 2:
                printf("Opcion 2\n");
                
                break;
                
            case 3:
                printf("Opcion 3\n");
                            
                break;

            case 4:
            	printf("Fin de la ejecución\n");       
                break;
        }  

        printf("\n");

        sleep(2); // espera 2 segundos

    }
    while (opcion!=4);    // ejecuta el do hasta que la variable opcion no sea 4
    
}