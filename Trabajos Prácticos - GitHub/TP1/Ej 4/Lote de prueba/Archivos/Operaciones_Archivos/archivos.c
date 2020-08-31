#include "archivos.h"

int generarLoteA()
{
    t_empleado emps[] = { { 111, "Jose", "Polverini", 250.00 }, { 222, "Juan", "Perez", 120.30 }, { 333, "Dario", "Oirad", 400.25 } };
    FILE * arch;

    arch = fopen("empleados_a.bin", "wb");

    if (!arch)
    {
        printf("No se pudo abrir el archivo.");
        return ERROR_ABRIR;
    }

    fwrite(emps, sizeof(emps), 1, arch);

    fclose(arch);

    return 0;
}

int generarLoteB()
{
    t_empleado emps[] = { { 111, "Jose", "Polverini", 250.00 }, { 444, "Ramiro", "Webber", 563.30 }, { 333, "Dario", "Oirad", 400.25 }, { 555, "Estefan", "Estefano", 679.90 } };
    FILE * arch;

    arch = fopen("empleados_b.bin", "wb");

    if (!arch)
    {
        printf("No se pudo abrir el archivo.");
        return ERROR_ABRIR;
    }

    fwrite(emps, sizeof(emps), 1, arch);

    fclose(arch);

    return 0;
}

int diferenciaEntre(char *ruta1, char *ruta2)
{
    FILE * arch_A, * arch_B, * destino;
    t_empleado empleado_A, empleado_B;
    int guardar = 1;

    arch_A = fopen(ruta1, "rb");

    if (!arch_A)
    {
        printf("No se pudo abrir el archivo %s", ruta1);
        return ERROR_ABRIR;
    }

    arch_B = fopen(ruta2, "rb");

    if (!arch_B)
    {
        printf("No se pudo abrir el archivo %s", ruta1);
        fclose(arch_A); //Cerramos el anterior archivo
        return ERROR_ABRIR;
    }

    destino = fopen("diferencia.bin", "wb");

    if (!destino)
    {
        printf("No se pudo abrir el archivo.");
        fclose(arch_A);
        fclose(arch_B);
        return ERROR_ABRIR;
    }
    //La diferencia consiste en aggarrar todos los del primer conjunto que no estén en el segundo

    printf("Realizando diferencia entre '%s' y '%s'", ruta1, ruta2);

    fread(&empleado_A, sizeof(t_empleado), 1, arch_A);
    fread(&empleado_B, sizeof(t_empleado), 1, arch_B);

    while (!feof(arch_A))
    {
        //Recorremos todo el archivo B y comparamos por sobre el mismo registro de A, para asegurarnos que realmente no esté en B
        while (!feof(arch_B) && guardar)
        {
            //Si son iguales, seteamos guardar en 0 y salimos del ciclo
            if (compararRegistros(&empleado_A, &empleado_B))
                guardar = 0;

            fread(&empleado_B, sizeof(t_empleado), 1, arch_B);
        }

        if (guardar)
            fwrite(&empleado_A, sizeof(t_empleado), 1, destino);

        guardar = 1;
        rewind(arch_B);
        fread(&empleado_A, sizeof(t_empleado), 1, arch_A);
    }

    fclose(arch_A);
    fclose(arch_B);
    fclose(destino);

    mostrarArchivo("diferencia.bin");

    return 0;
}

int compararRegistros(t_empleado *regA, t_empleado *regB)
{
    if (regA->dni == regB->dni && !strcmp(regA->nombre, regB->nombre) && !strcmp(regA->apellido, regB->apellido) && regA->sueldo == regB->sueldo)
        return 1;
    else
        return 0;
}

void mostrarArchivo(char *ruta)
{
    FILE * arch;
    t_empleado emp;

    arch = fopen(ruta, "rb");

    fread(&emp, sizeof(t_empleado), 1, arch);

    while (!feof(arch))
    {
        printf("\n\nDNI: %d", emp.dni);
        printf("\nNombre: %s", emp.nombre);
        printf("\nApellido: %s", emp.apellido);
        printf("\nSueldo: %f", emp.sueldo);
        fread(&emp, sizeof(t_empleado), 1, arch);
    }

    printf("\n\n");
    fclose(arch);
}

