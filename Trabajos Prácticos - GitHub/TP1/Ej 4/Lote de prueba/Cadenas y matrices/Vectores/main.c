#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include "funciones.h"

#define ENTER_KEY 13
#define TAM 6

//Este proyecto contiene todos los ejercicios de vectores del TP1
//Incluye un menú para seleccionar el ejercicio
//Además los ejercicios están adaptados para el "usuario" (tomando los arrays y sus posiciones empezando desde 1)

void menu();
void imprimirOpciones(int, char*[], int);
void ejecutarEjercicio(int);


int main()
{
    menu();
    return 0;
}

void menu()
{
    char* ejercicios[] = { "EJ. 22: Insercion en pos. dada", "EJ. 23: Insercion ascendente", "EJ. 24: Eliminar en pos. dada",
    "EJ. 25: Eliminar primera aparicion", "EJ. 26: Eliminar todas las apariciones", "EJ. 27: Determinar palindromo" };
    char keypress;
    int index = 0, size = 6;



    do
    {
        imprimirOpciones(index, ejercicios, size);
        keypress = getch();

        switch(keypress)
        {
            case 'w':
            case 'W':
                index--;
                if (index < 0)
                    index = 0;
                imprimirOpciones(index, ejercicios, size);
                break;
            case 's' :
            case 'S':
                index++;
                if (index > size-1)
                    index = size-1;
                imprimirOpciones(index, ejercicios, size);
                break;
            case ENTER_KEY:
                ejecutarEjercicio(index);
                getch();
                break;
        }

    } while(keypress != 0);

}

void ejecutarEjercicio(int index)
{
    system("CLS");
    switch(index)
    {
        case 0: ejercicio22();
            break;
        case 1: ejercicio23();
            break;
        case 2: ejercicio24();
            break;
        case 3: ejercicio25();
            break;
        case 4: ejercicio26();
            break;
        case 5: ejercicio27();
            break;
    }
}

void imprimirOpciones(int index, char *ejercicios[], int size)
{
    char flecha[] = "<----";

    int i;

    system("CLS");
    printf("\t\t\t\t Mueva la flecha con las teclas W y S. Aprete ENTER para elegir.\n\n\n");

    for (i = 0; i < size; i++)
    {
        if (i == index)
            printf("\t\t\t\t %s %s\n\n", ejercicios[i], flecha);
        else
            printf("\t\t\t\t %s \n\n", ejercicios[i]);
    }
}

int ejercicio22()
{
    int vec[TAM] = {2, 3, 7, 9};
    int elemento, posicion, cantElem; //size
    cantElem = 6; //Apunta a la siguiente posicion libre, o sea, cantElem - 1 es la verdadera cant
    int size = sizeof(vec)/sizeof(int);

    showArrayWithPos(vec, size);

    printf("\n\nIngrese un elemento para añadir al vector: ");
    scanf("%d", &elemento);
    printf("\nIngrese la posicion en la que desea añadirlo: ");
    scanf("%d", &posicion);
    posicion = abs(posicion);

    while (posicion>TAM-1 || posicion > cantElem)
    {
        printf("\nLa posicion ingresada es mas grande que la cantidad de posiciones del vector.");
        printf("\nIntente de nuevo.\n\n");
        printf("\nIngrese la posicion: ");
        scanf("%d", &posicion);
        posicion = abs(posicion);
    }

	insertarElemento(posicion, elemento, vec, cantElem);
	printf("\nAsi quedo el vector: \n");
	showArrayWithPos(vec, size);
	printf("Cant elem: %d", cantElem);

    return 0;
}

int ejercicio23()
{
    int vec[TAM] = {2, 10, 20, 30, 40, 50};
    int elemento, cantElem = 6; //Apunta a la siguiente posicion libre, o sea, cantElem - 1 es la verdadera cant;
    int size = sizeof(vec)/sizeof(int);

    showArrayWithPos(vec, size);

    printf("\n\nIngrese un elemento para añadir al vector: ");
    scanf("%d", &elemento);
    insertarElementoAscendente(elemento, vec, cantElem);
    printf("\nAsi quedo el vector: \n");
    showArrayWithPos(vec, size);
    return 0;
}

int ejercicio24()
{
    int vec[TAM] = {2, 10, 20, 30, 40, 50};
    int posicion, cantElem = 6;
    int size = sizeof(vec)/sizeof(int);

    showArrayWithPos(vec, size);

    printf("\nIngrese la posicion del elemento que desea eliminar: ");
    scanf("%d", &posicion);
    posicion = abs(posicion);
    while (posicion>TAM-1)
    {
        printf("\nLa posicion ingresada es mas grande que la cantidad de posiciones del vector.");
        printf("\nIntente de nuevo.\n\n");
        printf("\nIngrese la posicion del elemento que desea eliminar: ");
        scanf("%d", &posicion);
        posicion = abs(posicion);
    }
    eliminarElementoEnPos(posicion, vec, cantElem);
    printf("\nAsi quedo el vector: \n");
    showArrayWithPos(vec, size);
    return 0;
}

int ejercicio25()
{
    int vec[TAM] = {10, 2, 20, 10, 40, 10};
    int elemento, cantElem = 6;
    int size = sizeof(vec)/sizeof(int);

    showArrayWithPos(vec, size);

    printf("\n\nIngrese un elemento para eliminar del vector: ");
    scanf("%d", &elemento);
    deleteOnce(elemento, vec, cantElem);
    printf("\nAsi quedo el vector: \n");
    showArrayWithPos(vec, size);
    return 0;
}

int ejercicio26()
{
    int vec[TAM] = {2, 10, 20, 10, 40, 11};
    int elemento, cantElem = 6;
    int size = sizeof(vec)/sizeof(int);
    showArrayWithPos(vec, size);

    printf("\n\nIngrese un elemento para eliminar del vector: ");
    scanf("%d", &elemento);
    deleteAll(elemento, vec, cantElem);
    printf("\nAsi quedo el vector: \n");
    showArrayWithPos(vec, size);
    return 0;
}

int ejercicio27()
{
    char cadena[] = "anita lava la tina";
    int size = 0, cantPosiciones;
    char cadenaLimpia[sizeof(cadena)];

    //cantPosiciones guarda la cantidad de posiciones de diferencia que hay entre la cadena original
    //y la cadena sin espacios. A este numero le sumamos 2, ya que es la cantidad de caracteres del null terminator en C ('\0')
    cantPosiciones = removerEspacios(cadena, cadenaLimpia) + 2;
    size = sizeof(cadenaLimpia)/sizeof(char);
    printf("%s \n", cadenaLimpia);
    //printf("%d \n", cantPosiciones);

    if (esPalindromo(cadenaLimpia, size, cantPosiciones))
        printf("\nEs palindromo.");
    else
        printf("\nNo es palindromo.");
    return 0;
}
