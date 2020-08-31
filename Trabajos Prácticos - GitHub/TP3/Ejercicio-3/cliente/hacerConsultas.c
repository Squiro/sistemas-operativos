#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void main(int argc, char *argv[]) {
    int pipeEscritura = open("../fifoEntrada", O_WRONLY);
    //char busqueda[] = "MARCA=MAROLIO";
    printf("CONSULTA ENVIADA: %s\n", argv[1]);
    write(pipeEscritura, argv[1], strlen(argv[1]));
    close(pipeEscritura);
}