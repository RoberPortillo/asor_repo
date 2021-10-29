#include <stdio.h>
#include <string.h>

int main(){

    int i;
    for(i = 1; i <= 255; i++){
        printf("%s\n", strerror(i));
    }

    return 0;
}