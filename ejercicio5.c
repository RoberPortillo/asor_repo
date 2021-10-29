#include <sys/utsname.h>
#include <stdio.h>
#include <stdlib.h>

int main(){

    struct utsname *buffer = malloc(sizeof(struct utsname));

    if(uname(buffer) == -1){
        
        perror("Error in uname");
        return 1;
    }

    printf("SO name: %s\n", buffer->sysname);
    printf("Host name: %s\n", buffer->nodename);
    printf("SO release: %s\n", buffer->release);
    printf("SO version date: %s\n", buffer->version);
    printf("Hardware: %s\n", buffer->machine);
    printf("Domain name: %s\n", buffer->__domainname);

    free(buffer);

    return 0;
}