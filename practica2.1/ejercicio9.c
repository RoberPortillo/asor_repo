#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>

int main(){

    int real = getuid(), effective = geteuid();

    printf("Real uid: %d\n", real);
    printf("Effective uid: %d\n", effective);

    if(real == effective)
        printf("Setuid flag is set to true\n");
    else
        printf("Setuid flag is set to false\n");

    return 0;
}