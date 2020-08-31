#pragma once
#include <iostream>

using namespace std;

class Racionales
{
    private:
        int nume;
        int denom;

    public:
        //Constructores
        Racionales(const int = 1, const int = 1);
        Racionales(const Racionales &);

        //Get y Set
        int getNume();
        int getDenom();
        void setNume(const int);
        void setDenom(const int);

        //Métodos
        void mostrar();
        static bool validar(const int);
        static int hallarMCD(const int, const int);
        void simplificar(Racionales &);

        //Operadores
        //Entre clase Racionales
        Racionales & operator = (const Racionales &);
        Racionales & operator += (const Racionales &);
        Racionales & operator -= (const Racionales &);
        Racionales & operator *= (const Racionales &);
        Racionales & operator /= (const Racionales &);
        Racionales operator + (const Racionales &)const;
        Racionales operator - (const Racionales &)const;
        Racionales operator * (const Racionales &)const;
        Racionales operator / (const Racionales &)const;
        bool operator == (const Racionales &)const;
        bool operator > (const Racionales &)const;
        bool operator < (const Racionales &)const;
        bool operator >= (const Racionales &)const;
        bool operator <= (const Racionales &)const;

        //Entre racionales y enteros
        Racionales operator + (const int)const;
        Racionales operator - (const int)const;
        friend Racionales operator + (const int, const Racionales &);
        friend Racionales operator - (const int, const Racionales &);
};
