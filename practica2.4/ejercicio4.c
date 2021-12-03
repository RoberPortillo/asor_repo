#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, char *argv[]){

    if(argc != 2){
        printf("El programa recibe un argumento.\n");
        return 1;
    }

    int fd;

    if((fd = open("/tmp/fifo", O_WRONLY)) == -1){
        perror("Error en open");
        return 1;
    }

    if(write(fd, argv[1], strlen(argv[1])) == -1){
        perror("Error en write");
        return 1;
    }

    close(fd);

    return 0;
}