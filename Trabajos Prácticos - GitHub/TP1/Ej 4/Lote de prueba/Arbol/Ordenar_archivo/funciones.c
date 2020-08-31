#include "funciones.h"

/** Hacer las correcciones:
    -Abrir el archivo antes y pasarle el puntero archivo.
    -Modificar inorden para que reciba el puntero y escriba directamente.
*/

int generarArchivoEmpleados(char * ruta)
{
    FILE * arch;
    t_empleado emp[4] = { { 10, "Albertito", "Perez", 250.25 }, { 2, "Josefina", "Napoleon", 342.34 }, { 1, "Sargento", "Garcia", 202.20 },
    { 6, "Eric", "Cartman", 123.123 } };
    int i;

    arch = fopen(ruta, "wb");

    if (!arch)
        return ERROR_ABRIR;

    for (i = 0; i < 4; i++)
        fwrite(&emp[i], sizeof(t_empleado), 1, arch);

    fclose(arch);

    return SUCCESS;
}

int generarIndice(t_arbol * pa, char * rutaEmp, char * rutaIdx)
{
    FILE * archEmp, * archIdx;
    t_empleado emp;
    t_indice idx;
    int count = 0;

    archEmp = fopen(rutaEmp, "rb");

    if (!archEmp)
        return ERROR_ABRIR;

    fread(&emp, sizeof(t_empleado), 1, archEmp);

    while (!feof(archEmp))
    {
        idx.clave = emp.clave; //Asigno la clave
        idx.numReg = count; //Asigno el desplazamiento
        insertarOrdenado(pa, &idx, compararClaves); //Inserto el indice en el arbol
        count++; //Incremento el desplazamiento para el proximo registro
        fread(&emp, sizeof(t_empleado), 1, archEmp);
    }

    archIdx = fopen(rutaIdx, "wb");

    if (!archIdx)
        return ERROR_ABRIR;

    generarArchivoIndice(pa, archIdx);

    fclose(archEmp);
    fclose(archIdx);

    return SUCCESS;
}

void generarArchivoIndice(t_arbol *pa, FILE * arch)
{
    if (*pa)
    {
        generarArchivoIndice(&(*pa)->izq, arch);
        fwrite(&(*pa)->dato, sizeof(t_indice), 1, arch);
        generarArchivoIndice(&(*pa)->der, arch);
    }

    return;
}

/** Sobreescribe el archivo indice.idx para que comience limpio
int generarArchivoIndice(t_arbol *pa, char * rutaIdx)
{
    FILE * arch;

    arch = fopen(rutaIdx, "wb");

    if (!arch)
        return ERROR_ABRIR;

    fclose(arch);

    inOrden(pa, guardarIndice);

    return SUCCESS;
}*/

/** Accion que adjunta un indice en el archivo */
int guardarIndice(const void *arg)
{
    FILE * arch;
    t_indice * idx = (t_indice *) arg;

    arch = fopen("indice.idx", "ab");

    if (!arch)
        return ERROR_ABRIR;

    fwrite(idx, sizeof(t_indice), 1, arch);

    fclose(arch);

    return SUCCESS;
}

/** Genera el archivo empleados ordenado a partir del indice */

int ordenarArchivoEmpleados(char * rutaEmp, char *rutaIdx, char *rutaOrd)
{
    FILE * archEmp, * archIdx, * archOrd;
    t_empleado emp;
    t_indice idx;

    //Abro ambos archivos

    archEmp = fopen(rutaEmp, "rb");

    if (!archEmp)
        return ERROR_ABRIR;

    archIdx = fopen(rutaIdx, "rb");

    if (!archIdx)
    {
        fclose(archEmp);
        return ERROR_ABRIR;
    }

    archOrd = fopen(rutaOrd, "wb");

    if (!archOrd)
    {
        fclose(archEmp);
        fclose(archOrd);
        return ERROR_ABRIR;
    }

    fread(&idx, sizeof(t_indice), 1, archIdx);

    while (!feof(archIdx))
    {
        //Nos movemos desp * cantBytes de registro
        fseek(archEmp, idx.numReg*sizeof(t_empleado), SEEK_SET);
        fread(&emp, sizeof(t_empleado), 1, archEmp);
        fwrite(&emp, sizeof(t_empleado), 1, archOrd);
        fread(&idx, sizeof(t_indice), 1, archIdx);
    }

    fclose(archOrd);
    fclose(archEmp);
    fclose(archIdx);

    return SUCCESS;
}


/** Funciones mostrar archivo */

int mostrarArchivoEmpleados(char * ruta)
{
    FILE * arch;
    t_empleado emp;

    arch = fopen(ruta, "rb");

    if (!arch)
        return ERROR_ABRIR;

    fread(&emp, sizeof(t_empleado), 1, arch);
    printf("Mostrando archivo %s: \n", ruta);

    while (!feof(arch))
    {
        printf("\nClave: %d\n", emp.clave);
        printf("Nombre: %s\n", emp.nombre);
        printf("Apellido: %s\n", emp.apellido);
        printf("Sueldo: %.3lf\n\n", emp.sueldo);
        fread(&emp, sizeof(t_empleado), 1, arch);
    }

    fclose(arch);

    return SUCCESS;
}

int mostrarIndice(char * ruta)
{
    FILE * arch;
    t_indice idx;

    arch = fopen(ruta, "rb");

    if (!arch)
        return ERROR_ABRIR;

    fread(&idx, sizeof(t_indice), 1, arch);
    printf("Mostrando archivo %s: \n", ruta);

    while (!feof(arch))
    {
        printf("\nClave: %d\n", idx.clave);
        printf("Registro: %d\n\n", idx.numReg);
        fread(&idx, sizeof(t_indice), 1, arch);
    }

    fclose(arch);

    return SUCCESS;
}
