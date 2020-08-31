#include "funciones.h"

void error(char *msg) {
    printf("%s\n\n", msg);
}

// Crea area de memoria compartida
// retorna el puntero hacia la memoria
char * crearSHM(int *shmid) {
    //int shmid;
    char *memComp;

    *shmid = shmget(234, sizeof(char)*TAM_CONSULTA, IPC_CREAT | 0666);
    // Shmget asigna un espacio de memoria del sistema
    if (*shmid == -1) {
        error("Hubo un error al intentar crear el área compartida de memoria (shmget).");
        exit(1);
    }

    memComp = shmat(*shmid, NULL, 0);

    if (memComp == (void *)-1) {
        error("Hubo un error al intentar crear el área compartida de memoria (shmat).");
        exit(1);
    }

    return memComp;
}

void destruirSHM(char *memComp, int shmid) {
    if (shmdt(memComp) == -1 || shmctl(shmid, IPC_RMID, NULL) == -1) {
        error("Hubo un error al intentar destruir el área compartida de memoria.");
        exit(1);
    }

    //shmctl(shmid, IPC_RMID, NULL)
}

void leerConsultas(char *memComp) {
    // Almacenara la consulta
    char consulta[TAM_CONSULTA];

    // Argumentos: name (es un nombre que empieza con barra, no es una ruta)
    // oflag: generalmente O_CREAT para crear el semaforo
    // mode: modo de escritura, lectura, etc
    // value: valor inicial del semaforo
    sem_t *mutexMemoria = sem_open("/mutexMemoria", O_CREAT, 0666, 1);
    sem_t *hayConsulta = sem_open("/hayConsulta", O_CREAT, 0666, 0);
    sem_t *hayRespuesta = sem_open("/hayRespuesta", O_CREAT, 0666, 0);

    // Este semaforo es usado por los procesos que quieren realizar consultas
    sem_t *puedeConsultar = sem_open("/puedeConsultar", O_CREAT, 0666, 1);
    sem_t *puedeEnviar = sem_open("/puedeEnviar", O_CREAT, 0666, 1);

    if (!mutexMemoria) {
        error("Hubo un error al tratar de inicializar el semaforo.");
        exit(1);
    }        

    //Abrimos el archivo aca para no tener que estar abriendolo y cerrandolo todo el rato
    FILE * arch = abrirArchivo("articulos.txt");

    while (1) {
        //Esperamos a recibir una consulta
        sem_wait(hayConsulta);
        //Leemos la consulta de memoria
        sem_wait(mutexMemoria);
        strncpy(consulta, memComp, sizeof(consulta));
        sem_post(mutexMemoria);
        //Procesamos
        procesarConsulta(consulta, memComp, mutexMemoria, hayRespuesta, puedeEnviar, arch);
        //Volvemos a aceptar consultas
        sem_post(puedeConsultar);
    }

    fclose(arch);
    sem_close(mutexMemoria);
    sem_unlink("/mutexMemoria");
    sem_close(hayConsulta);
    sem_unlink("/hayConsulta");
}

void procesarConsulta(char *consulta, char *memComp, sem_t *mutexMemoria, sem_t *hayRespuesta, sem_t * puedeEnviar, FILE * arch) {  
    //Rebobinamos fd del archivo para que apunte a la primera posicion
    fseek(arch, 0, SEEK_SET);
    
    printf("CONSULTA: %s\n", consulta);
    char linea[512], *campo;
    // Obtenemos el nombre de la columna que estamos buscando (id, nombre, etc)
    campo = obtenerCampo(consulta);

    if (campo) {
        // Leemos la primera linea del archivo de datos
        fgets(linea, sizeof(linea), arch);    
        // Hallamos la posicion en la que se encuentra la columna
        int columna = hallarPosicionColumna(linea, campo);

        //Liberamos la memoria que asignamos anteriormente
        free(campo);

        // Obtenemos el valor de lo que estamos buscando en sí
        char *buscado = obtenerBuscado(consulta);

        recorrerArchivo(memComp, linea, buscado, columna, mutexMemoria, hayRespuesta, puedeEnviar, arch);

        //Liberamos la memoria
        free(buscado);
    } else {
        //Se recibio una consulta con campo erróneo, lo escribimos
        const char errCons[] = "La consulta posee un formato erróneo. Inténtelo de nuevo.";
        //strncpy(memComp, errCons, sizeof(errCons));
        escribirEnMemoria(errCons, memComp, mutexMemoria, hayRespuesta, puedeEnviar);
    }

    // Mandamos un mensaje para que termine de procesar respuestas
    escribirEnMemoria("ENDOFTHELINE", memComp, mutexMemoria, hayRespuesta, puedeEnviar);
}

FILE * abrirArchivo(char *path) {
    FILE * arch = fopen(path, "r");

    if (!arch) {
        error("No se pudo abrir el archivo que contiene los datos.");
        exit(1);
    }

    return arch;
}

void recorrerArchivo(char *memComp, char *linea, char *buscado, int columna, sem_t *mutexMemoria, sem_t *hayRespuesta, sem_t *puedeEnviar, FILE * arch) {
// Leemos otra linea del archivo
    fgets(linea, TAM_CONSULTA, arch);

    int bool_seHalloCoincidencia = 0;
    // Buscamos coincidencias dentro del arhivo y las escribimos en memoria compartida    
    while (!feof(arch)) {
        if (buscarCoincidencia(linea, columna, buscado) == 1)
        {
            printf("Se encontró un registro coincidente.\n");
            printf("%s\n", linea);
            escribirEnMemoria(linea, memComp, mutexMemoria, hayRespuesta, puedeEnviar);
            /*sem_wait(puedeEnviar);
            sem_wait(mutexMemoria);
            
            strcpy(memComp, linea);
            // Incrementamos el semaforo, porque ya terminamos de escribir en memoria
            sem_post(mutexMemoria);
            sem_post(hayRespuesta);*/
            bool_seHalloCoincidencia = 1;
        }
        
        fgets(linea, TAM_CONSULTA, arch);
    }

    if (bool_seHalloCoincidencia)         
        bool_seHalloCoincidencia = 0;
    else 
    {
        const char errNoCoinc[] = "No se hallaron coincidencias para la consulta.";
        //strncpy(memComp, errNoCoinc, sizeof(errNoCoinc));
        escribirEnMemoria(errNoCoinc, memComp, mutexMemoria, hayRespuesta, puedeEnviar);
        printf("%s\n", errNoCoinc);
    }
}

void escribirEnMemoria(const char *msg, char *memComp, sem_t *mutexMemoria, sem_t *hayRespuesta, sem_t * puedeEnviar) {
    sem_wait(puedeEnviar);
    sem_wait(mutexMemoria);
    strcpy(memComp, msg);
    sem_post(mutexMemoria);
    sem_post(hayRespuesta);
}


int buscarCoincidencia(char *linea, int columna, char *buscado) {
    char *puntoPartida, *delimitadorActual, *ultPos = linea;

    int cantSaltos = columna+1;
    //printf("CANT SALTOS: %d\n", cantSaltos);
    
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

    //printf("REGISTRO: %s BUSCADO: %s\n", puntoPartida, buscado);
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
        error("La consulta tiene errores o no respeta el formato adecuado.");
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
    printf("Este programa procesa consultas hacia un archivo que contiene datos, \n");
    printf("usando como medio áreas de memoria compartida para enviar y recibir.\n");
    printf("datos.\n");
    printf("El programa queda demonizado a la espera de consultas para resolver.\n");
    printf("No recibe parámetros.\n\n");
}