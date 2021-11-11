#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <limits.h>
#include <stdlib.h>


int main(int argc, char *argv[]){

    // Comprueba que recibe el numero correcto de argumentos
    if(argc != 2){
        printf("Error: El programa recibe la ruta de un directorio como argumento.\n");
        return 1;
    }

    DIR *dp;
    struct dirent *entrada;

    /* 
       Abre el directorio, en caso de que no sea un directorio
       el programa acaba
    */
    if((dp = opendir(argv[1])) == NULL){
        perror("Error en opendir");
        return 1;
    }

    char *path_link = malloc(PATH_MAX);
    char *file = malloc(30);
    struct stat stats;
    int fileType, nBytes = 0;

    // Recorre todas las entradas del directorio
    while((entrada = readdir(dp)) != NULL){

        // Formatea la ruta a cada entrada del directorio
        if(sprintf(file, "%s/%s", argv[1], entrada->d_name) == -1){
            printf("Error al formatear la ruta\n");
            return 1;
        }

        // Llama a lstat con la entrada del directorio
        if(lstat(file, &stats) == -1){
            perror("Error en stat");
            return 1;
        }

        switch(stats.st_mode & S_IFMT){

            // Si es directorio lo muesta con / delante
            case S_IFDIR:
                printf("/%s\n", entrada->d_name);
                break;
            // Si es link llama a readlink y lo muesta con ->
            case S_IFLNK:
                readlink(file, path_link, PATH_MAX);
                printf("%s->%s\n", entrada->d_name, path_link);
                nBytes += stats.st_size;
                break;
            /* Si es regular lo muestra con * detras solo si
               es ejecutable*/
            case S_IFREG:
                if(stats.st_mode & S_IXUSR)
                    printf("%s*\n", entrada->d_name);
                else
                    printf("%s\n", entrada->d_name);
                nBytes += stats.st_size;
                break;
            // Ficheros de otro tipo
            default:
                printf("El fichero es de otro tipo\n");
                break;
        } 
    }

    // Muestra el tamaño del directorio
    printf("El directorio contiene %d kilobytes\n", nBytes/1000);

    // Libera la memoria reservada
    free(path_link);
    free(file);

    return 0;
}