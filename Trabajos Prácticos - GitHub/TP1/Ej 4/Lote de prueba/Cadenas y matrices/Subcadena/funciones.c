#include "funciones.h"

char * reemplazar(char * str, char *sub_str, char * new_str)
{
    char *pos = mi_strstr(str, sub_str);
    int len = mi_strlen(new_str), acum = 0;
    //Si el substring no esta dentro del string que me mandan, devuelvo el string original
    if (!pos)
        return str;

    while(*pos && acum <= len)
    {
        *pos = *new_str;
        new_str++;
        pos++;
        acum++;
    }

    while(*pos)
        pos++;

    *pos = '\0';

    return str;
}

char * mi_strncpy(char * str1, const char * str2, int limite)
{
    char *pc = str1;
    int acum = 0;

    while (*str2 && acum < limite)
    {
        *str1 = *str2;
        str1++;
        str2++;
        acum++;
    }
    *str1 = '\0';
    return pc;
}

char * mi_strstr(char *str1, char *str2)
{
    int lenStr2 = mi_strlen(str2);
    if (mi_strlen(str1) < lenStr2)
        return NULL;

    char *pStr1, *pStr2;
    int acum = 0;

    while (*str1)
    {
        pStr1 = str1;
        pStr2 = str2;

        while (*pStr2 && *pStr1 == *pStr2)
        {
            pStr1++;
            pStr2++;
            acum++;
        }

        if (acum == lenStr2)
            return str1;
        str1++;
    }

    return NULL;
}


int mi_strlen(const char *str)
{
    unsigned int count = 0;

    while (*str)
    {
        str++;
        count++;
    }

    return count;
}
