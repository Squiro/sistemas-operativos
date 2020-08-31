#ifndef FUNCIONES_H_
#define FUNCIONES_H_

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

double mi_atof(const char *numPtr);

int mi_atoi(const char *numPtr);

char * mi_itoa(int num, char * str, int base);

char * invertirCadena(char *cadena);

#endif // FUNCIONES_H_
