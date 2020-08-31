#include "arbol.h"

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

int insertarOrdenado(t_arbol * pa, t_dato *d, t_cmp comparar)
{
    int cmp;

    if (*pa)
    {
        cmp = comparar(&(*pa)->dato, d);

        if (cmp < 0)
            return insertarOrdenado(&(*pa)->der, d, comparar);
        else if (cmp > 0)
            return insertarOrdenado(&(*pa)->izq, d, comparar);
        else
            return DUPLICADO;
    }
    else
    {
        *pa = (t_nodo *) malloc(sizeof(t_nodo));

        if (!(*pa))
            return SIN_MEM;

        (*pa)->dato = *d;
        (*pa)->izq = NULL;
        (*pa)->der = NULL;

        return SUCCESS;
    }

    return SUCCESS;
}

int insertarBalanceado(t_arbol * pa, FILE * arch, int ini, int fin)
{
    t_indice idx;
    int mid = (ini+fin)/2;

    if (ini > fin)
    {
        //*pa = NULL;
        return 0;
    }

    /**pa = (t_nodo *) malloc(sizeof(t_nodo));

    if (!(*pa))
        return SIN_MEM;*/

    fseek(arch, mid*sizeof(t_indice), SEEK_SET);
    fread(&idx, sizeof(t_indice), 1, arch);

    //(*pa)->dato = idx;
    insertarOrdenado(pa, &idx, compararClaves);

    insertarBalanceado(&(*pa)->izq, arch, ini, mid-1);
    insertarBalanceado(&(*pa)->der, arch, mid+1, fin);

    return SUCCESS;
}

/*int insertarBalanceadoArray(t_arbol * pa, t_dato * arr, int ini, int fin)
{
    if (ini > fin)
    {
        *pa = NULL;
        return 0;
    }

    int mid = (ini+fin)/2;

    *pa = (t_nodo *) malloc(sizeof(t_nodo));

    if (!(*pa))
        return SIN_MEM;

    (*pa)->dato = *(arr+mid);

    insertarBalanceado(&(*pa)->izq, arr, ini, mid-1);
    insertarBalanceado(&(*pa)->der, arr, mid+1, fin);

    return SUCCESS;
}*/

void preOrden(t_arbol * pa, t_accion accion)
{
    if (*pa)
    {
        accion(&(*pa)->dato);
        preOrden(&(*pa)->izq, accion);
        preOrden(&(*pa)->der, accion);
    }

    return;
}

int mostrar(const void *arg)
{
    t_indice * idx = (t_indice *) arg;

    printf("Clave: %d\n", idx->clave);

    return 0;
}

int compararClaves(const void * arg1, const void *arg2)
{
    int *clave1 = (int *) arg1, *clave2 = (int *)arg2;

    return *clave1-*clave2;
}
