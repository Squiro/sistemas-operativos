#include "matrices.h"


void mostrarMatriz(int mat[][COL], int filas, int colum)
{
    int i, j;

    for(i = 0; i < filas; i++)
        for (j = 0; j < colum; j++)
            printf("%d ", mat[i][j]);
}

void mostarDiagPrin(int mat[][COL], int tam)
{
    int i;

    printf("Mostrando la diagonal principal: ");

    for (i = 0; i < tam; i++)
    {
        printf("%d ", mat[i][i]);
    }
    printf("\n\n");
}

void mostrarDiagSec(int mat[][COL], int tam)
{
    int i, j;

    printf("Mostrando la diagonal secundaria: ");

    for (i = 0, j = tam-1; i < tam; i++, j--)
        printf("%d ", mat[i][j]);

    printf("\n\n");
}

void mostrarTriangSupDP(int mat[][COL], int tam, int inc)
{
    int i, j = tam -1;

    if (!inc)
        printf("Mostrando triangulo superior incluyendo diag principal: ");
    else
        printf("Mostrando triangulo superior sin incluir diag principal: ");

    for (i = 0; i < tam; i++)
        for (j = i+inc; j < tam; j++)
            printf("%d ", mat[i][j]);

    printf("\n\n");
}

void mostrarTriangSupDS(int mat[][COL], int tam, int inc)
{
    int i, j;

    if (!inc)
        printf("Mostrando triangulo superior incluyendo diag secundaria: ");
    else
        printf("Mostrando triangulo superior sin incluir diag secundaria: ");

    for (i = 0; i < tam; i++)
        for (j = 0; j < (tam-i) - inc; j++)
            printf("%d ", mat[i][j]);

    printf("\n\n");
}

void mostrarTriangInfDP(int mat[][COL], int tam, int inc)
{
    int i, j;

    if (!inc)
        printf("Mostrando triangulo inferior incluyendo diag principal: ");
    else
        printf("Mostrando triangulo inferior sin incluir diag principal: ");

    for (i = 0; i < tam; i++)
        for (j = 0; j <= i - inc; j++)
            printf("%d ", mat[i][j]);

    printf("\n\n");
}

void mostrarTriangInfDS(int mat[][COL], int tam, int inc)
{
    int i, j;

    if (!inc)
        printf("Mostrando triangulo inferior incluyendo diag secundaria: ");
    else
        printf("Mostrando triangulo inferior sin incluir diag secundaria: ");

    for (i = 0; i < tam; i++)
        for (j = (tam-1)-i + inc; j < tam; j++)
            printf("%d ", mat[i][j]);

    printf("\n\n");
}

void mostrarT1(int mat[][COL], int tam, int inc)
{
    int i, j;

    if (!inc)
        printf("Mostrando triangulo T1 incluyendo diagonales: ");
    else
        printf("Mostrando triangulo T1 sin incluir diagonales: ");

    for (i = 0; i < tam/2; i++)
        for (j = i + inc; j < tam-i - inc; j++)
            printf("%d ", mat[i][j]);

    printf("\n\n");
}

void mostrarT2(int mat[][COL], int tam, int inc)
{
    int i, j;

    if (!inc)
        printf("Mostrando triangulo T2 incluyendo diagonales: ");
    else
        printf("Mostrando triangulo T2 sin incluir diagonales: ");

    for (i = tam/2; i < tam; i++)
        for (j = (tam-i)-1 + inc; j <= i - inc; j++)
            printf("%d ", mat[j][i]);

    printf("\n\n");
}

void mostrarT3(int mat[][COL], int tam, int inc)
{
    int i, j;

    if (!inc)
        printf("Mostrando triangulo T3 incluyendo diagonales: ");
    else
        printf("Mostrando triangulo T3 sin incluir diagonales: ");

    for (i = tam/2; i < tam; i++)
        for (j = (tam-i)-1 + inc; j <= i - inc; j++)
            printf("%d ", mat[i][j]);

    printf("\n\n");
}

