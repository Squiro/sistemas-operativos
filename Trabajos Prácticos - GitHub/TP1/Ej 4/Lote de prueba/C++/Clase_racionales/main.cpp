#include <iostream>
#include "racionales.h"

using namespace std;

int main()
{
    //bool val;
    Racionales rac(1, 2), rac2(4,5), rac3;

    //val = Racionales::validar(0);

    //cout << "VAL: " << val << endl;

    rac.mostrar();

    rac3 = rac*rac2;

    rac3.mostrar();
    return 0;
}
