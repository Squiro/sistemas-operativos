#include "funciones.h"

void mostrarElemento(int *mat, int filas, int columnas, int posX, int posY)
{
    int *pFil = mat;

    pFil += (posX*posY)-1;
    if (pFil > pFil+(filas-1) || *pFil > *pFil+(columnas-1))
    {
        printf("Out of bounds.");
    }
    else
        printf("El elemento es: %d", *pFil);

    /*int (*pFil)[COL] = mat;
    int *pCol;

    if (pFil+(posX-1) > pFil+(filas-1) || *pFil+(posY-1) > *pFil+(columnas-1))
    {
        printf("Out of bounds.");
    }
    else
    {
        //Aumentamos las posiciones de las "filas" (el aumento se hace por fila, o sea, si yo le aumento 2, estaria salteando DOS FILAS, incluyendo todas las dir de memo de las columnas)
        pFil += --posX;
        pCol = *pFil; //Igualamos la primera posicion de la fila con la primera posicion de la columna
        pCol += --posY; //Aumentamos las posiciones de las columnas
        printf("El elemento es: %d", *pCol);
    }*/
}


void mostrarMatriz(int *mat, int filas, int columnas)
{
    int *pFil = mat;

    while (pFil < mat+filas*columnas)
    {
        printf("\n %d \n", *pFil);
        pFil++;
    }
}