void mostrarT4(int mat[][COL], int tam, int inc)
{
    int i, j;

    if (!inc)
        printf("Mostrando triangulo T4 incluyendo diagonales: ");
    else
        printf("Mostrando triangulo T4 sin incluir diagonales: ");

    for (i = 0; i < tam/2; i++)
        for (j = i + inc; j < tam-i - inc; j++)
            printf("%d ", mat[j][i]); //Recorremos por columnas

    printf("\n\n");
}

void productoMatrices(int mat[][COL], int mat2[][COL], int fil1, int col1, int fil2, int col2)
{
    int i, j, k, res[FIL][COL];

    printf("Producto entre matrices: ");
    //i < f1
    for (i = 0; i < fil1; i++)
    {
        //j < col2
        for (j = 0; j < col2; j++)
        {
            //k < col1 o k < fil2
            for (k = 0; k < fil2; k++)
                res[i][j] += mat[i][k] * mat2[k][j];

            //printf(" %d ", acum);
        }
    }
    //El tamaño de la matriz resultado va a ser filas1 por column2
    mostrarMatriz(res, fil1, col2);
}

void mostrarEnEspiral(int mat[][COL], int filas, int columnas, int startx, int starty)
{
    int i;

    printf("\n\nMostrando en espiral: ");

    //Ejecutamos mientras que la cantidad de posiciones (col-1, fil-1) menos el start sea mayor que 0
    while ((columnas-1)-starty > 0 && (filas-1)-startx > 0)
    {
        //Imprimo los valores de izquierda a derecha
        for (i = startx; i < columnas; i++)
            printf(" %d ", mat[starty][i]);

        //Imprimo de arriba a abajo
        //starty + 1 porque el primer elemento de la columna ya fue impreso por el anterior for
        for (i = starty + 1; i < filas; i++)
            printf(" %d ", mat[i][columnas-1]);

        //Ya imprimimos una columna entera y no necesitamos mas el valor viejo de cant de columnas, restamos 1
        columnas--;

        //Imprimo de derecha a izquierda
        //columnas - 1 porque el ultimo elemento de la columna ya fue impreso por el for anterior
        for (i = columnas - 1; i > startx; i--)
            printf(" %d ", mat[filas-1][i]);

        //Imprimo de abajo a arriba
        //filas - 1 porque el primer elemento de la ultima fila ya fue impreso por el for anterior
        for (i = filas - 1; i > starty; i--)
            printf(" %d ", mat[i][startx]);

        filas--;
        //Necesitamos aumentarle en 1 a startx e starty para que pasen al proximo elemento y no haga un bucle estupido
        startx++;
        starty++;
    }
}

/*
    La matriz será simétrica si todos los elementos que no pertenezcan a la diagonal principal son iguales a sus "opuestos" (los que están del otro lado). Aij = Aji
*/
int simetricaDP(int mat[][COL], int tam)
{
    int i, j;

    for (i = 0; i < tam/2; i++)
        for (j = 0; j < tam; j++)
            if (i != j && mat[i][j] != mat[j][i])
                return 0; //En caso de que hallemos un elemento que no sea igual, retornamos 0

    return 1;
}

/*
    La matriz va a ser simetrica respecto a su diagonal secundaria si y solo si, siendo n = tamaño, A(i,j) = A(n-j+1,n-i+1)
    Persymmetric matrix.
*/
int simetricaDS(int mat[][COL], int tam)
{
    int i, j;

    for (i = 0; i < tam; i++)
        for (j = 0; j < tam; j++)
            if (mat[i][j] != mat[tam-(j+1)][tam-(i+1)])
            {
                //printf("Explote acá. POS i: %d, POS j: %d", mat[i][j], mat[tam-(j+1)][tam-(i+1)]);
                return 0; //En caso de que hallemos un elemento que no sea igual, retornamos 0

            }
    return 1;
}

/*
    La matriz va a ser matriz identidad si todos los números de su diagonal princpal son igual 1, y todos los demás son 0.
*/
int esIdentidad(int mat[][COL], int tam)
{
    //Antes que nada, chequeamos que todos los elementos de la diagonal principal sean 1. Si no lo son, efectivamente
    //no es identidad.
    if (sonTodosIgualesDP(mat, tam, 1))
        if(sonTodosIgualesSinDP(mat, tam, 0))
            return 1;
        else
            return 0;
    else
        return 0;
}

