#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <locale.h>

int main(){

    time_t *seconds = malloc(sizeof(time_t));
    char *buffer = malloc(60);
    struct tm *lTime;

    time(seconds);
    lTime = localtime(seconds);

    setlocale(LC_ALL, "es_ES");
    strftime(buffer, 60, "%A, %d de %B de %Y, %H:%M", lTime);

    printf("%s\n", buffer);

    free(seconds);
    free(buffer);

    return 0;
}