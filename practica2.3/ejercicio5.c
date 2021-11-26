#include <unistd.h>
#include <stdio.h>
#include <sys/resource.h>
#include <linux/limits.h>

int main(){

    pid_t pid, ppid, pgid, sid;
    struct rlimit limit;
    char buffer[PATH_MAX];


    pid = getpid();
    ppid = getppid();

    if((pgid = getpgid(0)) == -1){
        perror("Error al obtener pgid");
        return 1;
    }

    if((sid = getsid(0)) == -1){
        perror("Error al obtener sid");
        return 1;
    }

    if(getrlimit(RLIMIT_NOFILE, &limit) == -1){
        perror("Error al comprobar el numero de ficheros");
        return 1;
    }

    if(getcwd(buffer, sizeof(buffer)) == NULL){
        perror("Error al comprobar el directorio");
        return 1;
    }

    printf("Pid: %d\n", pid);
    printf("Ppid: %d\n", ppid);
    printf("Pgid: %d\n", pgid);
    printf("Sid: %d\n", sid);

    printf("Numero maximo de ficheros que puede abrir: %d\n", limit.rlim_max);

    printf("Directorio actual: %s\n", buffer);


    return 0;
}