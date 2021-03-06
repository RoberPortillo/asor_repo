#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

int main(int argc, char *argv[]){

    if(argc != 2){
        printf("Error: El programa requiere un nombre de fichero como argumento\n");
        return 1;
    }

    int fd = open(argv[1], O_WRONLY | O_CREAT, 0666);

    if(fd == -1){
        perror("Error al abrir el fichero");
        return 1;
    }

    if(dup2(fd, STDOUT_FILENO) == -1){
        perror("Error en dup2");
        return 1;
    }

    if(close(fd) == -1){
        perror("Error en close");
        return 1;
    }

    printf("Esto es una prueba del programa que redirecciona la salida standar a este fichero\n");

    return 0;
}