#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

int main(int argc, char *argv[]){

    // Comprueba posibles errores en los argumentos del programa
    if(argc != 2){
        printf("Error: El programa requiere un nombre de fichero como argumento\n");
        return 1;
    }

    // Abre el fichero o lo crea en caso de que no exista
    int fd = open(argv[1], O_WRONLY | O_CREAT, 0666);

    // Sale en caso de error al abrir el fichero
    if(fd == -1){
        perror("Error al abrir el fichero");
        return 1;
    }

    // Hace un duplicado del descriptor del fichero en stdout
    if(dup2(fd, STDOUT_FILENO) == -1){
        perror("Error en dup2");
        return 1;
    }

    // Cierra el descriptor del fichero original
    if(close(fd) == -1){
        perror("Error en close");
        return 1;
    }

    // Hace un duplicado de stdout en stderr
    if(dup2(STDOUT_FILENO, STDERR_FILENO) == -1){
        perror("Error en dup2");
        return 1;
    }

    /*Imprime una serie de cadenas tanto en stdout
    como en stderr que se imprimiran en el fichero
    recibido como argumento */
    printf("Esto es una prueba del programa que redirecciona la salida standar a este fichero\n");
    fprintf(stderr, "Esto es una prueba del programa que redirecciona la salida de error a este fichero\n");

    return 0;
}