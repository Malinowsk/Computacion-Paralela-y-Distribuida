#include <stdio.h>
#include <stdlib.h>  // para usar el system
#include <unistd.h>  //  para usar el sleep

void menu();
int menu_nivel_2();

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
            case 1:  // pi

                int opcion_1;
                do
                {
                    opcion_1 = menu_nivel_2();
                switch (opcion_1)
                {
                case 1:
                    int numStep1;
                    printf("\n");
                    printf("Ingresa numero de step:\n");
                    printf("\n");
                    scanf("%d", &numStep1);
                    //ejecuto algoritmo de pi con el parametro numstep
                    break;
                
                case 2:
                    int numStep2;
                    printf("\n");
                    printf("Ingresa numero de step:\n");
                    printf("\n");
                    scanf("%d", &numStep2);
                    break;
                     //ejecuto algoritmo de pi con el parametro numstep // caso 1 y 2 se juntan
                }
                } while (opcion_1 != 3);
            
                break;
                
            case 2:
                
                int opcion_3;
                do
                {
                    opcion_3 = menu_nivel_2();
                switch (opcion_3)
                {
                case 1:
                    int n1;
                    printf("\n");
                    printf("Ingresa el tamaño de la matriz:\n");
                    printf("\n");
                    scanf("%d", &n1);
                    //ejecuto algoritmo de pi con el parametro numstep
                    break;
                
                case 2:
                    int n2;
                    printf("\n");
                    printf("Ingresa el tamaño de la matriz:\n");
                    printf("\n");
                    scanf("%d", &n2);
                    break;
                     //ejecuto algoritmo de pi con el parametro numstep // caso 1 y 2 se juntan
                }
                } while (opcion_1 != 3);
            
                break;
                
            case 3:
                printf("Opcion 3\n");
                    printf("\n");  
                    printf("Aca se describe el harware de la compu:\n");
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