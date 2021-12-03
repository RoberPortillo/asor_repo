#include <stdio.h>
#include <unistd.h>


int main(int argc, char *argv[]){

    if(argc < 5){
        printf("El programa recibe otros dos programas como argumentos.\n");
        return 1;
    }

    int fd[2];

    if(pipe(fd) == -1){
        perror("Error en la llamada a pipe");
        return 1;
    }

    switch(fork()){

        case -1:
            perror("Error en la llamada a fork");
            return 1;
            break;

        case 0:
            // Proceso hijo
            dup2(fd[0], 0);
            close(fd[0]);
            close(fd[1]);
            execlp(argv[3], argv[3], argv[4], NULL);
            break;

        default:
            // Proceso padre
            dup2(fd[1], 1);
            close(fd[0]);
            close(fd[1]);
            execlp(argv[1], argv[1], argv[2], NULL);
            break;
    }

    return 0;
}