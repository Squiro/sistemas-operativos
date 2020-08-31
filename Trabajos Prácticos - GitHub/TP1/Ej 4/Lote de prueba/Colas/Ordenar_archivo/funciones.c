#include "funciones.h"

int generarLote(char * ruta)
{
    FILE * arch;
    t_empleado emps[3] = { { 1, "Jose", 250 }, { 4, "Martin", 225 }, { 2, "Martina", 220 } };
    int i;

    arch = fopen(ruta, "wb");

    if (!arch)
        return ERROR_ARCH;

    for (i = 0; i < 3; i++)
        fwrite(&emps[i], sizeof(t_empleado), 1, arch);

    fclose(arch);

    return SUCCESS;
}

int guardarEnCola(t_cola *c, char * ruta)
{
    FILE * arch;
    t_empleado emp;

    arch = fopen(ruta, "rb");

    if (!arch)
        return ERROR_ARCH;

    fread(&emp, sizeof(t_empleado), 1, arch);

    while (!feof(arch))
    {
        acolar(c, &emp);
        fread(&emp, sizeof(t_empleado), 1, arch);
    }

    fclose(arch);

    return SUCCESS;
}

int ordenarCola(t_cola *c, t_cmp comparar)
{
    t_cola colaAux;
    t_empleado min, emp;

    crearCola(&colaAux);


    while (!colaVacia(c))
    {
        min = extraerMinimo(c);
        acolar(&colaAux, &min);
    }

    while (!colaVacia(&colaAux))
    {
        desacolar(&colaAux, &emp);
        acolar(c, &emp);
    }

    return SUCCESS;
}

t_empleado extraerMinimo(t_cola *c)
{
    t_empleado emp, minimo;
    t_cola colaAux;
    crearCola(&colaAux);

    desacolar(c, &minimo);

    while (!colaVacia(c))
    {
        desacolar(c, &emp);
        if (compararDNI(&emp, &minimo) > 0)
        {
            acolar(&colaAux, &minimo);
            minimo = emp;
        }
        else
            acolar(&colaAux, &emp);
    }

    while (!colaVacia(&colaAux))
    {
        desacolar(&colaAux, &emp);
        acolar(c, &emp);
    }

    return minimo;
}

int generarResultado(t_cola *c, char * ruta)
{
    FILE * arch;
    t_empleado emp;

    arch = fopen(ruta, "wb");

    if (!arch)
        return ERROR_ARCH;

    while (!colaVacia(c))
    {
        desacolar(c, &emp);
        fwrite(&emp, sizeof(t_empleado), 1, arch);
    }

    fclose(arch);

    return SUCCESS;
}


int mostrarArchivo(char * ruta)
{
    FILE * arch;
    t_empleado emp;

    arch = fopen(ruta, "rb");

    if (!arch)
        return ERROR_ARCH;

    fread(&emp, sizeof(t_empleado), 1, arch);

    while (!feof(arch))
    {
        printf("\nDNI: %d", emp.dni);
        printf("\nNombre: %s", emp.apyn);
        printf("\nSueldo: %0.3lf", emp.sueldo);
        printf("\n\n");
        fread(&emp, sizeof(t_empleado), 1, arch);
    }

    fclose(arch);

    return SUCCESS;
}

int compararDNI(const void *arg1, const void *arg2)
{
    t_empleado * emp1 = (t_empleado *) arg1, * emp2 = (t_empleado *) arg2;

    return emp1->dni - emp2->dni;
}
