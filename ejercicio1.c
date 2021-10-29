#include <stdio.h>
#include <unistd.h>

int main(){
    
    if(setuid(0) == -1){
        perror("Error in setuid");
        return 1;
    }

    return 0;
}