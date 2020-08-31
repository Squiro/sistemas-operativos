#include "funciones.h"

unsigned int mi_strlen(const char *cadena) //Recibimos siempre la direccion a la primera posicion del array
{
    unsigned int i = 0;
    //char *pc = cadena; //El contenido del puntero es constante, pero NO el puntero que recibimos

    while (*cadena) // No hace falta poner != '\0', ya que *pc va a ser valido mientras que no sea el fin de linea
    {           // \0 es FALSO
        cadena++;
        i++;
    }
    return i;
}

char *mi_strcpy(char *cadena1, const char *cadena2)
{
    char *pc = cadena1; //Puntero que indica el comienzo de cadena1

    while (*cadena2 != '\0')
    {
        *cadena1 = *cadena2;
        cadena1++;
        cadena2++;
    }
    *cadena1 = '\0';

    return pc; //Devolvemos la primera pos de cadena 1
}

char *mi_strncpy(char *cadena1, const char *cadena2, unsigned int limite)
{
    char *pc = cadena1; //Puntero que indica el comienzo de cadena1
    int index = 0;

    while (*cadena2 != '\0' && index < limite)
    {
        *cadena1 = *cadena2;
        cadena1++;
        cadena2++;
        index++;
    }
    *cadena1 = '\0';

    return pc; //Devolvemos la primera pos de cadena 1
}

//In C, the functions strcmp and memcmp perform a three-way comparison between strings and memory buffers, respectively.
//They return a negative number when the first argument is lexicographically smaller than the second, zero when the arguments are equal, and a positive number otherwise.
int mi_strcmp(const char *cadena1, const char *cadena2)
{
    do
    {
        if (*cadena1 != *cadena2)
            return *cadena1>*cadena2?1:-1;
        cadena1++;
        cadena2++;
    } while (*cadena1 && *cadena2);

    return 0;
}

int mi_strncmp(const char *cadena1, const char *cadena2, unsigned int limite)
{
    int index = 0;
    do
    {
        if (*cadena1 != *cadena2)
            return *cadena1>*cadena2?*cadena2-*cadena1:*cadena1-*cadena2;
        cadena1++;
        cadena2++;
        index++;
    } while (*cadena1 && *cadena2 && index < limite);

    return 0;
}

char *mi_strcat(char *cadena1, const char *cadena2)
{
    char* pc = cadena1;
    cadena1 += mi_strlen(cadena1); //Al sumarle la cantidad de caracteres de cadena1, directamente nos posicionamos por sobre el caracter nulo

    while (*cadena2)
    {
        *cadena1 = *cadena2;
        cadena1++;
        cadena2++;
    }

    *cadena1 = '\0';

    return pc;
}

char *mi_strncat(char *cadena1, const char *cadena2, unsigned int limite)
{
    char* pc = cadena1;
    int index = 0;

    cadena1 += mi_strlen(cadena1); //Al sumarle la cantidad de caracteres de cadena1, directamente nos posicionamos por sobre el caracter nulo

    while (*cadena2 && index < limite)
    {
        *cadena1 = *cadena2;
        cadena1++;
        cadena2++;
        index++;
    }

    *cadena1 = '\0';

    return pc;
}

char *mi_strchr(char *cadena, int caracter)
{
    char *nulo = NULL;
    while (*cadena)
    {
        if (*cadena == (char)caracter)
            return cadena;

        cadena++;
    }

    return nulo; //Devolvemos un puntero "nulo" si no se encuentra nada
}


char *mi_strrchr(char *cadena, int caracter)
{
    char *found=NULL;

    while (*cadena)
    {
        if (*cadena == (char)caracter)
            found = cadena;

        cadena++;
    }

    return found; //Devolvemos un puntero "nulo" si no se encuentra nada
}

char *mi_strstr(const char *cadena1, const char *cadena2)
{
    int len = mi_strlen(cadena2);
    //Si la cadena1 es menor que la cadena2, devolvemos null. Es imposible que una esté en la otra
    if (mi_strlen(cadena1) < len)
        return NULL;

    int acum = 0;
    char *pCad1, *pCad2;

    while (*cadena1)
    {
        pCad1 = cadena1;
        pCad2 = cadena2;
        while (*pCad2 && *pCad1 == *pCad2)
        {
            pCad1++;
            pCad2++;
            acum++;
        }

        if (acum == len)
            return cadena1;

        cadena1++;
    }

}



