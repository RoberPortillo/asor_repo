#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

int main(){

    if(setuid(0) == -1){
        printf("Error number: %d\nDescription: %s", errno, strerror(errno));
        return 1;
    }

    return 0;
}