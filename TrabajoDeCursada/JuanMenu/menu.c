#include <stdio.h>
#include <stdlib.h>  // para usar el system
#include <unistd.h>  //  para usar el sleep

void menu_nivel_1();
int menu_nivel_2();
int pedirStep();
int pedirTamMatrix();

int main(){

    menu_nivel_1();
    
    return 0;
}

void menu_nivel_1(){

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
            case 1:  // pi

                int opcion_1;
                do
                {
                    opcion_1 = menu_nivel_2();
                switch (opcion_1)
                {
                case 1:
                case 2:
                    int numStep1 = pedirStep();
                    //ejecuto algoritmo de pi con el parametro numstep, paramentro de reducion o no
                break;
                }
                } while (opcion_1 != 3);
            
                break;
                
            case 2:
                
                int opcion_2;
                do
                {
                    opcion_2 = menu_nivel_2();
                switch (opcion_2)
                {
                case 1:
                case 2:
                    int n = pedirTamMatrix();
                    break;
                     //ejecuto algoritmo de mtrix con el parametro n y bollean reducion
                }
                } while (opcion_2 != 3);
            
                break;
                
            case 3:
                printf("Opcion 3\n");
                    printf("\n");  
                    printf("Aca se describe el harware de la compu:\n"); // datos del cpu
                    printf("\n");  
                    sleep(1);
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

int menu_nivel_2(){
    int opcion;
    system("clear"); // limpia la pantalla

    printf("\n");
    printf("Que tipo de paralelismo desea usar:\n");
    printf("\n");
    printf("    1- sin reduccion\n");
    printf("    2- con reduccion\n");
    printf("    3- atras\n");
    printf("\n");
    printf("Ingrese una opción:  ");
    scanf("%d", &opcion); // pide al usuario que ingrese lo que desea hacer
    printf("\n");
    return opcion;
}

int pedirStep(){
    int step;
    printf("\n");
    printf("Ingresa numero de step:\n");
    printf("\n");
    scanf("%d", &step);   
    return step;
}

int pedirTamMatrix(){
    int n;
    printf("\n");
    printf("Ingresa tamaño de matriz:\n");
    printf("\n");
    scanf("%d", &n);   
    return n;
}