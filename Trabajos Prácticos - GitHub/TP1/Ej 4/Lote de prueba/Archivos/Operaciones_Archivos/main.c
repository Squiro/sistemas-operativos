#include "archivos.h"

int main()
{
    generarLoteA();
    generarLoteB();
    diferenciaEntre("empleados_a.bin", "empleados_b.bin");
    diferenciaEntre("empleados_b.bin", "empleados_a.bin");
    intersecEntre("empleados_a.bin", "empleados_b.bin");
    unionEntre("empleados_a.bin", "empleados_b.bin");
    return 0;
}
