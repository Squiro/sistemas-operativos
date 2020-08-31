#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void main(int argc, char *argv[]) {
    int w = open("../fifoSalida", O_RDONLY);
    char busqueda[256];

    read(w, busqueda, sizeof(busqueda));

    while (strcmp(busqueda, "null") != 0) {
    	printf("%s\n", busqueda);
    	read(w, busqueda, sizeof(busqueda));    	
    }    
}