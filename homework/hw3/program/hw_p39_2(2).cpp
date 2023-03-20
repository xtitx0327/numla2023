#include <iostream>
#include <ctime>
#include "xtLAPACK.h"

int main () {
    srand ((unsigned) time (0));
    Matrix <double> A, b, sol1, sol2;

    A.M = A.N = 40;
    b.M = 40, b.N = 1;

    for (int i = 1; i <= 40; ++ i)
        for (int j = 1; j <= 40; ++ j)
            A.arr [i][j] = 1.0 / (i + j - 1);

    for (int i = 1; i <= 40; ++ i)
        for (int j = 1; j <= i; ++ j)
            b.arr [i][1] += 1.0 / (i + j - 1);

    sol1 = solveCholesky (A, b);
    sol2 = solveImprovedCholesky (A, b);

    for (int i = 1; i <= 40; ++ i)
        std :: cout << "x_" << i << " = " << sol1.arr [i][1] << "   " << sol2.arr [i][1] << std :: endl;
    
    return 0;
}