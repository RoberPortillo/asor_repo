#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[]){

    // Comprueba que los argumentos del programa sean correctos
    if(argc != 2){
        printf("Error: El programa recibe el nombre de un fichero como argumento\n");
        return 1;
    }

    // Reserva memoria para el nombre de los enlaces
    char *sym = malloc(sizeof(argv[1]) + 4);
    char *hard = malloc(sizeof(argv[1]) + 5);

    // Copia el titulo del fichero y añade la extension de los enlaces
    sym = strcat(strcpy(sym, argv[1]), ".sym");
    hard = strcat(strcpy(hard, argv[1]), ".hard");

    // Crea el enlace simbolico comprobando posibles errores
    if(link(argv[1], hard) == -1){
        perror("Error en link");
        return 1;
    }

    // Crea el enlace rigido comprobando posibles errores
    if(symlink(argv[1], sym) == -1){
        perror("Error en symlink");
        return 1;
    }

    return 0;
}