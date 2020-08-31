#include "complejos.h"

using namespace std;

/** Constructores */

Complejos :: Complejos(const int real, const int imagi)
{
    this->real = real;
    this->imagi = imagi;
}

Complejos :: Complejos(const Complejos & obj)
{
    this->real = obj.real;
    this->imagi = obj.imagi;
}

/** Get y set */

int Complejos :: getReal()
{
    return this->real;
}

int Complejos :: getImagi()
{
    return this->imagi;
}

void Complejos :: setReal(const int num)
{
    this->real = num;
}

void Complejos :: setImagi(const int num)
{
    this->imagi = num;
}

/** Métodos */

void Complejos :: mostrar()
{
    cout << "(" << this->real << ", " << this->imagi << "i)" << endl;
}

/** Operadores */

Complejos & Complejos :: operator = (const Complejos &obj)
{
    this->real = obj.real;
    this->imagi = obj.imagi;

    return *this;
}

Complejos & Complejos :: operator += (const Complejos &obj)
{
    this->real += obj.real;
    this->imagi += obj.imagi;

    return *this;
}

Complejos & Complejos :: operator -= (const Complejos &obj)
{
    this->real -= obj.real;
    this->imagi -= obj.imagi;

    return *this;
}

Complejos & Complejos :: operator *= (const Complejos &obj)
{
    this->real = this->real*obj.real - this->imagi*obj.imagi;
    this->imagi = this->real*obj.imagi + this->imagi*obj.real;

    return *this;
}

Complejos & Complejos :: operator /= (const Complejos &obj)
{
    int divisor = (obj.real * obj.real + obj.imagi * obj.imagi);

    this->real = (this->real*obj.real + this->imagi*obj.imagi)/divisor;
    this->imagi = (this->imagi*obj.real - this->real*obj.imagi)/divisor;

    return *this;
}

Complejos Complejos :: operator + (const Complejos &obj)const
{
    return Complejos(this->real + obj.real, this->imagi + obj.imagi);
}

Complejos Complejos :: operator - (const Complejos &obj)const
{
    return Complejos(this->real - obj.real, this->imagi - obj.imagi);
}

Complejos Complejos :: operator * (const Complejos &obj)const
{
    return Complejos(this->real*obj.real - this->imagi*obj.imagi, this->real*obj.imagi + this->imagi*obj.real);
}

Complejos Complejos :: operator / (const Complejos &obj)const
{
    int divisor = (obj.real * obj.real + obj.imagi * obj.imagi);
    return Complejos((this->real*obj.real + this->imagi*obj.imagi)/divisor, (this->imagi*obj.real - this->real*obj.imagi)/divisor);
}

bool Complejos :: operator == (const Complejos &obj)const
{
    return this->real == obj.real && this->imagi == obj.imagi;
}

bool Complejos :: operator >= (const Complejos &obj)const
{
    return this->real >= obj.real && this->imagi >= obj.imagi;
}

bool Complejos :: operator <= (const Complejos &obj)const
{
    return this->real <= obj.real && this->imagi <= obj.imagi;
}

bool Complejos :: operator > (const Complejos &obj)const
{
    if (this->real > obj.real)
        return true;
    else if (this->real == obj.real)
        return this->imagi > obj.imagi;

    return false;
}

bool Complejos :: operator < (const Complejos &obj)const
{
    if (this->real < obj.real)
        return true;
    else if (this->real == obj.real)
        return this->imagi < obj.imagi;

    return false;
}

Complejos Complejos :: operator + (const int num)const
{
    return Complejos(this->real+num);
}

Complejos Complejos :: operator - (const int num)const
{
    return Complejos(this->real-num);
}

Complejos operator + (const int num, const Complejos &obj)
{
    return Complejos(obj.real+num, obj.imagi);
}

Complejos operator - (const int num, const Complejos &obj)
{
    return Complejos(obj.real-num, obj.imagi);
}

ostream & operator << (ostream & salida, const Complejos &obj)
{
    salida << "(" << obj.real << ", " << obj.imagi << "i)" << endl;
    return salida;
}

istream & operator >> (istream & entrada, Complejos &obj)
{
    cout << "Ingrese la parte real: ";
    entrada >> obj.real;
    cout << "Ingrese la parte imaginaria: ";
    entrada >> obj.imagi;
    return entrada;
}