int intersecEntre(char *ruta1, char *ruta2)
{
    FILE * arch_A, * arch_B, * destino;
    t_empleado empleado_A, empleado_B;
    int guardar = 0;

    arch_A = fopen(ruta1, "rb");

    if (!arch_A)
    {
        printf("No se pudo abrir el archivo %s", ruta1);
        return ERROR_ABRIR;
    }

    arch_B = fopen(ruta2, "rb");

    if (!arch_B)
    {
        printf("No se pudo abrir el archivo %s", ruta1);
        fclose(arch_A); //Cerramos el anterior archivo
        return ERROR_ABRIR;
    }

    destino = fopen("intersec.bin", "wb");

    if (!destino)
    {
        printf("No se pudo abrir el archivo.");
        fclose(arch_A);
        fclose(arch_B);
        return ERROR_ABRIR;
    }
    //La interseccion consiste en aggarrar todos los del primer conjunto que estén en el segundo

    printf("Realizando interseccion entre '%s' y '%s'", ruta1, ruta2);

    fread(&empleado_A, sizeof(t_empleado), 1, arch_A);
    fread(&empleado_B, sizeof(t_empleado), 1, arch_B);

    while (!feof(arch_A))
    {
        //Recorremos todo el archivo B y comparamos por sobre el mismo registro de A, para asegurarnos que realmente esté en B
        while (!feof(arch_B) && !guardar)
        {
            //Si son iguales, seteamos guardar en 1 y salimos del ciclo
            if (compararRegistros(&empleado_A, &empleado_B))
                guardar = 1;

            fread(&empleado_B, sizeof(t_empleado), 1, arch_B);
        }

        if (guardar)
            fwrite(&empleado_A, sizeof(t_empleado), 1, destino);

        guardar = 0;
        rewind(arch_B);
        fread(&empleado_A, sizeof(t_empleado), 1, arch_A);
    }

    fclose(arch_A);
    fclose(arch_B);
    fclose(destino);

    mostrarArchivo("intersec.bin");

    return 0;
}

int unionEntre(char *ruta1, char *ruta2)
{
    FILE * arch_A, * arch_B, * destino;
    t_empleado empleado_A, empleado_B;
    int guardar = 1;

    arch_A = fopen(ruta1, "rb");

    if (!arch_A)
    {
        printf("No se pudo abrir el archivo %s", ruta1);
        return ERROR_ABRIR;
    }

    arch_B = fopen(ruta2, "rb");

    if (!arch_B)
    {
        printf("No se pudo abrir el archivo %s", ruta1);
        fclose(arch_A); //Cerramos el anterior archivo
        return ERROR_ABRIR;
    }

    destino = fopen("union.bin", "wb+");

    if (!destino)
    {
        printf("No se pudo abrir el archivo.");
        fclose(arch_A);
        fclose(arch_B);
        return ERROR_ABRIR;
    }
    //La interseccion consiste en aggarrar todos los del primer conjunto que estén en el segundo

    printf("Realizando union entre '%s' y '%s'", ruta1, ruta2);

    fread(&empleado_A, sizeof(t_empleado), 1, arch_A);
    //Guardamos todos los de un archivo primero
    while (!feof(arch_A))
    {
        fwrite(&empleado_A, sizeof(t_empleado), 1, destino);
        fread(&empleado_A, sizeof(t_empleado), 1, arch_A);
    }

    rewind(destino);
    fread(&empleado_B, sizeof(t_empleado), 1, arch_B);
    fread(&empleado_A, sizeof(t_empleado), 1, destino);
    while (!feof(arch_B))
    {
        while (!feof(destino) && guardar)
        {
            if(compararRegistros(&empleado_B, &empleado_A))
                guardar = 0;
            fread(&empleado_A, sizeof(t_empleado), 1, destino);
        }

        if (guardar)
        {
            fseek(destino, 0, SEEK_END);
            fwrite(&empleado_B, sizeof(t_empleado), 1, destino);
        }
        rewind(destino);
        guardar = 1;
        fread(&empleado_B, sizeof(t_empleado), 1, arch_B);
    }


    fclose(arch_A);
    fclose(arch_B);
    fclose(destino);

    mostrarArchivo("union.bin");

    return 0;
}
