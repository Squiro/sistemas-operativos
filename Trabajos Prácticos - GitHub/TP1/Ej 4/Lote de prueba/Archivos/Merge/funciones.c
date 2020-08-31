#include "funciones.h"

int generarLoteMaestro()
{
    t_alumno alums[] = { { 123, "Agustin", "Alvaro", 'M' },
                 { 234, "Baltazar", "Benitez", 'M' },
                 { 456, "Carlotes", "Carlota", 'F' }};

    FILE * arch;

    arch = fopen("maestro.bin", "wb");

    if (!arch)
    {
        printf("No se pudo abrir el archivo, hubo un error, el try catch no funciono.");
        return ERROR_ABRIR;
    }

    fwrite(&alums, sizeof(alums), 1, arch);

    fclose(arch);

    return SUCCESS;
}

int generarLoteNovedades()
{
    t_novedad alums[] = { { 123, "Agustina", "Alvaro", 'F', MODIF },
                  { 233, "Juancito", "Cenitez", 'M', ALTA },
                  { 456, "Carlotes", "Carlota", 'F', BAJA },
                  { 503, "Alesio", "Sinopoli", 'M', ALTA },
                  { 999, "Manuel", "Alderete", 'F', BAJA } };

    FILE * arch;

    arch = fopen("novedades.bin", "wb");

    if (!arch)
    {
        printf("No se pudo abrir el archivo, hubo un error, el try catch no funciono.");
        return ERROR_ABRIR;
    }

    fwrite(&alums, sizeof(alums), 1, arch);

    fclose(arch);

    return SUCCESS;
}

int actualizarMaestro()
{
    FILE * maestro;
    FILE * novedad;
    FILE * maestAct;
    t_novedad nov;
    t_alumno alum;

    maestro = fopen("maestro.bin", "rb");

    if (!maestro)
    {
        printf("No se pudo abrir el archivo, hubo un error, el try catch no funciono.");
        return ERROR_ABRIR;
    }

    novedad = fopen("novedades.bin", "rb");

    if (!novedad)
    {
        printf("No se pudo abrir el archivo, hubo un error, el try catch no funciono.");
        fclose(maestro);
        return ERROR_ABRIR;
    }

    maestAct = fopen("maestroAct.bin", "wb");

    if (!maestAct)
    {
        printf("No se pudo abrir el archivo, hubo un error, el try catch no funciono.");
        return ERROR_ABRIR;
    }

    fread(&nov, sizeof(t_novedad), 1, novedad);
    fread(&alum, sizeof(t_alumno), 1, maestro);

    while (!feof(novedad))
    {
        if (nov.dni <= alum.dni || feof(maestro))
        {
            //Nos fijamos que hay que hacer
            switch(nov.tipo)
            {
            case ALTA: darAlta(&nov, &alum, maestAct);
                fread(&nov, sizeof(t_novedad), 1, novedad);
                break;

            case BAJA: if (nov.dni == alum.dni)
                {
                    fread(&nov, sizeof(t_novedad), 1, novedad);
                    fread(&alum, sizeof(t_alumno), 1, maestro);
                }
                else
                {
                    printf("\nError al dar de baja. No existe alumno con DNI: %d. a dif de %d \n", nov.dni, alum.dni);
                    writeError(BAJA, &nov);
                    fread(&nov, sizeof(t_novedad), 1, novedad);
                }
                break;

            case MODIF: if(!darModif(&nov, &alum, maestAct))
                {
                    fread(&alum, sizeof(t_alumno), 1, maestro);
                }
                fread(&nov, sizeof(t_novedad), 1, novedad);
                break;
            }
        }
        else
        {
            //printf("hola");
            fwrite(&alum, sizeof(t_alumno), 1, maestAct);
            fread(&alum, sizeof(t_alumno), 1, maestro);
        }
    }

    fclose(maestro);
    fclose(novedad);
    fclose(maestAct);

    return SUCCESS;
}

