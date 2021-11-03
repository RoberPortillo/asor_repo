#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

int main(int argc, char *argv[]){

    // Comprueba errores en los argumentos del programa
    if(argc != 2){
        printf("Error: El programa requiere un nombre de fichero como argumento\n");
        return 1;
    }

    /* Abre el fichero recibido por argumento 
    o lo crea si no existe. Sale en caso de error*/
    int fd = open(argv[1], O_WRONLY | O_CREAT, 0666);
    if(fd == -1){
        perror("Error al abrir el fichero");
        return 1;
    }

    /* Provocamos que STD_OUT sea un duplicado 
    del descriptor del fichero recibido como argumento*/
    if(dup2(fd, STDOUT_FILENO) == -1){
        perror("Error en dup2");
        return 1;
    }

    // Cerramos el descriptor original
    if(close(fd) == -1){
        perror("Error en close");
        return 1;
    }

    /* Como stdout ahora apunta a nuestro fichero, 
    la llamada printf escribira en dicho fichero en lugar de en pantalla*/
    printf("Esto es una prueba del programa que redirecciona la salida standar a este fichero\n");

    return 0;
}