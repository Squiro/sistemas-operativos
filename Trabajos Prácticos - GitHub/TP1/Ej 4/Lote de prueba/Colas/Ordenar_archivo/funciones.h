#ifndef FUNCIONES_H_
#define FUNCIONES_H_

#include <stdlib.h>
#include <stdio.h>
#include "cola.h"

#define ERROR_ARCH 99

typedef int (*t_cmp)(const void *, const void *);

int generarLote(char * ruta);
int guardarEnCola(t_cola *c, char * ruta);
int ordenarCola(t_cola *c, t_cmp comparar);
int generarResultado(t_cola *c, char * ruta);
int mostrarArchivo(char * ruta);

t_empleado extraerMinimo(t_cola *c);
int compararDNI(const void *, const void *);

#endif // FUNCIONES_H_
