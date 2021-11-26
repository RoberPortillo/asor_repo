#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]){

    char *argumentos[argc-1];

    int i;
    for(i = 1; i < argc; i++)
        argumentos[i-1] = argv[i];
        
    if(execvp(argv[1], argumentos) == -1){
        perror("Error al ejecutar el programa");
        return 1;
    }

    printf("El comando termino de ejecutarse\n");

    return 0;
}