#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(){

    umask(0026);

    if(open("ficheroEj8", O_CREAT, 0666) == -1){
        perror("Error en open");
        return 1;
    }

    return 0;
}