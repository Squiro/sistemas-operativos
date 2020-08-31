#include <string.h>
#include <stdio.h>
#include <stdlib.h>

unsigned int mi_strlen(const char *cadena);
char *mi_strcpy(char *cadena1, const char *cadena2);
char *mi_strncpy(char *cadena1, const char *cadena2, unsigned int limite);
int mi_strcmp(const char *cadena1, const char *cadena2);
int mi_strncmp(const char *cadena1, const char *cadena2, unsigned int limite);
char *mi_strcat(char *cadena1, const char *cadena2);
char *mi_strncat(char *cadena1, const char *cadena2, unsigned int limite);
char *mi_strchr(char *cadena, int caracter);
char *mi_strrchr(char *cadena, int caracter);
char *mi_strstr(const char *cadena1, const char *cadena2);
