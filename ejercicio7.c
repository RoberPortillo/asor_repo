#include <stdio.h>
#include <unistd.h>
#include <errno.h>

int main(){

    int parametros[3] = {_PC_LINK_MAX, _PC_PATH_MAX, _PC_NAME_MAX};
    const char *msg[3] = {"Links limit: ", "Path length limit: ", "File's name length limit: "};
    const char *names[3] = {"LINK_MAX", "PATH_MAX", "NAME_MAX"};

    long res;
    int i;
    for(i = 0; i < 3; i++){

        if((res = pathconf("/", parametros[i])) == -1){

            if(errno == 0)
                printf("No limit for %s\n", names[i]);
            else{
                perror("Error en pathconf");
                return 1;
            }
        }

        printf("%s%ld\n", msg[i], res);
    }

    return 0;
}