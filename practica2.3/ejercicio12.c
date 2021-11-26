#include <stdio.h>
#include <signal.h>

volatile int contINT = 0, contTSTP = 0;

void manejador(int sig){

    if(sig == SIGINT)
        contINT++;
    if(sig == SIGTSTP)
        contTSTP++;
}

int main(){

    struct sigaction accion;
    sigset_t signals;

    sigaction(SIGINT, NULL, &accion);
    accion.sa_handler = manejador;
    sigaction(SIGINT, &accion, NULL);
    sigaction(SIGTSTP, NULL, &accion);
    accion.sa_handler = manejador;
    sigaction(SIGTSTP, &accion, NULL);
    
    sigemptyset(&signals);

    while(contINT + contTSTP < 10)
        sigsuspend(&signals);    

    printf("\nSe han recibido SIGINT %d veces\n", contINT);
    printf("Se ha recibido SIGTSTP %d veces\n", contTSTP);

    return 0;
}