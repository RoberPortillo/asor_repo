#include <stdio.h>
#include <unistd.h>
#include <string.h>


int main(){

    int parameters[3] = {_SC_ARG_MAX, _SC_CHILD_MAX, _SC_OPEN_MAX};
    const char *msg[3] = {"Arguments max length: ", "Max number of childs: ", "Max number of files: "};

    long res;
    int i;
    for(i = 0; i < 3; i++){

        res = sysconf(parameters[i]);

        if(res == -1){
            perror("Error in sysconf");
            return 1;
        }
        
        printf("%s%ld\n", msg[i], res);
    }

    return 0;
}