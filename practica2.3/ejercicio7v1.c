#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){

    if(argc != 2){
        printf("Error: El programa recibe un comando con sus argumentos en forma de un unico string\n");
        return 1;
    }

    if(system(argv[1]) == -1){
        perror("Error en la llamada al sistema");
        return 1;
    }

    printf("El comando termino de ejecutarse\n");

    return 0;
}