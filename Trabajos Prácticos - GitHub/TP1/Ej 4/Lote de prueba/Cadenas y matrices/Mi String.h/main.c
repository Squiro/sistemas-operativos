#include "funciones.h"

int main()
{
    char cadena[] = "asdf"; //No constante
    //char *cadena = "HOLA"; //Constante
    char cadena2[5] = "Hols"; //No constante
    char cadena3[5] = "Hols"; //No constante
    char cadena4[] = "Comparame. :)";
    char cadena5[] = "Strcateame :)";

    printf("STRLEN POSTA: %d\n", strlen(cadena));
    printf("MI_STRLEN (NO POSTA): %d\n\n", mi_strlen(cadena));

    printf("PRE STRCPY: %s | SIZE: %d\n", cadena2, sizeof(cadena2));
    strcpy(cadena2, "Me llamo carlos.");
    printf("POST STRCPY: %s | SIZE: %d\n\n", cadena2, sizeof(cadena2));

    printf("PRE MI_STRCPY: %s | SIZE: %d\n", cadena3, sizeof(cadena3));
    //mi_strcpy(cadena3, "Me llamo carlos.");
    printf("POST MI_STRCPY: %s | SIZE: %d\n\n", mi_strcpy(cadena3, "Me llamo carlos."), sizeof(cadena3));


    printf("PRE MI_STRnCPY: %s | SIZE: %d\n", cadena3, sizeof(cadena3));
    mi_strncpy(cadena3, "Me llamo carlos.", 5);
    printf("POST MI_STRnCPY: %s | SIZE: %d\n\n", cadena3, sizeof(cadena3));

    printf("STRCMP: %s | %s | RETURNS: %d\n", cadena4, cadena3, strcmp(cadena4, cadena3));
    printf("MI_STRCMP: %s | %s | RETURNS: %d\n\n", cadena4, cadena3, mi_strcmp(cadena4, cadena3));

    printf("STRnCMP: %s | %s | RETURNS: %d\n", cadena4, cadena3, strncmp(cadena4, cadena3, 5));
    printf("MI_STRnCMP: %s | %s | RETURNS: %d\n\n", cadena4, cadena3, mi_strncmp(cadena4, cadena3, 5));

    printf("PRE STRCAT: %s | %s |\n", cadena4, "ni idea");
    strcat(cadena4, "ni idea");
    printf("POST STRCAT: %s | %s |\n\n", cadena4, "ni idea");

    printf("PRE MI_STRCAT: %s | %s |\n", cadena5, "ni idea");
    mi_strcat(cadena5, "ni idea");
    printf("POST MI_STRCAT: %s | %s |\n\n", cadena5, "ni idea");

    printf("PRE MI_STRnCAT: %s | %s |\n", cadena5, "ni idea");
    mi_strncat(cadena5, "OKAY", 2);
    printf("POST MI_STRnCAT: %s | %s |\n\n", cadena5, "ni idea");

    printf("STRCHR: %s | %c | RETURNS: %s\n", cadena5, 'c', strchr(cadena5, 'c'));
    printf("MI_STRCHR: %s | %c | RETURNS: %s\n\n", cadena5, 'c', mi_strchr(cadena5, 'c'));

    printf("STRRCHR: %s | %c | RETURNS: %s\n", cadena5, 'q', strrchr(cadena5, 'q'));
    printf("MI_STRCHR: %s | %c | RETURNS: %s\n\n", cadena5, 'q', mi_strrchr(cadena5, 'q'));

    printf("STRSTR: %s | %s | RETURNS: %s\n", cadena5, "trc", strstr(cadena5, "trc"));
    printf("MI_STRSTR: %s | %s | RETURNS: %s\n\n", cadena5, "trc", mi_strstr(cadena5, "trc"));

    return 0;
}
