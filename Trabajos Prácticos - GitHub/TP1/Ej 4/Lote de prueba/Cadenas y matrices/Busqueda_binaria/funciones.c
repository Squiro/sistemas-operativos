#include "funciones.h"
#define REDONDEO_NEGATIVO(X)(((X)-(int)(X)) >= 0.5) ?((int)(X))-1 :(int)(X)

int busqueda_binaria(int arr[], int cantElem, int num)
{
    int prim = 0, ult = cantElem -1, medio;

    while (prim <= ult)
    {
        medio = REDONDEO_NEGATIVO(prim+ult/2);

        if (arr[medio] < num)
            prim = medio+1;
        else if (arr[medio] > num)
            ult = medio-1;
        else
            return arr[medio];
    }

    return -99999;
}
