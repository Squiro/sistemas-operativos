#ifndef FUNCIONES_H_
#define FUNCIONES_H_

#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_BUFFER 512


void error(char *);
void ayuda();
void crearFIFOS(char *, char *);
void unlinkFIFOS(char *fifoEntrada, char *fifoSalida);
void leerConsultas(char *, char *);
void procesarConsulta(char *consulta, char *fifoSalida, FILE * arch);
FILE * abrirArchivo(char *path);
void recorrerArchivo(FILE * arch, char *linea, char *buscado, int columna, int pipeEscritura);
int buscarCoincidencia(char *, int , char *);
char * obtenerCampo(char *);
char * obtenerBuscado(char *);
int hallarPosicionColumna(char *, char *);


#endif