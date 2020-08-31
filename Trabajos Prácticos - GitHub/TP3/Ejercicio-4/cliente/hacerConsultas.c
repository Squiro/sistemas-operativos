#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <semaphore.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_CONSULTA 512

void ayuda();
void error(char *);
char * abrirSHM(int *);

void main(int argc, char *argv[]) {
	if (argc > 1) {
		if (strcmp(argv[1],"-help") == 0) {
			ayuda();
		} else {
			int shmid;
			char respuesta[TAM_CONSULTA];
			char * memComp = abrirSHM(&shmid);
			sem_t *mutexMemoria = sem_open("/mutexMemoria", 0);
			sem_t *hayConsulta = sem_open("/hayConsulta", 0);
			sem_t *hayRespuesta = sem_open("/hayRespuesta", 0);
			sem_t *puedeConsultar = sem_open("/puedeConsultar", 0);
			sem_t *puedeEnviar = sem_open("/puedeEnviar", 0);
			
			//Preguntamos si podemos consultar
			sem_wait(puedeConsultar);
			//Nos fijamos que la memoria este libre para que la escribamos nosotros
			sem_wait(mutexMemoria);
			//Escribimos la consulta en memoria
			strcpy(memComp, argv[1]);
			//Dejamos a la memoria libre para que acceda otro proceso
			sem_post(mutexMemoria);
			//Indicamos que se realizo una consulta
			sem_post(hayConsulta);			

			strcpy(respuesta, "Procesando...");
			while (strcmp(respuesta,"ENDOFTHELINE") != 0) {
				printf("RESPUESTA: %s\n", respuesta);
				// Leemos la consulta de memoria
				sem_wait(hayRespuesta);
				sem_wait(mutexMemoria);
				strncpy(respuesta, memComp, sizeof(respuesta));
				sem_post(mutexMemoria);	
				sem_post(puedeEnviar);		
			}

			sem_close(mutexMemoria);
			sem_close(hayRespuesta);
			sem_close(hayConsulta);
			sem_close(puedeConsultar);
			sem_close(puedeEnviar);
		}


	} else {
		error("Este programa necesita recibir por parámetro la consulta.");
		ayuda();
	}


}

char * abrirSHM(int *shmid) {
    //int shmid;
    char *memComp;

    *shmid = shmget(234, sizeof(char)*TAM_CONSULTA, 0);

    // Shmget asigna un espacio de memoria del sistema
    if (*shmid == -1) {
        error("Hubo un error al intentar abrir el área compartida de memoria.");
        exit(1);
    }

    memComp = shmat(*shmid, NULL, 0);

    if (!memComp) {
        error("Hubo un error al intentar abrir el área compartida de memoria.");
        exit(1);
    }

    return memComp;
}

void error(char *msg) {
    printf("%s\n\n", msg);
}

void ayuda() {
    printf("\n\n");
    printf("Este programa realiza consultas hacia un proceso demonio para\n");
    printf("obtener datos sobre un archivo.\n\n");
    printf("Sintaxis de ejecución: \n");
    printf("./hacerConsultas <consulta>\n");
}