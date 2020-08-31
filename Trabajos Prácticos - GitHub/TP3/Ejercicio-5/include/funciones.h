#ifndef FUNCIONES_H_
#define FUNCIONES_H_

#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <pthread.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_CONSULTA 512
#define MAX_QUEUE 16

typedef struct 
{
	int clientSocket;
} thread_info;

void error(char *);
void ayuda();
int configurarOpciones(int socket);
struct sockaddr_in configurarSocket(char *puerto);
void aceptarConexionesEntrantes(int serverSocket);
void * leerConsultas(void *info);
void procesarConsulta(char *consulta, FILE * arch, int clientSocket);
FILE * abrirArchivo(char *path);
void recorrerArchivo(char *linea, char *buscado, int columna, FILE * arch, int clientSocket); 
int buscarCoincidencia(char *, int , char *);
char * obtenerCampo(char *);
char * obtenerBuscado(char *);
int hallarPosicionColumna(char *, char *);

#endif

