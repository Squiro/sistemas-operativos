#ifndef FECHAS_H_
#define FECHAS_H_

typedef struct
{
    int dia;
    int mes;
    int anio;
} t_fecha;

int comprobarFecha(t_fecha fecha);
int esBisiesto(t_fecha fecha);

#endif // FECHAS_H_

