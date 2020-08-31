#ifndef ARBOL_H_
#define ARBOL_H_

#include <stdlib.h>
#include <stdio.h>

#define SIN_MEM 50
#define DUPLICADO 49
#define SUCCESS 0

/** Funciones parametrizadas */

typedef int (*t_cmp)(const void *, const void *);
typedef int (*t_accion)(const void*);

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
int arbolVacio(const t_arbol * pa);
int arbolLleno(const t_arbol * pa);
int insertarOrdenado(t_arbol * pa, t_dato * d, t_cmp comparar);
int insertarBalanceado(t_arbol * pa, FILE * arch, int ini, int fin);
int insertarBalanceadoArray(t_arbol * pa, t_dato * arr, int ini, int fin);

/** Recorridos */

void preOrden(t_arbol * pa, t_accion accion);

/** Utilidades */
int mostrar(const void *arg);

int compararClaves(const void * arg1, const void *arg2);
#endif // ARBOL_H_
