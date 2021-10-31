#include <time.h>
#include <stdio.h>
#include <stdlib.h>

int main(){

    int i;
    struct timeval *tv1 = malloc(sizeof(struct timeval)), *tv2 = malloc(sizeof(struct timeval));

    if(gettimeofday(tv1, NULL) == -1){
        perror("Error en gettimeofday");
        return 1;
    }

    for(i = 0; i < 1000000; i++);
        
    if(gettimeofday(tv2, NULL) == -1){
        perror("Error en gettimeofday");
        return 1;
    }

    printf("Loop took %ld microseconds\n", (tv2->tv_usec - tv1->tv_usec));

    free(tv1);
    free(tv2);

    return 0;
}