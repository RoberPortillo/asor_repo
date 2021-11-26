#include <stdio.h>
#include <sched.h>
#include <sys/types.h>
#include <unistd.h>

int main(){

    int pol = sched_getscheduler(0);
    struct sched_param param;

    switch(pol){

        case SCHED_OTHER:
            printf("Planificador estadar\n");
            break;
        case SCHED_FIFO:
            printf("Planificador fifo\n");
            break;
        case SCHED_RR:
            printf("Planificador Round Robin\n");
            break;
        default:
            perror("Error al comprobar el planificador");
            return 1;
    }

    if(sched_getparam(0, &param) == -1){
        perror("Error al comprobar la prioridad");
        return 1;
    }
    
    printf("La prioridad es %d\n", param.sched_priority);
    printf("Prioridad maxima: %d\n", sched_get_priority_max(pol));
    printf("Prioridad minima: %d\n", sched_get_priority_min(pol));

    return 0;
}