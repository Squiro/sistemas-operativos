#include "funciones.h"

int mi_toupper(int ch)
{
    if (ch < 97 || ch > 122)
        return ch;
    else
        return ch-32;
}

int mi_tolower(int ch)
{
    if (ch < 65 || ch > 90)
        return ch;
    else
        return ch+32;
}

int mi_isalnum(int c)
{
    if ((c > 47 && c < 58) || (c > 64 && c < 91) || (c > 96 && c < 123))
        return c;
    else
        return 0;
}

int mi_isalpha(int c)
{

    if ((c > 64 && c < 91) || (c > 96 && c < 123)) //(((c) | 32) - 'a' + 0U <= 'z' - 'a' + 0U)
        return c;
    else
        return 0;
}

int mi_isaccii(int c)
{
    if (c >= 0 && c <= 127)
        return c;
    else
        return NULL;
}

int mi_isctrl(int c)
{
    if (c >= 0 && (c < 32 || c == 127))
        return c;
    else
        return NULL;
}

int mi_isdigit(int c)
{
    //+ 0U nos asegura que la operacion de un resultado unsigned
    if (c - '0' +0U <= 9)
        return c;
    else
        return NULL;
}

int mi_isgraph(int c)
{
    if (c >= 0 && c <= 127 && c != 32)
        return c;
    else
        return NULL;
}

int mi_islower(int c)
{
    if (c > 96 && c < 127)
        return c;
    else
        return NULL;
}

int mi_isprint(int c)
{
    if (c >= 0 && c <= 127)
        return c;
    else
        return NULL;
}

int mi_ispunct(int c)
{
    if ((c >= 33 && c <= 47) || (c >= 58 && c <= 64) || (c >= 91 && c <= 96) || (c >= 123 && c <= 126))
        return c;
    else
        return NULL;
}

int mi_isspace(int c)
{
    if ((c >= 9 && c <= 14) || c == 32)
        return c;
    else
        return NULL;
}

int mi_isupper(int c)
{
    if (c > 64 && c < 91)
        return c;
    else
        return NULL;
}

int mi_isxdigit(int c)
{
    if ((c >= 30 && c <= 57) || (c >= 65 && c <= 70) || (c >= 97 && c <= 102))
        return c;
    else
        return NULL;
}

int mi_toascii(int c)
{
   return c & 127;

}
