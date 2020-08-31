#ifndef COLA_H_
#define COLA_H_

#include <stdlib.h>
#include <stdio.h>

#define SIN_MEM 99
#define COLA_VACIA 98
#define SUCCESS 0

typedef struct
{
    int dni;
    char apyn[30];
    double sueldo;
} t_empleado;

typedef t_empleado t_dato;

typedef struct s_nodo
{
    t_dato dato;
    struct s_nodo * sig;
} t_nodo;

typedef struct
{
    t_nodo * primero;
    t_nodo * ultimo;
} t_cola;

void crearCola(t_cola *c);
int colaVacia(const t_cola *c);
int colaLlena(const t_cola *c);
int acolar(t_cola *c, const t_dato *d);
int desacolar(t_cola *c, t_dato *d);
int verTope(const t_cola *c, t_dato *d);
void vaciarCola(t_cola *c);

#endif // COLA_H_
