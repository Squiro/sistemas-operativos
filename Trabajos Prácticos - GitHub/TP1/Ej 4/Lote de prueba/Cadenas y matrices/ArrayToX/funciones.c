#include "funciones.h"

double mi_atof(const char *numPtr)
{
    double num = 0;
    int posDec = 1;
    int sgn = 1;

    if (*numPtr == '-')
    {
        sgn = -1;
        numPtr++;
    }

    while (*numPtr && *numPtr != '.')
    {
        num = num * 10 + (*numPtr - '0');
        numPtr++;
    }

    numPtr++;

    while(*numPtr)
    {
        num = num * 10. + (*numPtr - '0');
        numPtr++;
        posDec *= 10;
    }

    return num/(posDec) *sgn;
}

int mi_atoi(const char *numPtr)
{
    double num = 0;
    int sgn = 1;

    if (*numPtr == '-')
    {
        sgn = -1;
        numPtr++;
    }

    while (*numPtr)
    {
        num = num * 10 + (*numPtr - '0');
        numPtr++;
    }

    return num*sgn;
}

char *mi_itoa(int num, char * str, int base)
{
    char *pEsc = str;
    int resto;
    int signo = 0;

    if (num < 0 && base == 10)
        signo = 1;

    //Como estamos trabajando con enteros, va a llegar un punto en el que la división de num/base va a arrojar 0
    while (num != 0)
    {
        resto = num % base;
        //Si el resto da como resultado algo mayor a 9, significa que estamos laburando en hexa (u otra base) y necesitamos usar la parte de las letras de ASCII
        *pEsc = (resto > 9) ? resto-10 + 'a' : resto + '0';
        num = num/base;
        *pEsc++;
    }

    if (signo)
        *(++pEsc) = '-';

    *pEsc = '\0';
    invertirCadena(str);
    return str;
}

char * invertirCadena(char *cadena)
{
    char *pIni = cadena;
    char aux;

    while (*cadena)
        cadena++;

    cadena--;

    while (cadena-pIni >= 1)
    {
        aux = *pIni;
        *pIni = *cadena;
        *cadena = aux;
        cadena--;
        pIni++;
    }

    return cadena;
}
