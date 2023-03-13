#include <iostream>
#include "la.h"

int m1, n1, m2, n2, _arr [MAXN][MAXN];

int main () {
    Matrix <int> Mat1, Mat2, Mat3;

    std :: cin >> m1 >> n1;
    //std :: cin >> m1 >> n1 >> m2 >> n2;
    for (int i = 1; i <= m1; ++ i)
        for (int j = 1; j <= n1; ++ j)
            std :: cin >> _arr [i][j];

    Mat1.buildMatrix (m1, n1, _arr);

    /*for (int i = 1; i <= m2; ++ i)
        for (int j = 1; j <= n2; ++ j)
            std :: cin >> _arr [i][j];

    Mat2.buildMatrix (m2, n2, _arr);

    Mat3 = Mat1 * Mat2;

    Mat3.printMatrix ();*/

    Mat1.rowReduction ();

    Mat1.printMatrix ();

    return 0;
}