#include "arbol.h"

/** Primitivas */

void crearArbol(t_arbol * pa)
{
    *pa = NULL;
}

int arbolVacio(const t_arbol * pa)
{
    return *pa == NULL;
}

int arbolLleno(const t_arbol * pa)
{
    t_nodo * aux = (t_nodo *) malloc(sizeof(t_nodo));
    free(aux);

    return aux == NULL;
}

void eliminarArbol(t_arbol * pa)
{
    if (*pa)
    {
        eliminarArbol(&(*pa)->izq);
        eliminarArbol(&(*pa)->der);
        free(pa);
        *pa = NULL;
    }
}

int insertarOrdenado(t_arbol * pa, const t_dato *d, t_cmp comparar)
{
    int cmp;

    if (*pa)
    {
        cmp = comparar(&(*pa)->dato.clave, &d->clave);

        if (cmp < 0)
            return insertarOrdenado(&(*pa)->der, d, comparar);
        else if (cmp > 0)
            return insertarOrdenado(&(*pa)->izq, d, comparar);
        else
            return DUPLICADO;
    }
    else
    {
        t_nodo * nuevo = (t_nodo *) malloc(sizeof(t_nodo));

        if (!nuevo)
            return SIN_MEM;

        nuevo->dato = *d;
        nuevo->izq = NULL;
        nuevo->der = NULL;
        *pa = nuevo;

        return SUCCESS;

    }
    return SUCCESS;
}

void inOrden(const t_arbol * pa, t_accion accion)
{
    if (*pa)
    {
        inOrden(&(*pa)->izq, accion);
        accion(&(*pa)->dato);
        inOrden(&(*pa)->der, accion);
    }

    return;
}

/** Utilidades */

int compararClaves(const void * arg1, const void *arg2)
{
    int *clave1 = (int *) arg1, *clave2 = (int *)arg2;

    return *clave1-*clave2;
}

int mostrar(const void *arg)
{
    t_indice * idx = (t_indice *) arg;

    printf("Clave: %d\n", idx->clave);

    return 0;
}
