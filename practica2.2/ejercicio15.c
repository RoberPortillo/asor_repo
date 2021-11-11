#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <fcntl.h>
#include <stdlib.h>

int main(int argc, char *argv[]){

    // Comprueba que el programa reciba un argumento
    if(argc != 2){
        printf("Error: El programa debe recibir un nombre de fichero como argumento\n");
        return 1;
    }

    int fd;
    
    // Abre el fichero comprobando posibles errores
    if((fd = open(argv[1], O_WRONLY | O_TRUNC | O_CREAT, 0666)) == -1){
        perror("Error al abrir el fichero");
        return 1;
    }

    // Activa el candado del fichero comprobando errores
    if(lockf(fd, F_TLOCK, 0) == -1){
        perror("Error en lock");
        return 1;
    }

    // Escribe la hora actual en el fichero
    time_t *seconds = malloc(sizeof(time_t));
    char *buffer = malloc(6);
    struct tm *lTime;

    time(seconds);
    lTime = localtime(seconds);

    /* 
       En caso de error al formatear el mensaje
       o escribir en el fichero muestra el error, 
       libera la memoria reservada, suelta el 
       candado y termina la ejecucion.
    */
    if(sprintf(buffer, "%d:%d\n", lTime->tm_hour, lTime->tm_min) == -1){
        printf("Error al formatear el string\n");
        free(seconds);
        free(buffer);
        return 1;
    }

    if(write(fd, buffer, sizeof(buffer)) == -1){
        perror("Error en write");
        lockf(fd, F_ULOCK, 0);
        free(seconds);
        free(buffer);
        return 1;
    }

    // Duerme el proceso 30 segundos
    sleep(30);

    // Suelta el candado
    lockf(fd, F_ULOCK, 0);

    // Libera la memoria reservada
    free(seconds);
    free(buffer);

    return 0;
}