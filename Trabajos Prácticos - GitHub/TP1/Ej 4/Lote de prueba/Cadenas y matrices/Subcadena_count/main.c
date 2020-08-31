#include <stdio.h>
#include <stdlib.h>

/** ¿Cuántas veces se repite un sub_str dentro de un str? */

int main()
{
    char cad[] = "ananavana";
    char sub_str[] = "ana";

    printf("%d", substr_count(cad, sub_str));

    return 0;
}
