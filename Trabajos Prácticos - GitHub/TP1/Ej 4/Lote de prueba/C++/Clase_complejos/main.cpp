#include <iostream>
#include "complejos.h"

using namespace std;

int main()
{
    Complejos c1(1, 2), c2(3, 4), c3;

    c1.mostrar();

    c3 = c1 + c2;
    cout << c3;

    return 0;
}
