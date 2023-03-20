#include <iostream>
#include "xtLAPACK.h"

int main () {
    int n;
    Matrix <double> A, b;

    std :: cin >> n;

    A.M = A.N = n;
    b.M = n, b.N = 1;
    for (int i = 1; i <= n; ++ i)
        for (int j = 1; j <= n; ++ j)
            std :: cin >> A.arr [i][j];

    for (int i = 1; i <= n; ++ i)
        std :: cin >> b.arr [i][1];

    b = solveImprovedCholesky (A, b);
    b.printMatrix ();

    return 0;
}