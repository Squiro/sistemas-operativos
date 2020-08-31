#pragma once
#include <iostream>

using namespace std;

class Complejos
{
    private:
        int real;
        int imagi;

    public:
        //Constructores
        Complejos(const int real = 0, const int imagi = 0);
        Complejos(const Complejos &obj);

        //Métodos
        void mostrar();

        //Get y Set
        int getReal();
        int getImagi();
        void setReal(const int num);
        void setImagi(const int num);

        //Operadores
        //Entre clase complejos
        Complejos & operator = (const Complejos &obj);
        Complejos & operator += (const Complejos &obj);
        Complejos & operator -= (const Complejos &obj);
        Complejos & operator *= (const Complejos &obj);
        Complejos & operator /= (const Complejos &obj);
        Complejos operator + (const Complejos &obj)const;
        Complejos operator - (const Complejos &obj)const;
        Complejos operator * (const Complejos &obj)const;
        Complejos operator / (const Complejos &obj)const;
        bool operator == (const Complejos &obj)const;
        bool operator >= (const Complejos &obj)const;
        bool operator <= (const Complejos &obj)const;
        bool operator > (const Complejos &obj)const;
        bool operator < (const Complejos &obj)const;

        //Entre complejos y enteros
        Complejos operator + (const int num)const;
        Complejos operator - (const int num)const;
        friend Complejos operator + (const int num, const Complejos &obj);
        friend Complejos operator - (const int num, const Complejos &obj);

        //Entre complejos y otros
        friend ostream & operator << (ostream & salida, const Complejos &obj);
        friend istream & operator >> (istream & entrada, Complejos &obj);
};
