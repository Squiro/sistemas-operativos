#ifndef FUNCIONES_H_
#define FUNCIONES_H_

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

void error(char *);
void ayuda();
char * crearSHM(int *);
void leerConsultas(char *);
void procesarConsulta(char *consulta, char *memComp, sem_t *mutexMemoria, sem_t *hayRespuesta, sem_t * puedeEnviar, FILE * arch);
FILE * abrirArchivo(char *path);
void recorrerArchivo(char *memComp, char *linea, char *buscado, int columna, sem_t *mutexMemoria, sem_t *hayRespuesta, sem_t *puedeEnviar, FILE * arch);
void escribirEnMemoria(const char *, char *, sem_t *, sem_t *, sem_t * );
int buscarCoincidencia(char *, int , char *);
char * obtenerCampo(char *);
char * obtenerBuscado(char *);
int hallarPosicionColumna(char *, char *);

#endif

