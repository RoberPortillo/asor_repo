#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>

int main(int argc, char *argv[]){

    struct stat stats;

    // Comprueba error en los argumentos del sistema
    if(argc != 2){
        printf("Error: La aplicación requiere de una ruta como argumento\n");
        return 1;
    }

    // Llamada a stat para obtener las propiedades del archivo
    if(stat(argv[1], &stats) == -1){
        perror("Error en stat");
        return 1;
    }

    // Muestra el major y minor del dispositivo
    printf("Numero major: %d\n", major(stats.st_dev));
    printf("Numero minor: %d\n", minor(stats.st_dev));
    printf("I-nodo: %d\n", stats.st_ino);

    // Comprueba el tipo de fichero filtrando el modo con las mascara S_IFMT
    switch(stats.st_mode & S_IFMT){

        case S_IFDIR:
            printf("El fichero es un directorio\n");
            break;
        case S_IFLNK:
            printf("El fichero es un enlace simbolico\n");
            break;
        case S_IFREG:
            printf("El fichero es regular\n");
            break;
        default:
            printf("El fichero es de otro tipo\n");
            break;
    }   

    // Ultima modificacion del archivo. ctime marcaria la ultima modificación del inodo
    printf("Ultima modificacion: %d\n", stats.st_mtime);

    return 0;
}