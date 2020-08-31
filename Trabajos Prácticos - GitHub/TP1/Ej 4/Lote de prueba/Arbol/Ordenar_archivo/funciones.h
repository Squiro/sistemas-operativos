#ifndef FUNCIONES_H_
#define FUNCIONES_H_

#include <stdio.h>
#include <stdlib.h>
#include "arbol.h"

#define ERROR_ABRIR 99

typedef struct
{
    int clave;
    char nombre[50];
    char apellido[50];
    double sueldo;
} t_empleado;

/** Genera un lote de pruebas */
int generarArchivoEmpleados(char * ruta);

/** A partir de un archivo, genera un indice del mismo. Crea un archivo de ext. idx donde guarda todo.

PARAM:
    -pa = puntero a arbol en donde se va a guardar la clave del reg y el desplazamiento
    -ruta = ruta del archivo a leer

*/
int generarIndice(t_arbol * pa, char * rutaEmp, char * rutaIdx);
void generarArchivoIndice(t_arbol *pa, FILE * arch);
/** Sobreescribe el archivo indice para crearlo desde 0.
int generarArchivoIndice(t_arbol *pa, char * rutaIdx);*/
/** Accion utilizada en la funcion anterior. Adjunta un indice en el archivo. */
int guardarIndice(const void *arg);

int ordenarArchivoEmpleados(char * rutaEmp, char *rutaIdx, char *rutaOrd);


/** Mostrar archivos */

int mostrarArchivoEmpleados(char * ruta);
int mostrarIndice(char * ruta);



#endif // FUNCIONES_H_
