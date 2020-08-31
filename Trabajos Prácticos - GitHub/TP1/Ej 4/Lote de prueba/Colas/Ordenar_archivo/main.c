#include <stdio.h>
#include <stdlib.h>
#include "funciones.h"
#include "cola.h"

int main()
{
    t_cola cola;
    crearCola(&cola);
    generarLote("empleados.bin");
    guardarEnCola(&cola, "empleados.bin");
    ordenarCola(&cola, compararDNI);
    generarResultado(&cola, "resultado.bin");
    mostrarArchivo("resultado.bin");
    return 0;
}
