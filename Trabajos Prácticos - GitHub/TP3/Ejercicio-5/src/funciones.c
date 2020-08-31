#include "funciones.h"

void error(char *msg) {
    printf("%s\n\n", msg);
}

int configurarOpciones(int socket) {
    int habilitar = 1;
    return setsockopt(socket, SOL_SOCKET, SO_REUSEADDR, &habilitar, sizeof(int));
}

struct sockaddr_in configurarSocket(char *puerto) {
    struct sockaddr_in serverAddress;

    // Limpiamos la estructura de configuracion del servidor antes de setear
    // los valores
    memset(&serverAddress, 0, sizeof(struct sockaddr_in));
    // Dominio
    serverAddress.sin_family = AF_INET;
    // Puerto
    serverAddress.sin_port = htons(atoi(puerto));
    // Adress a la que escuchará el server (en este caso, cualquiera)
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    return serverAddress;
}

void aceptarConexionesEntrantes(int serverSocket) {

    socklen_t cl = sizeof(struct sockaddr_in);
    struct sockaddr_in clientAddress;    
    int clientSocket;
    pthread_t th_id;
    thread_info info;

    while (1) {      
        clientSocket = accept(serverSocket, (struct sockaddr *) &clientAddress, &cl);
        info.clientSocket = clientSocket;        
        pthread_create(&th_id, NULL, &leerConsultas, &info);
    }
}

void * leerConsultas(void *info) {
    thread_info * threadInfo = (thread_info *) info;

    // Almacenara la consulta
    char consulta[TAM_CONSULTA];
    //Abrimos el archivo aca para no tener que estar abriendolo y cerrandolo todo el rato
    FILE * arch = abrirArchivo("articulos.txt");

    recv(threadInfo->clientSocket, consulta, TAM_CONSULTA, 0);

    while (strcmp(consulta,"QUIT") != 0) {
        // Bloquea hasta recibir un mensaje        
        procesarConsulta(consulta, arch, threadInfo->clientSocket);
        recv(threadInfo->clientSocket, consulta, TAM_CONSULTA, 0);
    }

    fclose(arch);
    close(threadInfo->clientSocket);
}

void procesarConsulta(char *consulta, FILE * arch, int clientSocket) {  
    //Rebobinamos fd del archivo para que apunte a la primera posicion
    fseek(arch, 0, SEEK_SET);

    printf("CONSULTA: %s\n", consulta);
    char linea[512], *campo;
    char packetSize[10];

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

        recorrerArchivo(linea, buscado, columna, arch, clientSocket);

        //Liberamos la memoria
        free(buscado);
    } else {
        //Se recibio una consulta con campo erróneo, lo escribimos
        const char errCons[] = "La consulta posee un formato erróneo. Inténtelo de nuevo.";
        
        sprintf(packetSize, "%d", (int) sizeof(errCons));        
        send(clientSocket, packetSize, sizeof(int), 0);
        send(clientSocket, errCons, sizeof(errCons), 0);        
    }

    // Mandamos un mensaje para que termine de procesar respuestas
    // el proceso cliente
    const char theEnd[] = "ENDOFTHELINE";          
    sprintf(packetSize, "%d", (int) sizeof(theEnd));
    send(clientSocket, packetSize, sizeof(int), 0);
    send(clientSocket, theEnd, sizeof(theEnd), 0); 
}

FILE * abrirArchivo(char *path) {
    FILE * arch = fopen(path, "r");

    if (!arch) {
        error("No se pudo abrir el archivo que contiene los datos.");
        exit(1);
    }

    return arch;
}

void recorrerArchivo(char *linea, char *buscado, int columna, FILE * arch, int clientSocket) {
    // Leemos otra linea del archivo
    fgets(linea, TAM_CONSULTA, arch);

    int bool_seHalloCoincidencia = 0;
    // Buscamos coincidencias dentro del arhivo y las escribimos
    int len;
    char packetSize[10];

    while (!feof(arch)) {
        if (buscarCoincidencia(linea, columna, buscado) == 1)
        {
            printf("Se encontró un registro coincidente.\n");
            printf("%s\n", linea);
            // Calculamos el length de la linea
            len = strlen(linea);            
            sprintf(packetSize, "%d", len);
            // Enviamos el tamaño del mensaje
            send(clientSocket, packetSize, sizeof(int), 0);
            // Enviamos el mensaje
            send(clientSocket, linea, len, 0);
            bool_seHalloCoincidencia = 1;
        }
        
        fgets(linea, TAM_CONSULTA, arch);
    }

    if (bool_seHalloCoincidencia)         
        bool_seHalloCoincidencia = 0;
    else 
    {
        const char errNoCoinc[] = "No se hallaron coincidencias para la consulta.";
        sprintf(packetSize, "%d", (int) sizeof(errNoCoinc));
        send(clientSocket, packetSize, sizeof(int), 0);
        send(clientSocket, errNoCoinc, sizeof(errNoCoinc), 0);           
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
    printf("usando como medio sockets para enviar y recibir datos.\n");
    printf("El programa queda demonizado a la espera de consultas para resolver.\n");
    printf("Recibe como parámetros el puerto de escucha.\n\n");
}