/*
    La matriz va a ser matriz escalar si todos los números de su diagonal princpal son igual n, y todos los demás son 0.
*/
int esEscalar(int mat[][COL], int tam)
{
    //Antes que nada, chequeamos que todos los elementos de la diagonal principal sean n = A(0,0). Si no lo son, efectivamente
    //no es escalar.
    if (sonTodosIgualesDP(mat, tam, mat[0][0]) && mat[0][0] != 1 && mat[0][0] != 0)
        if(sonTodosIgualesSinDP(mat, tam, 0))
            return 1;
        else
            return 0;
    else
        return 0;
}

/* Chequea si los elementos de una matriz en SU DP son todos iguales. */

int sonTodosIgualesDP(int mat[][COL], int tam, int num)
{
    int i;

    for (i = 0; i < tam; i++)
        if (mat[i][i] != num)
            return 0; //En caso de que hallemos un elemento que no sea igual a num, retornamos 0
    return 1;
}

/* Chequea si los elementos de una matriz SIN SU DP son todos iguales. */

int sonTodosIgualesSinDP(int mat[][COL], int tam, int num)
{
    int i, j;
    //Chequeamos que todos los elementos que no pertenezcan a DP sean 0
    for (i = 0; i < tam/2; i++)
        for (j = 0; j < tam; j++)
            if (i != j && (mat[i][j] != num || mat[j][i] != num))
                return 0;

    return 1;
}

void trasponerRespDP(int mat[][COL], int tam)
{
    int i, j, aux;

    //Desde 0 hasta tam/2+1
    for (i = 0; i < tam/2+1; i++)
    {
        //Empezando desde i, hasta tam
        for (j = i; j < tam; j++)
        {
            //Obviamos la diagonal principal
            if (i != j)
            {
                aux = mat[i][j];
                mat[i][j] = mat[j][i];
                mat[j][i] = aux;
                //printf(" pos i: %d, pos j: %d; ",mat[i][j], mat[j][i]);
            }
        }
    }
    printf("\nMostrando matriz traspuesta: ");
    mostrarMatriz(mat, tam, tam);
}

void trasponerRespDS(int mat[][COL], int tam)
{
    int i, j, aux;

    //Desde 0 hasta tam/2+1
    for (i = 0; i < tam/2+1; i++)
    {
        //Empezando desde i, hasta tam
        for (j = 0; j < tam - i; j++)
        {
            aux = mat[i][j];
            mat[i][j] = mat[tam-(j+1)][tam-(i+1)];
            mat[tam-(j+1)][tam-(i+1)] = aux;
        }
    }
    printf("\nMostrando matriz traspuesta respecto a DS: ");
    mostrarMatriz(mat, tam, tam);
}

void trasponerHorizontal(int mat[][COL], int tam)
{
    int i, j, aux, cantPos;

    cantPos = tam-1; //Necesitamos operar con las posiciones, no con el tamaño real

    for (i = 0; i < tam/2; i++)
        for (j = 0; j < tam; j++)
        {
            aux = mat[i][j];
            mat[i][j]= mat[cantPos-i][j];
            mat[cantPos-i][j] = aux;
        }

    printf("\nMostrando matriz traspuesta respecto eje horizontal: ");
    mostrarMatriz(mat, tam, tam);
}

void trasponerVertical(int mat[][COL], int tam)
{
    int i, j, aux, cantPos = tam-1; //Necesitamos operar con las posiciones, no con el tamaño real

    for (i = 0; i < tam; i++)
        for (j = 0; j < tam/2; j++)
        {
            aux = mat[i][j];
            mat[i][j] = mat[i][cantPos-j];
            mat[i][cantPos-j] = aux;
        }

    printf("\nMostrando matriz traspuesta respecto eje horizontal: ");
    mostrarMatriz(mat, tam, tam);
}

