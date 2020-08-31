#include <stdio.h>
#include <stdlib.h>
#define COL 100
#define FIL 100
#define TAM 4

/**
*   /!\ Atención: Todas estas funciones solucionan problemas encontrados en matrices cuadradas. Algunas de ellas pueden
*   adaptarse a situaciones de matrices no cuadradas, modificando en presunto caso el código, pero manteniendo lógica similar.
*/


/**
* Muestra la matriz.
*/
void mostrarMatriz(int mat[][COL], int filas, int colum);

/**
* Muestra la diagonal principal de una matriz.
*/
void mostarDiagPrin(int mat[][COL], int tam);

/**
* Muestra la diagonal secundaria de una matriz.
*/
void mostrarDiagSec(int mat[][COL], int tam);

/**
* Muestra el triangulo superior de una matriz respecto a su DP.
* El parametro inc define si se incluye a los elementos de la diagonal principal o no. 0 incluye, 1 no.
*/
void mostrarTriangSupDP(int mat[][COL], int tam, int inc);

/**
* Muestra el triangulo superior de una matriz respecto a su DS.
* El parametro inc define si se incluye a los elementos de la diagonal principal o no. 0 incluye, 1 no.
*/

void mostrarTriangSupDS(int mat[][COL], int tam, int inc);

/**
* Muestra el triangulo inferior de una matriz respecto a su DP.
* El parametro inc define si se incluye a los elementos de la diagonal principal o no. 0 incluye, 1 no.
*/

void mostrarTriangInfDP(int mat[][COL], int tam, int inc);

/**
* Muestra el triangulo inferior de una matriz respecto a su DS.
* El parametro inc define si se incluye a los elementos de la diagonal principal o no. 0 incluye, 1 no.
*/

void mostrarTriangInfDS(int mat[][COL], int tam, int inc);

/**
* Muestra el triangulo T1 de la matriz.
* El parametro inc define si se incluye a los elementos de la diagonal principal o no. 0 incluye, 1 no.
*/

void mostrarT1(int mat[][COL], int tam, int inc);

/**
* Muestra el triangulo T2 de la matriz.
* El parametro inc define si se incluye a los elementos de las diagonales o no. 0 incluye, 1 no.
*/

void mostrarT2(int mat[][COL], int tam, int inc);

/**
* Muestra el triangulo T3 de la matriz.
* El parametro inc define si se incluye a los elementos de las diagonales o no. 0 incluye, 1 no.
*/

void mostrarT3(int mat[][COL], int tam, int inc);

/**
* Muestra el triangulo T4 de la matriz.
* El parametro inc define si se incluye a los elementos de las diagonales o no. 0 incluye, 1 no.
*/

void mostrarT4(int mat[][COL], int tam, int inc);

/**
* Muestra el producto entre dos matrices.
*/
void productoMatrices(int mat[][COL], int mat2[][COL], int fil1, int col1, int fil2, int col2);

/**
* Muestra una matriz en espiral.
*/
void mostrarEnEspiral(int mat[][COL], int filas, int columnas, int startx, int starty);

/**
* Chequea si la matriz es simétrica respecto a la diagonal principal.
* Retorna un valor booleano.
* 0 = no es simetrica
* 1 = es simetrica
*/
int simetricaDP(int mat[][COL], int tam);

/**
* Chequea si la matriz es simétrica respecto a la diagonal secundaria.
* Retorna un valor booleano.
* 0 = no es simetrica
* 1 = es simetrica
*/
int simetricaDS(int mat[][COL], int tam);

/**
* Chequea si la matriz es matriz identidad.
* Retorna un valor booleano.
* 0 = no es identidad
* 1 = es identidad
*/
int esIdentidad(int mat[][COL], int tam);

/**
* Chequea si la matriz es matriz escalar.
* Retorna un valor booleano.
* 0 = no es identidad
* 1 = es identidad
*/
int esEscalar(int mat[][COL], int tam);

/**
* Chequea si los elementos de DE LA DP son todos iguales.
* Retorna un valor booleano.
* 0 = no son todos iguales
* 1 = son todos iguales
* PARAM:
*        mat: la matriz.
*        tam: el tamaño de la matriz.
*        num: el numero a comparar.
*/
int sonTodosIgualesDP(int mat[][COL], int tam, int num);

/**
* Chequea si los elementos de una matriz SIN SU DP son todos iguales.
* Retorna un valor booleano.
* 0 = no son todos iguales
* 1 = son todos iguales
* PARAM:
*        mat: la matriz.
*        tam: el tamaño de la matriz.
*        num: el numero a comparar.
*/
int sonTodosIgualesSinDP(int mat[][COL], int tam, int num);

/**
* Traspone a la matriz respecto a la DP.
*
*/
void trasponerRespDP(int mat[][COL], int tam);

/**
* Traspone a la matriz respecto a la DS.
*
*/
void trasponerRespDS(int mat[][COL], int tam);

/**
* Traspone a la matriz respecto eje horizontal
*
*/
void trasponerHorizontal(int mat[][COL], int tam);


/**
* Traspone a la matriz respecto eje vertical
*
*/
void trasponerVertical(int mat[][COL], int tam);

/**
* Traspone a la matriz respecto centro
*
*/
void trasponerCentro(int mat[][COL], int tam);

/**
* Dado una posicion X, Y, muestra los vecinos de una entrada (incluyendo los que se encuentran diagonalmente)
* 0 incluye, 1 no.
*
*/
void mostrarVecinos(int mat[][COL], int filas, int columnas, int posX, int posY, int inc);

/**
* Dado una posicion X, Y, muestra la maxima matriz cuadrada que se puede formar con el como vertice superior izquierdo
*
*/
void maxMatVertSupIzq(int mat[][COL], int filas, int columnas, int posX, int posY);

/**
* Dado una posicion X, Y, muestra la maxima matriz cuadrada que se puede formar con el como vertice inferior izquierdo
*
*/
void maxMatVertInfIzq(int mat[][COL], int filas, int columnas, int posX, int posY);

/**
* Dado una posicion X, Y, muestra la maxima matriz cuadrada que se puede formar con el como vertice inferior derecho
*
*/
void maxMatVertInfDer(int mat[][COL], int posX, int posY);

/**
* Dado una posicion X, Y, muestra la maxima matriz cuadrada que se puede formar con el como vertice superior derecho
*
*/
void maxMatVertSupDer(int mat[][COL], int filas, int columnas, int posX, int posY);

/**
* Dado una posicion X, Y, muestra la maxima matriz cuadrada que se puede formar con el como vertice
*
*/
void maxMatCuad(int mat[][COL], int filas, int columnas, int posX, int posY);
