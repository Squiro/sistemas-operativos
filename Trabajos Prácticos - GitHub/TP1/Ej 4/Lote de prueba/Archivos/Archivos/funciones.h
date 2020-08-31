#ifndef FUNCIONES_H_
#define FUNCIONES_H_

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "fechas.h"

#define NO_INGRESO 0
#define INGRESO_OK 1

typedef struct
{
    int dni;
    char apellido[30];
    char nombre[30];
    char sexo;
    t_fecha nacimiento;
    float promedio;
} t_alumno;

int cargarRegistro(t_alumno * alumno);
void mostrarArchivo(FILE * arch);

#endif // FUNCIONES_H_
