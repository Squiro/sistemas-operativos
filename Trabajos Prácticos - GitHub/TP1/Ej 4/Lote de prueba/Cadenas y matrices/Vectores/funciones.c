//Comprueba si un elemento (numero) está presente en un array de enteros
//Recibe el numero, el puntero del array, y la cantidad de elementos del mismo
//TRUE = 1 | FALSE = 0
int is_inArray(int elemento, int* pvec, int cantElem)
{
    int i;

    for (i = 0; i < cantElem; i++)
    {
        if (*pvec == elemento)
            return 1;
        pvec++;
    }

    return 0;
}

//Imprime por pantalla el array mostrando posiciones "al usuario" (o sea, empezando desde 1)
void showArrayWithPos(int vec[], int size)
{
    int i;

    printf("ELEMENTOS: \t |");
    for (i = 0; i < size; i++)
        printf(" %d | ", *vec++);
    printf("\nPOSICIONES: \t |");
    for (i = 0; i < size; i++)
        printf(" %d | ", i+1);
}

//Imprime por pantalla el array mostrando mostrando la posiciones reales
void showArrayWithTruePos(int vec[], int size)
{
    int i;

    printf("ELEMENTOS: \t |");
    for (i = 0; i < size; i++)
        printf(" %d | ", *vec++);
    printf("\nPOSICIONES: \t |");
    for (i = 0; i < size; i++)
        printf(" %d | ", i);
}

//Parametros:
//pos = una posicion del vector
//elemento = elemento/num a insertar
//vector = al puntero de la primera posicion

void insertarElemento(int pos, int elemento, int* pvec, int cantElem)
{
	int i;
	int* pFin;

	pFin = pvec+(pos-1);

	pvec += cantElem-1; //Le sumamos al puntero la cantElem para apuntar a la ult posicion ocupada

	while (pvec > pFin)
    {
		*pvec = *(pvec-1);
        pvec--;
    }

	/*for (i = cantElem; i > pos; i--)
	{
		*pvec = *(pvec-1);
        pvec--;
	}*/

	*pvec = elemento; //Le asignamos a la pos indicada por el usuario, el elem indicado

	//return cantElem < TAM ? cantElem++ : cantElem;

	/* Forma menos optima
	int aux;
	aux = *(pvec); //el auxiliar es el elemento ORIGINAL que estaba en esa posicion

    for (i = pos; i < TAM; i++)
	{
		*(pvec+i) = elemento; //Guardamos el elemento DADO en la posicion dada
		elemento=aux; //SOBREESCRIBIMOS el elemento DADO por el auxiliar, para poder guardarlo en la prox iteracion
		aux = *(pvec+i+1); //Ahora el nuevo auxiliar va a ser el elemento presente en la posicion contigua
	}*/
}

void insertarElementoAscendente(int elemento, int* pvec, int cantElem)
{
    //Si el elemento está en el array, no hacemos nada
    if (is_inArray(elemento, pvec, cantElem))
        return;

    pvec += cantElem-1;

    while (*pvec > elemento && *(pvec-1) > elemento)
	{
		*pvec = *(pvec-1);
        pvec--;
	}

	*pvec = elemento;
}

//Elimina un elemento en una posicion y mueve los demas elementos
void eliminarElementoEnPos(int pos, int* pvec, int cantElem)
{
    int* pFin = pvec+cantElem-1;
    pvec += pos-1;

    while (pvec < pFin)
    {
        *pvec = *(pvec+1);
        pvec++;
    }

    *pvec = 0;
}

//Elimina todas las apariciones de un elemento
void deleteOnce(int elemento, int* pvec, int cantElem)
{
    //Si no está en el array, no hacemos nada
    if (!is_inArray(elemento, pvec, cantElem))
        return;

    int* pFin = pvec+cantElem-1;
    int removed = 0;

    while (pvec < pFin)
    {
        if (*(pvec+1) != elemento || removed == 1)
        {
            *pvec = *(pvec+1);
            removed = 1;
        }
        pvec++;
    }

    *pvec = 0;
}

void deleteAll(int elemento, int* pvec, int cantElem)
{
    //Si no está en el array, no hacemos nada
    if (!is_inArray(elemento, pvec, cantElem))
        return;

    int* pFin = pvec+cantElem;
    //puntero lectura, puntero escritura
    int* pLec = pvec, *pEsc = pvec;

    while (pLec < pFin)
    {
        if (*pLec == elemento)
            pLec++;

        *pEsc = *pLec;
        pEsc++;
        pLec++;
    }

    //Seteamos en 0 la basura
    while (pEsc < pFin)
    {
        *pEsc = 0;
        pEsc++;
    }
}

int esPalindromo(char cadena[], int size, int cantPos)
{
    //int i = 0, j = size-cantPos; //Esto es a lo que se refiere el comentario de la linea 13
    char *i = cadena, *j = cadena+(size-cantPos); //Punteros al vector

    //Recorremos la cadena desde 0 con i, hacia la derecha, y desde size-cantPos con j, hacia la izquierda

    while (i < (cadena+size) && j >= cadena)
    {
        printf("%c -> %c \n", *i, *j);
        if (*i != *j)
            return 0;
        i++;
        j--;
    }

    /*while (i < size && j >= 0)
    {
        printf("%c -> %c \n", cadena[i], cadena[j]);
        if (cadena[i] != cadena[j])
            return 0;
        i++;
        j--;
    }*/

    return 1;
}

//Retorna la cantidad de espacios removidos
int removerEspacios(char* source, char* dest)
{
    int i = 0, j = 0, contador = 0;

    while (*source != '\0') //Mientras no lleguemos al null terminator...
    {
        if (*source != ' ') //Si es diferente de un espacio en blanco... copiamos el contenido en el otro char
        {
            *dest = *source;
            dest++; //Incrementamos el pointer de dest para que el prox char se guarde en la siguiente posicion
        }
        else //Si no es diferente, no lo copiamos, y aumentamos el contador de espacios
            contador++;
        source++; //Incrementamos el pointer de source para ir avanzando por el string
    }
    *(dest) = '\0'; //Al ultimo espacio de dest le ponemos el null terminator para terminar la cadena cuando es necesario
    return contador;
}

