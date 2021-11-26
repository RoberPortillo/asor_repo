#include <stdio.h>
#include <signal.h>

volatile int CANCELAR = 0;

void manejador(int sig){

    if(sig == SIGUSR1)
        CANCELAR = 1;
}

int main(int argc, char *argv[]){

    if(argc != 2){
        printf("Error el programa recibe el numero de segundos antes de autodestruirse\n");
        return 0;
    }

    sigset_t conjunto;
    struct sigaction accion;

    sigemptyset(&conjunto);
    sigaddset(&conjunto, SIGUSR1);
    sigprocmask(SIG_UNBLOCK, &conjunto, NULL);

    sigaction(SIGUSR1, NULL, &accion);
    accion.sa_handler = manejador;
    sigaction(SIGUSR1, &accion, NULL);


    sleep(atoi(argv[1]));

    if(CANCELAR)
        printf("El programa no se borrara\n");
    else{
        printf("El programa va a borrarse\n");
        remove(argv[0]);
    }

    return 0;
}