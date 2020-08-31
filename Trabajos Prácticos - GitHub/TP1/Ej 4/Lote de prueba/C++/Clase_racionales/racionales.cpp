#include "racionales.h"
#include <stdexcept>

/** Constructores */

Racionales :: Racionales(const int nume, const int denom)
{
    if (validar(denom))
        throw std::logic_error("El denominador no puede ser igual a 0.");

    this->nume = nume;
    this->denom = denom;
    simplificar(*this);
}

Racionales :: Racionales(const Racionales &obj)
{
    this->nume = obj.nume;
    this->denom = obj.denom;
}

/** Get y set */

int Racionales :: getNume()
{
    return this->nume;
}

int Racionales :: getDenom()
{
    return this->denom;
}

void Racionales :: setNume(const int nume)
{
    this->nume = nume;
}

void Racionales :: setDenom(const int denom)
{
    this->denom = denom;
}

/** Métodos */

void Racionales :: mostrar()
{
    if (this->nume != 0)
        cout << this->nume << "/" << this->denom << endl;
    else
        cout << "0" << endl;
}

bool Racionales :: validar(const int denom)
{
    return denom == 0;
}

void Racionales :: simplificar(Racionales &obj)
{
    int mcd = hallarMCD(obj.nume, obj.denom);

    obj.nume /= mcd;
    obj.denom /= mcd;
}

int Racionales :: hallarMCD(const int a, const int b)
{
    return b == 0 ? a : hallarMCD(b, a % b);
}

/** Operadores */

Racionales & Racionales :: operator = (const Racionales &obj)
{
    this->nume = obj.nume;
    this->denom = obj.denom;

    return *this;
}

Racionales & Racionales :: operator += (const Racionales &obj)
{
    if (this->denom == obj.denom)
        this->nume += obj.nume;
    else
    {
        this->nume = this->nume*obj.denom + obj.nume*this->denom;
        this->denom = this->denom*obj.denom;
    }

    simplificar(*this);

    return *this;
}

Racionales & Racionales :: operator -= (const Racionales &obj)
{
    if (this->denom == obj.denom)
        this->nume -= obj.nume;
    else
    {
        this->nume = this->nume*obj.denom - obj.nume*this->denom;
        this->denom = this->denom*obj.denom;
    }

    simplificar(*this);

    return *this;
}

Racionales & Racionales :: operator *= (const Racionales &obj)
{
    this->nume = this->nume * obj.nume;
    this->denom = this->denom * obj.denom;

    simplificar(*this);

    return *this;
}

Racionales & Racionales :: operator /= (const Racionales &obj)
{
    this->nume = this->nume * obj.denom;
    this->denom = this->denom * obj.nume;

    simplificar(*this);

    return *this;
}

Racionales Racionales :: operator + (const Racionales &obj)const
{
    if (this->denom == obj.denom)
        return Racionales(this->nume + obj.nume, this->denom);
    else
        return Racionales(this->nume*obj.denom + obj.nume*this->denom, this->denom*obj.nume);
}

Racionales Racionales :: operator - (const Racionales &obj)const
{
    if (this->denom == obj.denom)
        return Racionales(this->nume - obj.nume, this->denom);
    else
        return Racionales(this->nume*obj.denom - obj.nume*this->denom, this->denom*obj.nume);
}

Racionales Racionales :: operator * (const Racionales &obj)const
{
    return Racionales(this->nume * obj.nume, this->denom * obj.denom);
}

Racionales Racionales :: operator / (const Racionales &obj)const
{
    return Racionales(this->nume * obj.denom, this->denom * obj.nume);
}


bool Racionales :: operator == (const Racionales &obj)const
{
    return this->nume == obj.nume && this->denom == obj.denom;
}

bool Racionales :: operator > (const Racionales &obj)const
{
    if (this->nume < 0 && obj.nume > 0)
        return false;

    if (this->denom == obj.denom)
        return this->nume > obj.nume;

    return this->denom > obj.denom;
}

bool Racionales :: operator < (const Racionales &obj)const
{
    if (this->nume > 0 && obj.nume < 0)
        return false;

    if (this->denom == obj.denom)
        return this->nume < obj.nume;

    return this->denom < obj.denom;
}

bool Racionales :: operator >= (const Racionales &obj)const
{
    if (this->nume == obj.nume && this->denom == obj.denom)
        return true;

    if (this->nume < 0 && obj.nume > 0)
        return false;

    if (this->denom == obj.denom)
        return this->nume > obj.nume;

    return this->denom > obj.denom;
}

bool Racionales :: operator <= (const Racionales &obj)const
{
    if (this->nume == obj.nume && this->denom == obj.denom)
        return true;

    if (this->nume > 0 && obj.nume < 0)
        return false;

    if (this->denom == obj.denom)
        return this->nume < obj.nume;

    return this->denom < obj.denom;
}

Racionales Racionales :: operator + (const int ent)const
{
    if (this->denom == 1)
        return Racionales(this->nume+ent, 1);
    else
        return Racionales(this->nume*1 + ent*this->denom, this->denom);
}

Racionales Racionales :: operator - (const int ent)const
{
    if (this->denom == 1)
        return Racionales(this->nume-ent, 1);
    else
        return Racionales(this->nume*1 - ent*this->denom, this->denom);
}

Racionales operator + (const int ent, const Racionales &obj)
{
    if (obj.denom == 1)
        return Racionales(obj.nume+ent, 1);
    else
        return Racionales(obj.nume*1 + ent*obj.denom, obj.denom);
}

Racionales operator - (const int ent, const Racionales &obj)
{
    if (obj.denom == 1)
        return Racionales(obj.nume-ent, 1);
    else
        return Racionales(obj.nume*1 - ent*obj.denom, obj.denom);
}
