#include "funciones.h"

int generarLote()
{
    t_empleado emps[] = { { 111, "Jose", "Polverini", 50.00 }, { 222, "Juan", "Perez", 120.30 }, { 333, "Dario", "Oirad", 400.25 } };
    FILE * arch;

    arch = fopen("empleados.bin", "wb");

    if (!arch)
    {
        printf("No se pudo abrir el archivo.");
        return ERROR_ABRIR;
    }

    fwrite(emps, sizeof(emps), 1, arch);

    fclose(arch);

    return 0;
}

//Hacer ambos archivos (long fija, long variable)
int convertirATxt()
{
    t_empleado emp;

    FILE * bin, *txt; //Cambiar a nombre a txtLv, agregar txtLF

    bin = fopen("empleados.bin", "rb");

    if (!bin)
    {
        printf("No se pudo abrir el archivo.");
        return ERROR_ABRIR;
    }

    txt = fopen("empleados.txt", "wt");

    if (!txt)
    {
        fclose(bin);
        printf("No se pudo abrir el archivo.");
        return ERROR_ABRIR;
    }

    fread(&emp, sizeof(t_empleado), 1, bin);

    while(!feof(bin))
    {
        //%06.2 ----> 6: cantidad de caracteres EN TOTAL (con el punto!)
        // ---------> 0: si la cantidad del numero a imprimir es menor, se le agregan 0 hasta completar
        //----------> .2: la precision es considerada DENTRO de la cantidad total (serian, 2 para la parte decimal, 1 para el punto, y 3 para la parte entera).
        fprintf(txt, "%8d%-*s%-*s%06.2lf\n", emp.dni, sizeof(emp.nombre), emp.nombre, sizeof(emp.apellido), emp.apellido, emp.sueldo);
        //fprintf(txt, "%-*.*Polverini                                         s", 50, 50, emp.nombre);
        fread(&emp, sizeof(t_empleado), 1, bin);
    }
    fclose(bin);
    fclose(txt);

    return 0;
}

int leerTxt()
{
    t_empleado emp;
    char datos[512];

    FILE * bin, *txt; //Cambiar a nombre a txtLv, agregar txtLF

    bin = fopen("empleados_longfija.bin", "wb");

    if (!bin)
    {
        printf("No se pudo abrir el archivo.");
        return ERROR_ABRIR;
    }

    txt = fopen("empleados.txt", "rt");


    //fgets(datos, 9, txt); fgets usado de forma ineficiente (ver abajo)
    fgets(datos, 512, txt);

    while(!feof(txt))
    {
        procesarLinea(datos, &emp);
        /* Esto es altamente ineficiente, porque estamos llamando al archivo cada vez que queremos buscar un pedacito de linea.
        Lo mejor es leer una linea, y procesarla, al estilo de long. variable.

        emp.dni = atoi(datos);
        fgets(emp.nombre, sizeof(emp.nombre), txt);
        fgets(emp.apellido, sizeof(emp.nombre), txt);
        fgets(datos, 256, txt);
        emp.sueldo = atof(datos);
        fgets(datos, 9, txt);*/

        /*printf("\n\nDNI: %d", emp.dni);
        printf("\nNOM: %s", emp.nombre);
        printf("\nAP: %s", emp.apellido);
        printf("\nSUELDO: %.2lf", emp.sueldo); */
        fwrite(&emp, sizeof(t_empleado), 1, bin);
        fgets(datos, 512, txt);
    }

    //fprintf(txt, "%8d%-*s%-*s%5.2lf\n", emp.dni, sizeof(emp.nombre), emp.nombre, sizeof(emp.apellido), emp.apellido, emp.sueldo);
    //fprintf(txt, "%-*.*s", 50, 50, emp.nombre);
    //fread(&emp, sizeof(t_empleado), 1, bin);

    fclose(bin);
    fclose(txt);

    return 0;
}

int procesarLinea(char *linea, t_empleado *emp)
{
    char *aux;

    aux = strchr(linea, '\n');
    //Si hubo algun problema al leer la linea, salimos rajando de aca
    if (!aux)
        return LINEA_MAL;
    *aux = '\0';
    //Nos movemos la cantidad de caracteres que tiene nuestro "sueldo" (definida por el formato que le dimos mas arriba)
    aux -= 6;
    sscanf(aux, "%f", &emp->sueldo);
    *aux = '\0';
    //Nos movemos la cantidad fija de caracteres de nuestra cadena
    aux -= sizeof(emp->nombre);
    //Sacamos los espacios innecesarios que tenga esta cadena (si los hay)
    sacarEspacios(aux);
    strcpy(emp->apellido, aux);
    *aux = '\0';
    aux -= sizeof(emp->apellido);
    sacarEspacios(aux);
    strcpy(emp->nombre, aux+1);
    *aux = '\0';
    //Leemos el resto de lo que queda de la linea
    sscanf(linea, "%d", &emp->dni);

    return 0;
}

//Lo que hacemos es buscar la ultima ocurrencia del caracter terminador y, desde ahi, empezar a verificar
//si hay espacios o no
int sacarEspacios(char *linea)
{
    linea = strrchr(linea, '\0');

    while (*(linea-1) == ' ')
        linea--;

    //seteamos el caracter nulo para acortar la cadena
    *linea = '\0';

    return 0;
}
