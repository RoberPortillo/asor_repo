#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <pwd.h>

int main(){

    int real = getuid(), effective = geteuid();

    printf("Real uid: %d\n", real);
    printf("Effective uid: %d\n", effective);

    if(real == effective)
        printf("Setuid flag is set to true\n");
    else
        printf("Setuid flag is set to false\n");

    struct passwd *res;

    if((res = getpwuid(effective)) == NULL){
        perror("Error en getpwuid");
        return 1;
    }

    printf("User name: %s\n",res->pw_name);
    printf("Home directory: %s\n",res->pw_dir);
    printf("User description: %s\n",res->pw_gecos);

    return 0;
}