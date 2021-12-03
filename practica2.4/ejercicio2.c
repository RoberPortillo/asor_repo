#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[]){

    int p_h[2], h_p[2], bytes_readed;
    char buffer[255];

    if(pipe(p_h) == -1 || pipe(h_p) == -1){
        perror("Error en la llamada a pipe");
        return 1;
    }

    switch(fork()){

        case -1:
            perror("Error en la llamada a fork");
            return 1;

        case 0:
            // Proceso hijo
            close(p_h[1]);
            close(h_p[0]);
            int i;
            for(i = 0; i < 10; i++){

                bytes_readed = read(p_h[0], buffer, 255);
                buffer[bytes_readed] = '\0';
                printf("HIJO Mensaje recibido %s\n", buffer);
                sleep(1);
                if(i == 9)
                    write(h_p[1], "q", 1);
                else
                    write(h_p[1], "l", 1);
            }

            close(p_h[0]);
            close(h_p[1]);
            break;

        default:
            // Proceso padre
            close(p_h[0]);
            close(h_p[1]);

            while(buffer[0] != 'q'){

                printf("Input:\n");
                scanf("%s", buffer);
                write(p_h[1], buffer, strlen(buffer) + 1);
                read(h_p[0], buffer, 1);
            }

            printf("Se han leido los 10 mensajes.\n");

            close(p_h[1]);
            close(h_p[0]);
            break;
    }

    return 0;
}