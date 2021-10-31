#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main(){

    struct tm *lTime;
    time_t *seconds = malloc(sizeof(time_t));

    time(seconds);

    lTime = localtime(seconds);

    free(seconds);

    printf("Year %d\n", (lTime->tm_year + 1900));

    return 0;
}