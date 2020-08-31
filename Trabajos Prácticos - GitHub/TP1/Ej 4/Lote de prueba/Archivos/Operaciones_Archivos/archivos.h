#ifndef ARCHIVOS_H_
#define ARCHIVOS_H_

#define ERROR_ABRIR 99

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int dni;
    char nombre[50];
    char apellido[50];
    float sueldo;
} t_empleado;

int generarLoteA();

int generarLoteB();

int diferenciaEntre(char *ruta1, char *ruta2);

int compararRegistros(t_empleado *regA, t_empleado *regB);

void mostrarArchivo(char *ruta);

int intersecEntre(char *ruta1, char *ruta2);

int unionEntre(char *ruta1, char *ruta2);


#endif // ARCHIVOS_H_
