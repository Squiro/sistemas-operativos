#ifndef ARBOL_H_
#define ARBOL_H_

#include <stdio.h>
#include <stdlib.h>

#define DUPLICADO 50
#define SIN_MEM 49
#define SUCCESS 0

/** Funciones parametrizadas */

typedef int (*t_cmp)(const void *arg1, const void *arg2);
typedef int (*t_accion)(const void *arg);

/** Estructuras utilizadas */

typedef struct
{
    int clave; //Guarda la clave del registro
    int numReg; //Guarda el desplazamiento de donde se encuentra
} t_indice;

typedef t_indice t_dato;

typedef struct s_nodo
{
    t_dato dato;
    struct s_nodo * izq;
    struct s_nodo * der;
} t_nodo;

typedef t_nodo * t_arbol;

/** Primitivas */

void crearArbol(t_arbol * pa);
int arbolLleno(const t_arbol * pa);
int arbolVacio(const t_arbol * pa);
void eliminarArbol(t_arbol * pa);
int insertarOrdenado(t_arbol * pa, const t_dato *d, t_cmp comparar);

/** Recorridos */

void inOrden(const t_arbol * pa, t_accion accion);

/** Utilidades */

int compararClaves(const void * arg1, const void *arg2);
int mostrar(const void *arg);

#endif // ARBOL_H_