int darModif(t_novedad *nov, t_alumno *alum, FILE * maestAct)
{
    if (nov->dni == alum->dni)
    {
        strcpy(alum->nombre, nov->nombre);
        strcpy(alum->apellido, nov->apellido);
        alum->sexo = nov->sexo;
        fwrite(alum, sizeof(t_alumno), 1, maestAct);
    }
    else
    {
        printf("Error al modificar al alumno con DNI: %d.", alum->dni);
        if (!writeError(MODIF, nov))
            return ERROR_ABRIR;

        return ERROR;
    }

    return SUCCESS;
}

int darAlta(t_novedad *nov, t_alumno *alum, FILE * maestAct)
{
    t_alumno nuevoAlum;

    if (nov->dni != alum->dni)
    {
        nuevoAlum.dni = nov->dni;
        strcpy(nuevoAlum.nombre, nov->nombre);
        strcpy(nuevoAlum.apellido, nov->apellido);
        nuevoAlum.sexo = nov->sexo;
        //t_alumno nuevoAlum = { nov->dni, nov->nombre, nov->apellido, nov->sexo };
        fwrite(&nuevoAlum, sizeof(t_alumno), 1, maestAct);
    }
    else
    {
        printf("Error al dar de alta al alumno con DNI: %d.", nov->dni);
        if (!writeError(ALTA, nov))
            return ERROR_ABRIR;

        return ERROR;
    }

    return SUCCESS;
}

int writeError(int tipo, t_novedad * nov)
{
    FILE * log;
    t_error error;

    log = fopen("error.bin", "wb");

    if (!log)
    {
        printf("No se pudo abrir el archivo, hubo un error, el try catch no funciono.");
        return ERROR_ABRIR;
    }

    switch(tipo)
    {
    case ALTA: strcpy(error.msg, "Alumno ya existente.");
                error.nov.dni = nov->dni;
                strcpy(error.nov.nombre, nov->nombre);
                strcpy(error.nov.apellido, nov->apellido);
                error.nov.sexo = nov->sexo;
        break;

    case BAJA: strcpy(error.msg, "Alumno no existente.");
                error.nov.dni = nov->dni;
                strcpy(error.nov.nombre, nov->nombre);
                strcpy(error.nov.apellido, nov->apellido);
                error.nov.sexo = nov->sexo;
        break;

    case MODIF: strcpy(error.msg, "Alumno no existente.");
                error.nov.dni = nov->dni;
                strcpy(error.nov.nombre, nov->nombre);
                strcpy(error.nov.apellido, nov->apellido);
                error.nov.sexo = nov->sexo;
        break;
    }

    fwrite(&error, sizeof(t_error), 1, log);

    fclose(log);

    return SUCCESS;
}

int mostrarMaestro()
{
    FILE * maestAct;
    t_alumno alumno;

    maestAct = fopen("maestroAct.bin", "rb");

    if (!maestAct)
    {
        printf("No se pudo abrir el archivo, hubo un error, el try catch no funciono.");
        return ERROR_ABRIR;
    }

    fread(&alumno, sizeof(t_alumno), 1, maestAct);
    printf("\nMostrando el archivo maestro actualizado... \n");
    while (!feof(maestAct))
    {
        printf("\n\nDNI: %d | AP: %s | Nom: %s | Sexo: %c", alumno.dni, alumno.apellido, alumno.nombre, alumno.sexo);
        fread(&alumno, sizeof(t_alumno), 1, maestAct);
    }

    fclose(maestAct);

    return SUCCESS;
}

int mostrarError()
{
    FILE * log;
    t_error logError;

    log = fopen("error.bin", "rb");

    if (!log)
    {
        printf("No se pudo abrir el archivo, hubo un error, el try catch no funciono.");
        return ERROR_ABRIR;
    }

    fread(&logError, sizeof(t_error), 1, log);

    printf("Mostrando el archivo de error... \n");
    while (!feof(log))
    {
        printf("\n\nDNI: %d | AP: %s | Nom: %s | Sexo: %c | Tipo: %d | Error: %s", logError.nov.dni, logError.nov.apellido, logError.nov.nombre, logError.nov.sexo, logError.nov.tipo, logError.msg);
        fread(&logError, sizeof(t_error), 1, log);
    }

    fclose(log);

    return SUCCESS;
}
