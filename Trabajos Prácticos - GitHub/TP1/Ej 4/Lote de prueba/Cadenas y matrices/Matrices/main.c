#include "matrices.h"

/* Todos estos ejercicios son con matrices cuadradas.
*
*   a. Mostrar diagonal principal. (Solamente las mat cuadradas tienen diag. prin.) X
*   b. Mostrar diagonal secundaria. X
*   c. Triangulo superior X
        1. Incluyendo diagonal principal X
        2. No incluyendo la diagonal principal X
*   d. Triangulo superior de diagonal secundaria X
        1. Incluyendo a DS. X
        2. Sin incluir a DS. X
*   e. Triangulo inferior de la DP X
        1. Incluyendo a DP. X
        2. Sin incluir a DP. X
*   e. Triangulo inferior de la DS X
        1. Incluyendo a DS. X
        2. Sin incluir a DS. X
*
*   "Dividiendo" la matriz en 4 triangulos, luego:
*   g. T1 1. Incluyendo DIAGONALES. 2. Sin incluir DIAGONALES. X
*   h. T2 1. Incluyendo DIAGONALES. 2. Sin incluir DIAGONALES. X
*   i. T3 1. Incluyendo DIAGONALES. 2. Sin incluir DIAGONALES. X
*   j. T4 1. Incluyendo DIAGONALES. 2. Sin incluir DIAGONALES. X
*
*   Hacer otra variante ^ de esos que los muestre en el orden que aparecen realmente.
*
*   k. Producto de matrices.
*   l. Mostrar en espiral una matriz.
*   m. ¿Es simetrica respecto a DP?
        1. ¿Es matriz identidad?
        2. ¿Es matriz escalar?
*   n. ¿Es simetrica respecto a DS?
*   o. Trasponer sobre sí misma. (respecto a su diagonal principal).
*   p. 1. Idem pero con respecto a la diagonal secundaria.
       2. Trasponer con respecto al eje horizontal.
       3. Trasponer respecto al eje vertical.
       4. Trasponer con respecto al centro de la matriz.
*
*   q. Dado un ij
        1. Mostrar vecinos (celdas de alrededor) (Incluyendolo o sin incluirlo)
        2. Mostrar la maxima matriz cuadrada que tenga a ij como vertice superior izquierdo
        3. Mostrar la maxima matriz cuadrada que tenga a ij como vertice inferior derecho
        4. Mostrar la maxima matriz que tenga a ij como vertice (Variantes: cuadrada y no cuadrada, maxima y minima, ambas).
*/

//void mostrarMenu();

int main()
{
    //Recordar cambiar el define TAM si utilizamos alguna matriz de otro tamaño (definido en matrices.h)
    //int mat[FIL][COL] = { { 1, 2}, {2, 1} };  //2x2 simetrica DP
    //int mat[FIL][COL] = { {  1, 2, 3 }, { 4, 5, 6 } } //2x3 (no cuadrada)
    //int mat[FIL][COL] = { { 1, 2, 3}, {2, 3, 1} };  //3x3 simetrica DP
    /*int mat[FIL][COL] = { { 1, 2, 3, 1 },
                          { 5, 6, 1, 3 },
                          { 9, 1, 6, 2 },
                          { 1, 9, 5, 1} };*/ //4x4 simetrica DS
    //int mat[FIL][COL] = { { 1, 2, 3 }, { 4, 5, 6}, { 7, 8, 9} }; 3x3
    //int mat[FIL][COL] = { { 1, 0, 0 }, {0, 1, 0 }, { 0, 0 , 1 } }; //3x3 identidad
    int mat[FIL][COL] = { { 0, 1, 2, 3 }, { 4, 5, 6, 7 }, { 8, 9, 10, 11 }, { 12, 13, 14, 15 } }; //4x4
    //int mat[FIL][COL] = { { 0, 1, 2, 3, 4 }, { 5, 6, 7, 8, 9 }, { 10, 11, 12, 13, 14 }, { 15, 16, 17, 18, 19 }, { 20, 21, 22, 23, 24 } }; //5x5

    mostarDiagPrin(mat, TAM);
    mostrarDiagSec(mat, TAM);
    mostrarTriangSupDP(mat, TAM, 0); //Incluyendo diag principal
    mostrarTriangSupDP(mat, TAM, 1); //Sin incluir diag principal
    mostrarTriangSupDS(mat, TAM, 0); //Incluye diag secundaria
    mostrarTriangSupDS(mat, TAM, 1); //Sin incluir diag secundaria
    mostrarTriangInfDP(mat, TAM, 0); //Incluye diag principal
    mostrarTriangInfDP(mat, TAM, 1); //Sin incluir diag principal
    mostrarTriangInfDS(mat, TAM, 0); //Incluye diag secundaria
    mostrarTriangInfDS(mat, TAM, 1); //Sin incluir diag secundaria
    mostrarT1(mat, TAM, 0); //Incluyendo diagonales
    mostrarT1(mat, TAM, 1); //Sin incluir diagonales
    mostrarT2(mat, TAM, 0); //Incluyendo diagonales
    mostrarT2(mat, TAM, 1); //Sin incluir diagonales
    mostrarT3(mat, TAM, 0); //Incluyendo diagonales
    mostrarT3(mat, TAM, 1); //Sin incluir diagonales
    mostrarT4(mat, TAM, 0); //Incluyendo diagonales
    mostrarT4(mat, TAM, 1); //Sin incluir diagonales
    productoMatrices(mat, mat, TAM, TAM, TAM, TAM);
    mostrarEnEspiral(mat, TAM, TAM, 0, 0);

    if (simetricaDP(mat, TAM))
        printf("\n\nLa matriz es simetrica respecto a DP.\n");
    else
        printf("\n\nLa matriz no es simetrica respecto a DP.\n");
    if (simetricaDS(mat, TAM))
        printf("\nLa matriz es simetrica respecto a DS.\n");
    else
        printf("\nLa matriz no es simetrica respecto a DS.\n");
    if (esIdentidad(mat, TAM))
        printf("\nLa matriz es matriz identidad.\n");
    else
        printf("\nLa matriz no es matriz identidad.\n");
    if (esEscalar(mat, TAM))
        printf("\nLa matriz es matriz escalar.\n");
    else
        printf("\nLa matriz no es matriz escalar.\n");
    //trasponerRespDP(mat, TAM);
    //trasponerRespDS(mat, TAM);
    //trasponerHorizontal(mat, TAM);
    //trasponerVertical(mat, TAM);
    //trasponerCentro(mat, TAM);
    printf("\n\nMostrando vecinos de la posicion (%d, %d):", 1, 1);
    mostrarVecinos(mat, TAM, TAM, 1, 1, 0);
    printf("\n\nMostrando vecinos de la posicion (%d, %d):", 1, 1);
    mostrarVecinos(mat, TAM, TAM, 1, 1, 1);
    printf("\n\nMostrando maxima matriz cuadrada con vertice sup. izq. (%d, %d): ", 2, 2);
    maxMatVertSupIzq(mat, TAM, TAM, 2, 2);
    printf("\n\nMostrando maxima matriz cuadrada con vertice inf. der. (%d, %d): ", 2, 3);
    maxMatVertInfDer(mat, 2, 3);
    printf("\n\nMostrando maxima matriz cuadrada con vertice (%d, %d): ", 4, 1);
    maxMatCuad(mat, TAM, TAM, 2, 1);

    //mostrarMenu();
    return 0;
}

/*void mostrarMenu()
{
    char* titles[] = { "a. Mostrar diagonal principal. ", "b. "};

    printf("%s", titles[1]);
}*/
