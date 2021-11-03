#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(){

    if(open("ficheroEj6", O_CREAT, 0645) == -1){
        perror("Error en open");
        return 1;
    }

    return 0;
}