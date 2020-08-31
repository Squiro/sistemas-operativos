#include <stdio.h>
#include <stdlib.h>
#include "funciones.h"
#include "arbol.h"

int main()
{
    char rutaEmp[] = "empleados.bin", rutaIdx[] = "indice.idx", rutaOrd[] = "empleados_ord.bin";
    t_arbol arbol;
    crearArbol(&arbol);

    generarArchivoEmpleados(rutaEmp);
    mostrarArchivoEmpleados(rutaEmp);
    generarIndice(&arbol, rutaEmp, rutaIdx);
    mostrarIndice(rutaIdx);
    ordenarArchivoEmpleados(rutaEmp, rutaIdx, rutaOrd);
    mostrarArchivoEmpleados(rutaOrd);

    return 0;
}
