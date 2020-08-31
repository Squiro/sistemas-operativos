#include "cola.h"

void crearCola(t_cola *c)
{
    c->primero = NULL;
    c->ultimo = NULL;
}

int colaVacia(const t_cola *c)
{
    return c->primero == NULL;
}

int colaLlena(const t_cola *c)
{
    t_nodo * aux = (t_nodo *) malloc(sizeof(t_nodo));

    free(aux);

    return aux == NULL;
}

int acolar(t_cola *c, const t_dato *d)
{
    t_nodo * nuevo = (t_nodo *) malloc(sizeof(t_nodo));

    if (!nuevo)
        return SIN_MEM;

    nuevo->dato = *d;
    nuevo->sig = NULL;

    if (!c->primero)
        c->primero = nuevo;
    else
        c->ultimo->sig = nuevo;
    c->ultimo = nuevo;

    return SUCCESS;
}

int desacolar(t_cola *c, t_dato *d)
{
    t_nodo * aux = c->primero;

    if (!aux)
        return COLA_VACIA;

    *d = aux->dato;
    c->primero = c->primero->sig;

    if (!c->primero)
        c->ultimo = NULL;

    free(aux);

    return SUCCESS;
}

int verTope(const t_cola *c, t_dato *d)
{
    if (!c->primero)
        return COLA_VACIA;

    *d = c->primero->dato;

    return SUCCESS;
}

void vaciarCola(t_cola *c)
{
    t_nodo * aux = c->primero;

    while (aux)
    {
        c->primero = c->primero->sig;
        free(aux);
        aux = c->primero;
    }

    c->ultimo = NULL;
}
