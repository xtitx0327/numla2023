#include <iostream>
#include "xtLAPACK.h"

int main () {
    Matrix <double> A, b;

    A.M = A.N = 3;
    for (int i = 1; i <= 3; ++ i)
        for (int j = 1; j <= 3; ++ j)
            std :: cin >> A.arr [i][j];

    b.M = 3; b.N = 1;
    for (int i = 1; i <= 3; ++ i)
        std :: cin >> b.arr [i][1];

    b = backwardSub (A, b);

    b.printMatrix ();

    return 0;
}