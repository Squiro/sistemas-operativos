#ifndef FUNCIONES_H_
#define FUNCIONES_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ERROR_ABRIR 99
#define LINEA_MAL 98

typedef struct
{
    int dni;
    char nombre[50];
    char apellido[50];
    float sueldo;
} t_empleado;


int generarLote();

int convertirATxt();

int convertirABin();

int procesarLinea(char *linea, t_empleado *emp);

void mostrarArchivo(FILE * arch);
#endif //FUNCIONES_H_
