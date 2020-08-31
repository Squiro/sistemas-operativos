#pragma once
#include <iostream>

using namespace std;

class Fecha
{
    private:
        //Atributos
        int dia;
        int mes;
        int anio;

    public:
        //Constructores
        Fecha(const int = 1, const int = 1, const int = 1990); //Constructor parametrizado y por defecto
        Fecha(const Fecha &); //Constructor por fecha

        //Get y Set ("propiedades")
        int getDia();
        int getMes();
        int getAnio();
        void setDia(const int);
        void setMes(const int);
        void setAnio(const int);

        //Métodos
        static bool validarFecha(const int, const int, const int); //Método estático
        static bool es_bisiesto(const int);
        void mostrar();

        //Operadores
        //Entre clase fecha
        Fecha & operator = (const Fecha &);
        Fecha & operator += (const Fecha &);
        Fecha & operator -= (const Fecha &);
        Fecha operator + (const Fecha &)const;
        Fecha operator - (const Fecha &)const;
        bool operator == (const Fecha &)const;
        bool operator < (const Fecha &)const;
        bool operator > (const Fecha &)const;
        bool operator >= (const Fecha &)const;
        bool operator <= (const Fecha &)const;

        //Clase fecha y enteros
        Fecha operator - (const int)const;
        Fecha operator + (const int)const;
        friend Fecha operator + (const int, const Fecha &);
        friend Fecha operator - (const int, const Fecha &);
};
