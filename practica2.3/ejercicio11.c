#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

int main(){

    sigset_t bloqueadas, pendientes;

    char *sleep_secs = getenv("SLEEP_SECS");

    if(sleep_secs == NULL){
        printf("Error no encuentra la variable\n");
        return 1;
    }

    sigemptyset(&bloqueadas);
    sigaddset(&bloqueadas, SIGINT);
    sigaddset(&bloqueadas, SIGTSTP);

    sigprocmask(SIG_BLOCK, &bloqueadas, NULL);

    sleep(atoi(sleep_secs));

    sigpending(&pendientes);

    if(sigismember(&pendientes, SIGINT)){
        printf("SIGINT recibida\n");
        sigdelset(&bloqueadas, SIGINT);
    }
    else
        printf("SIGINT no recibida\n");

    if(sigismember(&pendientes, SIGTSTP)){
        printf("SIGTSTP recibida\n");
        sigdelset(&bloqueadas, SIGTSTP);
    }
    else
        printf("SIGTSTP no recibida\n");

    sigprocmask(SIG_UNBLOCK, &bloqueadas, NULL);

    return 0;
}