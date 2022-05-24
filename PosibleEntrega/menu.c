#include <stdio.h>
#include <stdlib.h>  // para usar el system
#include <unistd.h>  //  para usar el sleep
#include <string.h>
#include "pi.h"
#include "matrix.h"

void menu_nivel_1();
int menu_nivel_2();
int getStep();
int getSizeMatrix();

int main(){

    menu_nivel_1();
    
    return 0;
}

void menu_nivel_1(){

    int option ;    
    

    do {
        system("clear"); // Limpia la Pantalla

        printf("\n");
        printf("Elija una opcion del menu:\n");
        printf("\n");
        printf("    1- Calculo de Pi\n");
        printf("    2- Multiplicacion de Matrices\n");
        printf("    3- Hardware del CPU y SO\n");
        printf("    4- Salir\n");
        printf("\n");
        printf("Ingrese una opción:  ");
        scanf("%d", &option); // Pide al usuario que ingrese lo que desea hacer
        printf("\n");

        switch (option) {
            case 1:  // pi
            {
                int option_1;
                do
                {
                    option_1 = menu_nivel_2();
                switch (option_1)
                {
                case 1:
                case 2:
                   { 
                      int numStep1 = getStep();
                      pi(numStep1,option_1);
                      getchar();
                   }
                break;
                }
                } while (option_1 != 3);
            
            break;
            }   
            case 2:
            {    
                int option_2;
                do
                {
                    option_2 = menu_nivel_2();
                switch (option_2)
                {
                case 1:
                case 2:
                  {
                    int n = getSizeMatrix();
                    matrix(n,option_2); 
                    getchar();
                    break;
                  }
                }
                } while (option_2 != 3);
            
            break;
            }    
            case 3:
            {       
                    system("clear"); // Limpia la Pantalla

                    printf("\n");
                    printf("\n");  
                    printf("\e[38;2;255;0;0m\e[3mDescripción del hardware de la CPU:\e[0m\n\n"); // datos del cpu
                    printf("\n");  
                    system("""lscpu | head -n $(lscpu | grep -n Bogo | cut -d \":\" -f 1)""");

                    printf("\n");  
                    printf("\n");  
                    printf("\e[38;2;255;0;0m\e[3mDescripción del SO:\e[0m\n\n"); // datos del so
                    printf("\n");  
                    system("cat /etc/*release | head -n $(cat /etc/*release | grep -n ID_LIKE | cut -d \":\" -f 1)");

                    
                    getchar();
                    
                    printf("\n"); 

                    sleep(1);

                    printf("\n"); 
                    printf("\e[38;2;0;0;255m\e[3mContinuar...\e[0m");
                    getchar();
                    
            break;
            }
            case 4:
            {	printf("Fin de la ejecución\n");       
                break;
            }
        }  

        printf("\n");

        sleep(1); // Espera 2 segundos

    }
    while (option!=4);    // Ejecuta el do-while hasta que la variable option no sea 4
    
}
int menu_nivel_2(){
    int option;
    system("clear"); // Limpia la Pantalla

    printf("\n");
    printf("Que tipo de paralelismo desea usar:\n");
    printf("\n");
    printf("    1- Sin reduccion\n");
    printf("    2- Con reduccion\n");
    printf("    3- Atras\n");
    printf("\n");
    printf("Ingrese una opción:  ");
    scanf("%d", &option); // Pide al usuario que ingrese lo que desea hacer
    printf("\n");
    return option;
}

int getStep(){
    system("clear"); // Limpia la Pantalla
    int step;
    printf("\n");
    printf("Ingresa numero de step:\n");
    printf("\n");
    scanf("%d", &step);
    system("clear"); // Limpia la Pantalla   
    return step;
}

int getSizeMatrix(){
    system("clear"); // Limpia la Pantalla
    int n;
    printf("\n");
    printf("Ingresa tamaño de matriz:\n");
    printf("\n");
    scanf("%d", &n);   
    system("clear"); // Limpia la Pantalla
    return n;
}
