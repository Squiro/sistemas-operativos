#include <unistd.h>
#include <sys/wait.h>
#include <pthread.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*# =========================== Encabezado =======================

# Nombre del archivo: ejercicio2.c
# Número de ejercicio: 2
# Trabajo Práctico: 3
# Entrega: Primer entrega

# ==============================================================

# ------------------------ Integrantes ------------------------
# 
#		Nombre		|		Apellido		|		DNI
# -------------------------------------------------------------*/
void error(char *);
void ayuda();
void crearHilos(int, char *);
int contarLineasArchivo(FILE *);
void * sumarVectores(void *info);
double procesarLinea(char *);

typedef struct 
{
    FILE * archVectores;
    FILE * archResultado;
    pthread_mutex_t mutexArchivo;
    int cantLineas;
} thread_info;


void main(int argc, char *argv[]) {

    if (argc > 1) {
        // Chequeamos si se recibio un parametro de ayuda
        if (strcmp(argv[1],"-help") == 0) {
            ayuda();
        } // Chequeamos si se recibio menos que la cantidad necesaria de parametros
        else if (argc < 3) {
            error("Argumentos faltantes. Este script necesita tanto el número de threads como la ruta del archivo.");
            ayuda();
        } else {
            // Convertimos el numero pasado por parametro a int
            int numThreads = atoi(argv[1]);        

            if (numThreads < 0)
            {
                error("El número de threads tiene que ser mayor a 0. Vuelva a ejecutar este script.");
                exit(1);
            }

            crearHilos(numThreads, argv[2]);
        }     
    } else
    {
        ayuda();
    }
}

void error(char *msg) {
    printf("%s\n\n", msg);
}

void crearHilos(int numThreads, char *pathArchivo) {
    // Abrimos ambos archivos
    FILE * archVectores = fopen(pathArchivo, "r");

    if (!archVectores) {
        error("Hubo un error al intentar abrir el archivo.");
        exit(1);
    }

    FILE * archResultado = fopen("resultado.txt", "w");

    if (!archResultado) {
        error("Hubo un error al intentar crear el archivo de resultado.");
        exit(1);
    }

    // Contamos las lineas del archivo de vectores
    int cantLineas = contarLineasArchivo(archVectores);
    // Rebobinamos el puntero al principio del archivo de vectores
    fseek(archVectores, 0, SEEK_SET);  

    
    int bool_sumarleUno = 0, lineasPorArchivo = cantLineas/numThreads;
    // ¿Que pasa su un archivo tiene 3 lineas, y lo dividimos por threads?
    // No podemos hacer que uno lea 0.5 lineas.. ni que el archivo quede sin recorrerse completamente
    if (cantLineas%numThreads != 0)
        bool_sumarleUno = 1;

    if (lineasPorArchivo == 0) {
        error("La cantidad de threads es muy alta. No se puede dividir el trabajo equitativamente.");
        exit(1);
    }

    int i; 
    pthread_t vectorDeIDs[numThreads];
    // Creamos un struct que contenga los datos que van a usar los hilos
    thread_info info;
    info.archVectores = archVectores;
    info.archResultado = archResultado;
    // Inicializamos el semaforom mutex
    pthread_mutex_init(&info.mutexArchivo, NULL);    
    info.cantLineas = lineasPorArchivo;

    printf("Cada thread operara con: %d elementos\n", info.cantLineas);

    // Creamos un thread por separado, que sume mas lineas que los otros
    if (bool_sumarleUno) {
        thread_info info2 = info;
        info2.cantLineas++;
        pthread_create(&vectorDeIDs[i], NULL, &sumarVectores, &info2);
        numThreads--;
    }

    // Creamos los hilos que sumen la misma cantidad de lineas
    for (i = 0; i < numThreads; i++) {
        vectorDeIDs[i] = i;        
        pthread_create(&vectorDeIDs[i], NULL, &sumarVectores, &info);
    }

    // Joineamos los threads. Hacer un join bloquea el hilo que llama a la funcion hasta que el thread aludido termine su ejecución.
    for (i = 0; i < numThreads; i++) {
        pthread_join(vectorDeIDs[i], NULL);
    }
}

int contarLineasArchivo(FILE * arch) {
    char buff[256];
    int contador = 0;

    while (fgets(buff,sizeof(buff), arch) != NULL) {
        contador++;
    }

    return contador;
}

void * sumarVectores(void *info) {
    // Convertimos el parametro recibido a puntero de nuestra struct
    thread_info * t_info = (thread_info *) info;

    int cantLineas = t_info->cantLineas;
    char datos[512];
    // Decrementamos el semaforo porque vamos a estar escribiendo y leyendo del archivo
    pthread_mutex_lock(&(t_info->mutexArchivo));
    fgets(datos, 512, t_info->archVectores);
    pthread_mutex_unlock(&(t_info->mutexArchivo));
    // Mientras que no lleguemos al fin del archivo y la cantidad de lineas de este thread sea mayor a 0
    while (!feof(t_info->archVectores) && cantLineas > 0) {
         // Decrementamos el semaforo porque vamos a estar escribiendo y leyendo del archivo
        pthread_mutex_lock(&(t_info->mutexArchivo));
        // Procesamos la linea y sumamos los valores double
        double resultado = procesarLinea(datos);
        // Escribimos en el archivo de resultado
        fprintf(t_info->archResultado, "%lf\n", resultado);
        // Decrementamos la cantidad de lineas a leer para este thread
        cantLineas--;
        // Leemos otra linea de datos del archivo solo si tenemos que
        if (cantLineas > 0)            
            fgets(datos, 512, t_info->archVectores);        
        // Incrementamos el semaforo
        pthread_mutex_unlock(&(t_info->mutexArchivo));
    }
}

double procesarLinea(char *linea) {
    char *aux;
    double valor1, valor2;

    aux = strchr(linea, '\n');
    // Si no encuentra el \n es que esta linea está mal
    if (!aux) {
        return 0;
    }
    *aux = '\0';
    // Buscamos la coma delimitadora
    aux = strrchr(linea, ',');
    // Escaneamos un double desde donde estamos parados
    sscanf(aux+1, "%lf", &valor2);
    *aux = '\0';
    // Como solo tenemos dos valores, buscamos un double desde el comienzo de la linea
    sscanf(linea, "%lf", &valor1);

    return valor1 + valor2;
}

void ayuda() {
    printf("\n\n");
    printf("Este script realiza la suma de dos vectores, cuyos valores están almacenados en un archivo.\n");
    printf("Para esto, divide equitativamente la tarea en un número de threads.\n");
    printf("Como resultado genera un archivo nuevo que almacena el vector resultado.\n\n");
    printf("Sintaxis de ejecución: \n");
    printf("./ejercicio2 <numero de threads> <ruta del archivo>\n");
    printf("Ejemplo de ejecución: \n");
    printf("./ejercicio2 4 /home/usuario/valores.txt\n");
}