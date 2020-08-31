#include "funciones.h"

//Carga por teclado los datos de un alumno
int cargarRegistro(t_alumno * alumno)
{
    //Si lo que esta inmediatamente a la izquierda es un puntero, usamos flecha. Si no, punto.
    printf("\nIngrese el DNI del alum (si es 0 fin ingreso): ");
    fflush(stdin);
    scanf("%d", &alumno->dni);

    if (!alumno->dni)
        return NO_INGRESO;

    printf("\nIngrese el nombre del alum: ");
    fflush(stdin);
    scanf("%s", &alumno->nombre);
    printf("\nIngrese el apellido del alum: ");
    fflush(stdin);
    scanf("%s", &alumno->apellido);
    printf("\nIngrese el sexo: ");
    fflush(stdin);
    scanf("%c", &alumno->sexo);

    do
    {
        printf("\nIngrese fecha de nac dd/mm/aa: ");
        fflush(stdin);
        scanf("%d/%d/%d", &alumno->nacimiento.dia, &alumno->nacimiento.mes, &alumno->nacimiento.anio);
    }
    while (!comprobarFecha(alumno->nacimiento));
    printf("\nIngrese el promedio: ");
    scanf("%f", &alumno->promedio);

    return INGRESO_OK;
}

void mostrarArchivo(FILE * arch)
{
    t_alumno alumno;
    fread(&alumno, sizeof(alumno), 1, arch);

    while (!feof(arch))
    {
        printf("\n\nDNI: %d", alumno.dni);
        printf("\nNombre: %s", alumno.nombre);
        printf("\nApellido: %s", alumno.apellido);
        printf("\nSexo: %c", alumno.sexo);
        printf("\nFecha de nacimiento: %d/%d/%d", alumno.nacimiento.dia, alumno.nacimiento.mes, alumno.nacimiento.anio);
        printf("\nPromedio: %0.2f", alumno.promedio);

        fread(&alumno, sizeof(alumno), 1, arch);
    }

    printf("\n\nSe alcanzo el fin del archivo. No hay mas registros para leer.");
//    fclose(arch);
//    return 0;

}

