#include "fecha.h"
#include <stdexcept>
/*
    Reminder: la estructura es
    tipo de retorno; nombre de clase; op de ambito; metodo
*/

/** CONSTRUCTORES */

//Constructor parametrizado por defecto
Fecha :: Fecha(const int dia, const int mes, const int anio)
{
    if (!validarFecha(dia, mes, anio))
        throw std::logic_error("La fecha ingresada no paso la verificacion.");

    this->dia = dia;
    this->mes = mes;
    this->anio = anio;
}

Fecha :: Fecha(const Fecha &obj)
{
    this->dia = obj.dia;
    this->mes = obj.mes;
    this->anio = obj.anio;
}

/** PROPIEDADES (GET Y SET) */

int Fecha :: getDia()
{
    return this->dia;
}

int Fecha :: getMes()
{
    return this->mes;
}

int Fecha :: getAnio()
{
    return this->anio;
}

void Fecha :: setDia(const int dia)
{
    this->dia = dia;
}

void Fecha :: setMes(const int mes)
{
    this->mes = mes;
}

void Fecha :: setAnio(const int anio)
{
    this->anio = anio;
}

/** METODOS */

bool Fecha :: validarFecha(const int dia, const int mes, const int anio)
{
    int cantDiasMes[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if (dia <= 0 || mes <= 0 || anio <= 0 || dia >= 31 || mes >= 12)
        return false;

    //¿La fecha es mayor a la cantidad de dias que tiene el mes?
    if (cantDiasMes[mes] < dia)
    {
        //¿Es febrero?
        if (mes == 2 && dia == 29)
            //¿Es el año bisiesto?
            if (es_bisiesto(anio))
                return true;


        return false;
    }

    //Si pasó todas las validaciones, returnamos true
    return true;
}

bool Fecha :: es_bisiesto(const int anio)
{
    if ((anio % 4 == 0 && anio % 100 != 0) || anio % 400 == 0)
        return true;

    return false;
}

void Fecha :: mostrar()
{
    cout << "Fecha: " << this->dia << "/" << this->mes << "/" << this->anio << endl;
}

/** OPERADORES */

Fecha & Fecha :: operator = (const Fecha &obj)
{
    this->dia = obj.dia;
    this->mes = obj.mes;
    this->anio = obj.anio;

    return *this;
}

Fecha & Fecha :: operator += (const Fecha &obj)
{

    return *this;
}

Fecha & Fecha :: operator -= (const Fecha &obj)
{

    return *this;
}

Fecha & Fecha :: operator + (const Fecha &obj)
{

    //return *this;
}

Fecha & Fecha :: operator - (const Fecha &obj)
{

    //return *this;
}

bool Fecha :: operator == (const Fecha &obj)const
{
    if (this->dia == obj.dia && this->mes == obj.mes && this->anio == obj.anio)
        return true;

    return false;
}

bool Fecha :: operator < (const Fecha &obj)const
{
    if (this->anio < obj.anio)
        return true;
    else if (this->anio > obj.anio)
        return false;

    if (this->mes < obj.mes)
        return true;
    else if (this->mes > obj.mes)
        return false;

    if (this->dia < obj.dia)
        return true;
    else if (this->dia > obj.dia)
        return false;

    return false;
}

bool Fecha :: operator > (const Fecha &obj)const
{
    if (this->anio > obj.anio)
        return true;
    else if (this->anio < obj.anio)
        return false;

    if (this->mes > obj.mes)
        return true;
    else if (this->mes < obj.mes)
        return false;

    if (this->dia > obj.dia)
        return true;
    else if (this->dia < obj.dia)
        return false;

    return false;
}

bool Fecha :: operator <= (const Fecha &obj)const
{
    if (this->dia == obj.dia && this->mes == obj.mes && this->anio == obj.anio)
        return true;

    if (this->anio < obj.anio)
        return true;
    else if (this->anio > obj.anio)
        return false;

    if (this->mes < obj.mes)
        return true;
    else if (this->mes > obj.mes)
        return false;

    if (this->dia < obj.dia)
        return true;
    else if (this->dia > obj.dia)
        return false;

    return false;
}

bool Fecha :: operator >= (const Fecha &obj)const
{
    if (this->dia == obj.dia && this->mes == obj.mes && this->anio == obj.anio)
        return true;

    if (this->anio > obj.anio)
        return true;
    else if (this->anio < obj.anio)
        return false;

    if (this->mes > obj.mes)
        return true;
    else if (this->mes < obj.mes)
        return false;

    if (this->dia > obj.dia)
        return true;
    else if (this->dia < obj.dia)
        return false;

    return false;
}
