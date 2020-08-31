#include <stdio.h>
#include <stdlib.h>
#include "funciones.h"
#include "arbol.h"

int main()
{
    t_arbol arbol;
    crearArbol(&arbol);
    char rutaIdx[] = "indice.idx";

    generarArbolBalanceado(&arbol, rutaIdx);
    preOrden(&arbol, mostrar);
    return 0;
}
