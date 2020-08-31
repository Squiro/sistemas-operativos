#include "funciones.h"


/*Dos archivos, uno maestro, uno de novedades que guarda todos los nuevos registros de forma ordenada
Generamos un archivo maestro actualizado a partir de ambos

Ademas debemos crear un log de errores para problemas como:
        -Baja de un alumno inexistente
        -Alta de un alumno existente
        -Modif de un alumno inexistente
*/

int main()
{
    generarLoteMaestro();
    generarLoteNovedades();
    actualizarMaestro();
    mostrarMaestro();
    //mostrarError();
    return 0;
}
