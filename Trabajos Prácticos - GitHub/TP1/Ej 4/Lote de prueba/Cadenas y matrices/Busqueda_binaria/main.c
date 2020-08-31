#include <stdio.h>
#include <stdlib.h>
#include "funciones.h"


int main()
{
    int arr[9] = { 1, 2, 3, 4, 5, 6, 7, 8, 9};

    printf("%d", busqueda_binaria(arr, 9, 4));
    return 0;
}
