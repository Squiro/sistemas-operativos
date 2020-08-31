#include "funciones.h"

int generarLote()
{
    t_empleado emps[] = { { 111, "Jose", "Polverini", 250.00 }, { 222, "Juan", "Perez", 120.30 }, { 333, "Dario", "Oirad", 400.25 } };
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

int convertirATxt()
{
    t_empleado emp;

    FILE * bin, *txt;

    bin = fopen("empleados.bin", "rb");

    if (!bin)
    {
        printf("No se pudo abrir el archivo.");
        return ERROR_ABRIR;
    }

    txt = fopen("empleados.txt", "w");

    if (!txt)
    {
        fclose(bin);
        printf("No se pudo abrir el archivo.");
        return ERROR_ABRIR;
    }

    fread(&emp, sizeof(t_empleado), 1, bin);

    while(!feof(bin))
    {
        fprintf(txt, "%d;%s;%s;%07.3lf\n", emp.dni, emp.nombre, emp.apellido, emp.sueldo);
        fread(&emp, sizeof(t_empleado), 1, bin);
    }
    fclose(bin);
    fclose(txt);

    return 0;
}

int convertirABin()
{
    FILE * bin, *txt;
    t_empleado emp;
    char datos[512];
    //char *aux;
    //char *pDatos;

    bin = fopen("convertido.bin", "w+b");

    if (!bin)
    {
        printf("No se pudo abrir el archivo.");
        return ERROR_ABRIR;
    }

    txt = fopen("empleados.txt", "r");

    if (!txt)
    {
        fclose(bin);
        printf("No se pudo abrir el archivo.");
        return ERROR_ABRIR;
    }

    fgets(datos, 512, txt);

    while (!feof(txt))
    {
        //Esta es otra forma de hacerlo, pero el problema que tiene es que los simbolos excluyentes del fscanf no son estandar para todas
        //las implementaciones
        //%[^;] -> lo unico no valido para leer
        //%[;] -> lo unico permitido para leer
        //los ; que aparecen son salteados
        //fscanf(txt, "%d;%[^;];%[^;];%.2lf", &emp.dni, &emp.nombre, &emp.apellido, &emp.sueldo);

        /* Esta es otra forma. Notar como usamos atof y atoi para guardar algunos datos, a diferencia de la funcion procesarLinea.

        *aux = strchr(datos, '\n');
        *aux = '\0';
        aux = strrchr(datos, ';');
        emp.sueldo = atof(aux+1);
        *aux = '\0';
        aux = strrchr(datos, ';');
        strcpy(emp.apellido, aux+1);
        *aux = '\0';
        aux = strrchr(datos, ';');
        strcpy(emp.nombre, aux+1);
        *aux = '\0';
        emp.dni = atoi(datos);*/

        procesarLinea(datos, &emp);
        fwrite(&emp, sizeof(t_empleado), 1, bin);
        fgets(datos, 512, txt);
    }

    /* Esta forma utiliza el strtok.

    pDatos = strtok(datos, ";");

    while (!feof(txt))
    {
        emp.dni = atoi(pDatos);
        strcpy(emp.nombre, strtok(NULL, ";"));
        strcpy(emp.apellido, strtok(NULL, ";"));
        emp.sueldo = atof(strtok(NULL, ";"));
        //Obtenemos el proximo empleado
        fgets(datos, 512, txt);
        pDatos = strtok(datos, ";");
        //Guardamos el empleado obtenido anteriormente en el nuevo bin
        fwrite(&emp, sizeof(t_empleado), 1, bin);
    }*/

    rewind(bin);
    mostrarArchivo(bin);
    fclose(txt);
    fclose(bin);

    return 0;
}

// Y esta es, sí, otra forma más. A diferencia de la anterior que se encuentra en el while, usamos sscanf para guardar formatos de cierto tipo.
int procesarLinea(char *linea, t_empleado *emp)
{
    char *aux;

    aux = strchr(linea, '\n');
    if (!aux)
        return LINEA_MAL;
    *aux = '\0';
    aux = strrchr(linea, ';');
    sscanf(aux, "%f", &emp->sueldo);
    *aux = '\0';
    aux = strrchr(linea, ';');
    strcpy(emp->apellido, aux+1);
    *aux = '\0';
    aux = strrchr(linea, ';');
    strcpy(emp->nombre, aux+1);
    *aux = '\0';
    sscanf(linea, "%d", &emp->dni);

    return 0;
}

void mostrarArchivo(FILE * arch)
{
    t_empleado emp;
    fread(&emp, sizeof(t_empleado), 1, arch);

    while (!feof(arch))
    {
        printf("\n\nDNI: %d", emp.dni);
        printf("\nNombre: %s", emp.nombre);
        printf("\nApellido: %s", emp.apellido);
        printf("\nSueldo: %.3lf", emp.sueldo);

        fread(&emp, sizeof(t_empleado), 1, arch);
    }
}
