#include "funciones.h"

//Muestra un elemento ij (enviando la matriz con punteros)
//Recorre toda una matriz con punteros

int main()
{
    int mat[FIL][COL] = { {1, 2, 3 }, { 4, 5, 6}, { 7, 8, 9}, { 10, 11, 12} };
    mostrarElemento(&mat, FIL, COL, 4, 3);
    mostrarMatriz(&mat, FIL, COL);
    return 0;
}
