#include "funciones.h"

int main()
{
    FILE * ptArch;
    t_alumno alumno;

    ptArch = fopen("alumnos.bin", "wb"); //Creamos el archivo

    if(!ptArch)
        exit(1);

    while (cargarRegistro(&alumno))
        fwrite(&alumno, sizeof(alumno), 1, ptArch);

    fclose(ptArch);
    system("CLS");

    ptArch = fopen("alumnos.bin", "rb");
    mostrarArchivo(ptArch);
    fclose(ptArch);

    return 0;
}
