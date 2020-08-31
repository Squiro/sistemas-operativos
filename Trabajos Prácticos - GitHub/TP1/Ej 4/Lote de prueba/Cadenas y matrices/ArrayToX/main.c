#include "funciones.h"

int main()
{
    char flotante[] = "-1234.567";
    char entero[] = "1234567";
    char cad[33];

    printf("%lf\n", mi_atof(flotante));
    printf("%d\n", mi_atoi(entero));
    printf("%s", mi_itoa(123456, cad, 10));
    return 0;
}
