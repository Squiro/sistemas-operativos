#include "funciones.h"

int main()
{
    printf("Resultado mi_tolower de %c: %c\n", 'A', mi_tolower('A'));
    printf("Resultado mi_toupper de %c: %c\n", 'b', mi_toupper('b'));
    printf("Resultado mi_toupper de %c: %c\n", 'ñ', mi_tolower('ñ'));
    printf("Resultado mi_isalnum de %c: %c\n", 'a', mi_isalnum('a'));
    printf("Resultado mi_isalpha de %c: %c\n", 'a', mi_isalpha('a'));
    printf("Resultado mi_isascii de %c: %c\n", 'é', mi_isaccii('é'));
    printf("Resultado mi_isctrl de %c: %c\n", 2, mi_isctrl(2));
    printf("Resultado mi_isdigit de %c: %c\n", '1', mi_isdigit('1'));
    printf("Resultado mi_isgraph de %c: %c\n", ' ', mi_isgraph(' '));
    printf("Resultado mi_isprint de %c: %c\n", 'A', mi_isprint('A'));
    printf("Resultado mi_ispunct de %c: %c\n", '?', mi_ispunct('?'));
    printf("Resultado mi_isspace de %c: %c\n", 12, mi_isspace(12));
    printf("Resultado mi_islower de %c: %c\n",'b', mi_islower('b'));
    printf("Resultado mi_isupper de %c: %c\n",'A', mi_isupper('A'));
    printf("Resultado mi_isxdigit de %c: %c\n",'J', mi_isxdigit('J'));
    printf("Resultado mi_toascii de %c: %c\n", 'ñ', mi_toascii('ñ'));
    return 0;
}
