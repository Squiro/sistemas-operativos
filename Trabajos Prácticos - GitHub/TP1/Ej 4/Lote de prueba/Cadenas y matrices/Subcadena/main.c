#include <stdio.h>
#include <stdlib.h>
#include "funciones.h"

int main()
{
    char cad[] = "hola como estas";
    char remp[] = "como estas";
    char nueva[] = "chau nos vemos";

    printf("%s", reemplazar(cad, remp, nueva));

    return 0;
}
