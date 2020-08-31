#include <iostream>
#include "fecha.h"

using namespace std;

int main()
{
    Fecha fec(29, 3, 1);
    Fecha fec2(29, 3, 1);

   if (fec >= fec2)
        cout << "Fec es mayor o igual" << endl;
    else
        cout << "Fec2 es mayor" << endl;
    return 0;
}
