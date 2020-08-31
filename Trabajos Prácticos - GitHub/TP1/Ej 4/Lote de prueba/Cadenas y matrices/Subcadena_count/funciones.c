#include "funciones.h"

int substr_count(char *str, char *sub_str)
{
    int acum = 0, count = 0, len = mi_strlen(sub_str);
    char *pStr, *pSub;

    while (*str)
    {
        pStr = str;
        pSub = sub_str;

        while (*pSub && *pStr == *pSub)
        {
            pSub++;
            pStr++;
            acum++;
        }

        if (acum == len)
        {
            count++;
            str+= len-1;
        }
        else
            str++;
        acum = 0;
    }
    return count;
}


int mi_strlen(const char *str)
{
    int count = 0;
    while (*str)
    {
        str++;
        count++;
    }

    return count;
}
