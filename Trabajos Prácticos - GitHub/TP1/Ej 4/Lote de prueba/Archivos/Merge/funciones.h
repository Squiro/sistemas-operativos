#ifndef FUNCIONES_H_
#define FUNCIONES_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ERROR -1
#define SUCCESS 0
#define ALTA 1
#define BAJA 2
#define MODIF 3
#define ERROR_ABRIR 99

typedef struct
{
    int dni;
    char nombre[50];
    char apellido[50];
    char sexo;
} t_alumno;

typedef struct
{
    int dni;
    char nombre[50];
    char apellido[50];
    char sexo;
    int tipo;
} t_novedad;

typedef struct
{
    char msg[100];
    t_novedad nov;
} t_error;

int generarLoteMaestro();

int generarLoteNovedades();

int actualizarMaestro();

int darAlta(t_novedad *nov, t_alumno *alum, FILE * maestAct);

int darModif(t_novedad *nov, t_alumno *alum, FILE * maestAct);

int writeError(int tipo, t_novedad * nov);

int mostrarMaestro();

int mostrarError();
#endif // FUNCIONES_H_
