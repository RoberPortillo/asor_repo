#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char *argv[]){

    pid_t mainPid;
    int fdOut, fdErr, fdIn;

    if((mainPid = fork()) == -1){
        perror("Error en fork");
        return 1;
    }

    if(mainPid == 0){
        // Proceso hijo (demonio)

        // Abre los ficheros necesarios
        if((fdOut = open("/tmp/daemon.out", O_WRONLY | O_TRUNC | O_CREAT, 0666)) == -1){
        perror("Error al abrir daemon.out");
        return 1;
        }

        if((fdErr = open("/tmp/daemon.err", O_WRONLY | O_TRUNC | O_CREAT, 0666)) == -1){
            perror("Error al abrir daemon.err");
            return 1;
        }

        if((fdIn = open("/dev/null", O_RDONLY | O_TRUNC | O_CREAT, 0666)) == -1){
            perror("Error al abrir /dev/null");
            return 1;
        }

        // Redirige las salidas y entradas standar a estos ficheros
        if(dup2(fdOut, STDOUT_FILENO) == -1){
            perror("Error al redirigir a stdout");
            return 1;
        }

        if(dup2(fdErr, STDERR_FILENO) == -1){
            perror("Error al redirigir stderr");
            return 1;
        }

        if(dup2(fdIn, STDIN_FILENO) == -1){
            perror("Error al redirigir stdin");
            return 1;
        }

        // Ejecuta el comando recibido por argumento
        char *argumentos[argc-1];

        int i;
        for(i = 1; i < argc; i++)
            argumentos[i-1] = argv[i];

        if(execvp(argv[1], argumentos) == -1){
            perror("Error al ejecutar el programa");
            return 1;
        }

        close(fdOut);
        close(fdErr);
        close(fdIn);
    }

    return 0;
}