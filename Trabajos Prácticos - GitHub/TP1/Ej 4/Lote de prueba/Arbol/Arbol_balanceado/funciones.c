#include "funciones.h"

int generarArbolBalanceado(t_arbol * pa, char * rutaIdx)
{
    FILE * archIdx;
    //int i = 0;

    archIdx = fopen(rutaIdx, "rb");

    if (!archIdx)
        return ERROR_ABRIR;

    //Obtengo la cantidad de elementos que voy a tener que guardar en el array
    fseek(archIdx, 0, SEEK_END); //Nos movemos al final
    int tam = ftell(archIdx)/sizeof(t_indice);//Dividimos la pos final por la cant de bytes

    /*t_indice arrIdx[tam];
    rewind(archIdx); //Rewindeamos

    fread(&arrIdx[i], sizeof(t_indice), 1, archIdx);

    while (!feof(archIdx))
    {
        i++;
        fread(&arrIdx[i], sizeof(t_indice), 1, archIdx);
    }*/

    insertarBalanceado(pa, archIdx, 0, tam-1);

    fclose(archIdx);

    return SUCCESS;
}
