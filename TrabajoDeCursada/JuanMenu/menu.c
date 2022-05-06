#include <stdio.h>
#include <stdlib.h>


int main(){

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
                printf("Instrucciones de la opcion 1\n");
                
                break;
                
            case 2:
                printf("Instrucciones de la opcion 2\n");
                
                break;
                
            case 3:
                printf("Instrucciones de la opcion 3\n");
                            
                break;

            case 4:
            	printf("Fin de la ejecución\n");       
                break;
        }  

    }
    while (opcion!=4);    // ejecuta el do hasta que la variable opcion no sea 4
    
    return 0;
}

/*
public static void menu(AnalizadorLexico al, Parser p, ConversorTercetoAssembler c) throws InterruptedException {
        int opcion ;
        Scanner s = new Scanner (System.in);
        do {
            System.out.println("\n");
            System.out.println("Elija una opcion del menu:");
            System.out.println("0- Imprimir codigo");
            System.out.println("1- Listar tabla de simbolos");
            System.out.println("2- Listar errores");
            System.out.println("3- Listar tercetos");
            System.out.println("4- Generar y mostrar el archivo assembler");
            System.out.println("5- Salir");
            System.out.println("Ingrese una opción");
            opcion = s.nextInt();
            switch (opcion) {
                case 0: {
                    al.imprimirCodigo();
                    break;
                }

                case 1: {
                    al.getTablaSimbolo().imprimirTabla();
                    break;
                }

                case 2: {
                    al.imprimirWarningsLexicos();         // caso de que un identificador se pase de los 22 caractenes
                    p.imprimirWarningsSemanticos();       // caso en el que se redeclara con el mismo nombre de variables
                    al.imprimirErroresLexicos();          // un error de caracter invalido o que se pase de rango los numeros
                    p.imprimirErroresSintacticos();
                    p.imprimirErroresSemanticos();
                    break;
                }
    sleep(2000);
        } while ( opcion != 5);
    }
*/