void trasponerCentro(int mat[][COL], int tam)
{
    int i, j, aux, cantPos = tam-1;

    for (i = 0; i < tam/2; i++)
        for (j = 0; j < tam; j++)
        {
            if (j < tam/2)
            {
                aux = mat[i][j];
                mat[i][j] = mat[cantPos-j][cantPos-i];
                mat[cantPos-j][cantPos-i] = aux;
            }
            else
            {
                aux = mat[i][j];
                mat[i][j] = mat[cantPos-i][cantPos-j];
                mat[cantPos-i][cantPos-j] = aux;
            }
        }
    printf("\nMostrando matriz traspuesta respecto al centro: ");
    mostrarMatriz(mat, tam, tam);
}

void mostrarVecinos(int mat[][COL], int filas, int columnas, int posX, int posY, int inc)
{
    //Usamos logica de usuario, la posicion que nos dan es una mas que la posicion empezando desde 0
    posX--;
    posY--;
    int endX = posX, endY = posY, i, j;

    if (posX-1 >= 0)
        posX--;
    if (posY-1 >= 0)
        posY--;
    if (posX+1 < filas)
        endX = posX+1;
    if (posY+1 < columnas)
        endY = posY+1;

    for (i = posX; i <= endX; i++)
        for (j = posY; j <= endY; j++)
            if (!inc)
                printf(" %d", mat[i][j]);
            else if (i+j != posX+posY)
                printf(" %d", mat[i][j]);
}

void maxMatVertSupIzq(int mat[][COL], int filas, int columnas, int posX, int posY)
{
    int i, j, fin;

    filas--;
    columnas--;
    posX--;
    posY--;

    if (filas-posX <= columnas-posY)
        fin = filas-posX;
    else
        fin = columnas-posY;

    for (i = 0; i <= fin; i++)
        for (j = 0; j <= fin; j++)
            printf("%d ", mat[posX+i][posY+j]);
}

void maxMatVertInfIzq(int mat[][COL], int filas, int columnas, int posX, int posY)
{
    int i, j, fin, endY;

    filas--;
    columnas--;
    posX--;
    posY--;

    if (posX <= columnas-posY)
        fin = posX;
    else
        fin = columnas-posX;

    for (i = 0; i <= fin; i++)
        for (j = 0; j <= fin; j++)
            printf("%d ", mat[posX-i][posY+j]);
}

void maxMatVertInfDer(int mat[][COL], int posX, int posY)
{
    int i, j, fin;

    posX--;
    posY--;

    //a cuanto estoy del 0 desde posx? y desde posy? la cantidad de movimientos esta restringida por el mas chico de los dos

    if (posX >= posY)
        fin = posY;
    else
        fin = posX;

    for (i = 0; i <= fin; i++)
        for (j = 0; j <= fin; j++)
            printf("%d ", mat[posX-i][posY-j]);
}

void maxMatVertSupDer(int mat[][COL], int filas, int columnas, int posX, int posY)
{
    int i, j, fin;

    posX--;
    posY--;
    filas--;
    columnas--;

    if (filas-posX <= posX)
        fin = filas-posX;
    else
        fin = posY;

    for (i = 0; i <= fin; i++)
        for (j = 0; j <= fin; j++)
            printf("%d ", mat[posX+i][posY-j]);
}


void maxMatCuad(int mat[][COL], int filas, int columnas, int posX, int posY)
{
    //Hay que chequear el cuadrante en el que nos encontramos, y en base a eso, llamar a la funcion correspondiente
    //Cuarto cuadrante
    if (posX > filas/2 && posY > columnas/2)
        maxMatVertInfDer(mat, posX, posY);
    else if (posX > filas/2 && posY <= columnas/2) //Tercer cuadrante
        maxMatVertInfIzq(mat, filas, columnas, posX, posY);
    else if (posX <= filas/2 && posY > columnas/2)
        maxMatVertSupDer(mat, filas, columnas, posX, posY); //Segundo cuadrante
    else
        maxMatVertSupIzq(mat, filas, columnas, posX, posY);
}
