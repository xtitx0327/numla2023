#include <iostream>
#include "xtLAPACK.h"

Matrix <double> A, b, x1, x2;

int main () {
    A.M = A.N = 84;
    b.M = 84; b.N = 1;

    for (int i = 1; i <= 84; ++ i) {
        A.arr [i][i] = 6;
        if (i + 1 <= 84)
            A.arr [i][i + 1] = 1;
        if (i - 1 >= 1)
            A.arr [i][i - 1] = 8;
    }

    for (int i = 2; i <= 83; ++ i)
        b.arr [i][1] = 15;
    
    b.arr [1][1] = 7;
    b.arr [84][1] = 14;

    // 初始化增广矩阵

    x1 = solveGauss (A, b);
    x2 = solveColumnPivotGauss (A, b);

    // 依次用不选主元和列主元法解方程组

    for (int i = 1; i <= 84; ++ i)
        std :: cout << "x_" << i << " = " << x1.arr [i][1] << "    " << x2.arr [i][1] << std :: endl;

    std :: cout << "左侧为不选主元法得到的结果，右侧为列主元法得到的结果." << std :: endl; 

    return 0;
}