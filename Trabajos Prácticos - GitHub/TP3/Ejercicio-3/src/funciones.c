#include "funciones.h"

void error(char *msg) {
    printf("%s\n\n", msg);
}

void crearFIFOS(char *fifoEntrada, char *fifoSalida) {
    mkfifo(fifoEntrada, 0666);
    mkfifo(fifoSalida, 0666);
}

void unlinkFIFOS(char *fifoEntrada, char *fifoSalida) {
    unlink(fifoEntrada);
    unlink(fifoSalida);
}

void leerConsultas(char *fifoEntrada, char *fifoSalida) {
    int fifoLectura;
    char consulta[TAM_BUFFER];
    //Abrimos el archivo de articulos, lo abrimos aca para
    //no tener que estar abriendolo y cerrandolo en cada ciclo del while
    FILE * arch = abrirArchivo("articulos.txt");

    //Abrimos el pipe de entrada
    fifoLectura = open(fifoEntrada, O_RDWR);

    while (1) {
        read(fifoLectura, consulta, sizeof(consulta));
        procesarConsulta(consulta, fifoSalida, arch);
        //write(fifoLectura, '\0', sizeof(char));
    }

    fclose(arch);
    close(fifoLectura);
    unlinkFIFOS(fifoEntrada, fifoSalida);
}

void procesarConsulta(char *consulta, char *fifoSalida, FILE * arch) {
    //Rebobinamos fd del archivo para que apunte a la primera posicion
    fseek(arch, 0, SEEK_SET);

    char linea[TAM_BUFFER], *campo;
    // Obtenemos el nombre de la columna que estamos buscando (id, nombre, etc)
    // Recordar que campo se asigna con un malloc
    campo = obtenerCampo(consulta);

    // Abrimos el pipe de escritura
	int pipeEscritura = open(fifoSalida, O_WRONLY);
    printf("CONSULTA: %s\n", consulta);
    // Si existe el campo buscado...
    if (campo) {   	
	    // Leemos la primera linea del archivo de datos
	    fgets(linea, TAM_BUFFER, arch);    
	    // Hallamos la posicion en la que se encuentra la columna
	    int columna = hallarPosicionColumna(linea, campo);

	    // Si la posicion es menor que 0, quiere decir que no existe la columna 
        // cosa que no va a pasar nunca... por que si encontraste el campo...
        /*
	    if (columna < 0) {
	        error("No se halló la columna especificada.");
	        exit(1);
	    }*/

	    //Liberamos la memoria que asignamos anteriormente, ya no nos sirve mas
	    free(campo);

	    // Obtenemos el valor de lo que estamos buscando en sí (nombre de articulo, etc)
	    char *buscado = obtenerBuscado(consulta);

        //Recorremos el archivo en busca de coincidencias
        recorrerArchivo(arch, linea, buscado, columna, pipeEscritura);

	    //Liberamos la memoria
	    free(buscado);
    } else {
        //Se recibio una consulta con campo erróneo, lo escribimos
        const char errCons[] = "La consulta posee un formato erróneo. Inténtelo de nuevo.";
        printf("%s\n", errCons);
        write(pipeEscritura, errCons, sizeof(errCons));
    }

    //Para que el otro proceso deje de leer el pipe y salga
    write(pipeEscritura, "null\0", sizeof(char)*5);
    close(pipeEscritura);
}

FILE * abrirArchivo(char *path) {
    FILE * arch = fopen(path, "r");

    if (!arch) {
        error("No se pudo abrir el archivo que contiene los datos.");
        exit(1);
    }

    return arch;
}

void recorrerArchivo(FILE * arch, char *linea, char *buscado, int columna, int pipeEscritura) {
    // Leemos otra linea del archivo      
    fgets(linea, TAM_BUFFER, arch);

    int bool_seHalloCoincidencia = 0;    
    
    while (!feof(arch)) {
        if (buscarCoincidencia(linea, columna, buscado) == 1)
        {
            write(pipeEscritura, linea, TAM_BUFFER);
            printf("Se encontró un registro coincidente.\n");
            bool_seHalloCoincidencia = 1;
        }
        fgets(linea, TAM_BUFFER, arch);
    }

    if (bool_seHalloCoincidencia)         
            bool_seHalloCoincidencia = 0;
    else 
    {
        const char errNoCoinc[] = "No se hallaron coincidencias para la consulta.";
        write(pipeEscritura, errNoCoinc, sizeof(errNoCoinc));
        printf("%s\n", errNoCoinc);
    }
}

int buscarCoincidencia(char *linea, int columna, char *buscado) {
    char *puntoPartida, *delimitadorActual, *ultPos = linea;

    int cantSaltos = columna+1;
    
    while (cantSaltos > 0) {
        puntoPartida = ultPos;
        delimitadorActual = strchr(puntoPartida, ';');
        // Cuando lleguemos a la ultima columna, no va a encontrar ningun delimitador, tenemos que evitar eso
        if (delimitadorActual)
                ultPos = delimitadorActual+1;
        cantSaltos--;
    }

    char delim = ';';
    if (!delimitadorActual) {
        delimitadorActual = strchr(puntoPartida, '\n');
        delim = '\n';
    }
    
    *delimitadorActual = '\0';

    if (strcmp(puntoPartida, buscado) == 0)
    {
        *delimitadorActual = delim;
        return 1;

    }
    else
        return 0;
}

// Obtiene el campo (columna) que se pide en la consulta 
char * obtenerCampo(char *buffer) {
    char *aux;
    char *campo = malloc(sizeof(char)*64);

    aux = strchr(buffer, '=');
    if (aux) {
        *aux = '\0';
        strcpy(campo, buffer);
        *aux = '=';
    } else {
        //error("La consulta tiene errores o no respeta el formato adecuado.");
        //exit(1);
        free(campo);
        return NULL;
    }

    return campo;    
}

// Obtiene aquello que se está buscando
char * obtenerBuscado(char *buffer) {
    char *aux;
    char *buscado = malloc(sizeof(char)*256);

    aux = strchr(buffer, '=');
    strcpy(buscado, aux+1);
    return buscado;    
}

// Identifica en qué posición se encuentra el campo en el archivo de texto
int hallarPosicionColumna(char *linea, char *campo) {
    int i = 0;
    char *aux, *puntoPartida = linea;
    
    aux = strchr(puntoPartida, ';');
    while (aux) {       
        *aux = '\0';

        if (strcmp(puntoPartida, campo) == 0) {
            return i;
        }

        puntoPartida = aux+1;
        i++; 
        aux = strchr(puntoPartida, ';');       
    }
    
    //Si salimos del while, tenemos que fijarnos si llegamos a la ultima columna (no tiene delimitador, es laultima)
    aux = strchr(puntoPartida, '\n');
    if (aux) {        
        *aux = '\0';

        if (strcmp(puntoPartida, campo) == 0) {
            return i;
        }
    }

    return -1;
}

void ayuda() {
    printf("\n\n");
    printf("Este programa crea dos FIFOS (named pipes) los cuales serán\n");
    printf("usados para procesar consultas hacia un archivo que contiene datos.\n");
    printf("El programa queda demonizado a la espera de consultas para resolver.\n");
    printf("Recibe como parámetros las rutas (con nombre) de los FIFOS a crear.\n\n");
    printf("Sintaxis de ejecución: \n");
    printf("./ejercicio3 <ruta fifo entrada> <ruta fifo salida>\n");
    printf("Ejemplo de ejecución: \n");
    printf("./ejercicio3 /home/usuario/entrada /home/usuario/salida\n");
}