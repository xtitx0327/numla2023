/**
 * @file xtLAPACK.h
 * @author 王笑同 (3210105450@zju.edu.cn)
 * @brief 基于 2022 - 2023 春夏《数值代数》课堂内容，自行完成的 C++ 头文件库，实现了课本上的主要算法
 * @version 0.1
 * @date 2023-03-13
 * @attention 项目网站：https://github.com/xtitx0327/numla2023
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef _xtLAPACK
#define _xtLAPACK

///@brief 矩阵的行列数上限
#define MAXN 85

#include <iostream>
#include <cstring>
#include <cmath>

template <typename DT>
class Matrix
{
private:
    /// @brief 矩阵初等行变换一：倍乘矩阵的某一行
    /// @param r 被乘的行号
    /// @param val 所乘的数值
    void rowMultiplication(int r, DT val)
    {
        if (r < 1 || r > M)
        {
            _errMessage = 1;
            return;
        }

        for (int i = 1; i <= N; ++i)
            arr[r][i] *= val;
    }

    /// @brief 矩阵初等行变换二：交换矩阵的某两行
    void rowExchange(int r1, int r2)
    {
        if (r1 < 1 || r1 > M || r2 < 1 || r2 > M)
        {
            _errMessage = 1;
            return;
        }

        static DT tmp;

        for (int i = 1; i <= N; ++i)
        {
            tmp = arr[r1][i];
            arr[r1][i] = arr[r2][i];
            arr[r2][i] = tmp;
        }
    }

    /// @brief 矩阵初等行变换三：将矩阵第 r2 行的 val 倍加到第 r1 行上
    void rowAddition(int r1, int r2, DT val)
    {
        if (r1 < 1 || r1 > M || r2 < 1 || r2 > M)
        {
            _errMessage = 1;
            return;
        }

        for (int i = 1; i <= N; ++i)
            arr[r1][i] += arr[r2][i] * val;
    }

public:
    /// @brief 矩阵的行数和列数
    int M, N;
    DT arr[MAXN][MAXN];

    Matrix()
    {
        M = N = 0;
        _errMessage = 0;
        memset(arr, 0, sizeof(arr));
    }
    ~Matrix()
    {
    }

    /// @brief 用于传递错误信息的内部指标
    int _errMessage;

    /// @brief 检测当前矩阵是否为上三角
    bool isUpperTriangular () {
        if (M != N)
            return 0;
        for (int i = 2; i <= N; ++ i)
            for (int j = 1; j < i; ++ j)
                if (arr [i][j] != 0)
                    return 0;
        
        return 1;
    }

    /// @brief 检测当前矩阵是否为下三角 
    bool isLowerTriangular () {
        if (M != N)
            return 0;
        for (int i = 1; i < N; ++ i)
            for (int j = i + 1; j <= N; ++ j)
                if (arr [i][j] != 0)
                    return 0;
        
        return 1;
    }

    /// @brief 通过 Gauss 消元法，将方阵分解为下三角和上三角矩阵的乘积，仍存储在当前矩阵中
    void GaussLU () {
        if (M != N) {
            _errMessage = 1;
            return;
        }
        for (int k = 1; k < N; ++ k) {
            for (int i = k + 1; i <= N; ++ i)
                arr [i][k] /= arr [k][k];
            for (int i = k + 1; i <= N; ++ i)
                for (int j = k + 1; j <= N; ++ j)
                    arr [i][j] -= arr [i][k] * arr [k][j];
        }
    }

    /// @brief 计算矩阵乘积 M*M2，其中 M 为当前矩阵
    Matrix<DT> operator*(const Matrix<DT> &M2)
    {
        Matrix<DT> res;
        if (N != M2.M)
        {
            res._errMessage = 1;
            return res;
        }

        res.M = M;
        res.N = M2.N;

        for (int i = 1; i <= res.M; ++i)
            for (int j = 1; j <= res.N; ++j)
                for (int k = 1; k <= N; ++k)
                    res.arr[i][j] += arr[i][k] * M2.arr[k][j];

        return res;
    }

    /// @brief 返回当前矩阵的某个子矩阵
    /// @param x 子矩阵的左上角在原矩阵中的行号
    /// @param y 子矩阵的左上角在原矩阵中的列号
    /// @param k 子矩阵的行数
    /// @param l 子矩阵的列数
    /// @return
    Matrix<DT> getSubMatrix(int x, int y, int k, int l)
    {
        Matrix<DT> res;

        if ((x + k > M) || (y + l > N))
        {
            res._errMessage = 1;
            return res;
        }

        res.M = M;
        res.N = N;

        for (int i = x; i < x + k; ++i)
            for (int j = y; j < y + l; ++j)
                res.arr[i - x + 1][j - y + 1] = arr[i][j];

        return res;
    }

    /// @brief 计算当前矩阵的行列式（未完成）
    DT getDeterminant()
    {
        if (M != N)
        {
            _errMessage = 2;
            return 0;
        }

        if (N == 1)
            return arr[1][1];
        else if (N == 2)
            return arr[1][1] * arr[2][2] - arr[1][2] * arr[2][1];
        else
        {
            DT res = 0;
            for (int i = 1; i <= N; ++i)
            {
            }
            return res;
        }
    }

    /// @brief 构建矩阵
    void buildMatrix(int _M, int _N, int _arr[MAXN][MAXN])
    {
        M = _M;
        N = _N;
        _errMessage = 0;
        for (int i = 1; i <= M; ++i)
            for (int j = 1; j <= N; ++j)
                arr[i][j] = _arr[i][j];
    }

    /// @brief 打印当前矩阵
    void printMatrix()
    {
        std :: cout << std ::endl;
        if (_errMessage) {
            std :: cout << "警告：矩阵运算过程中出现错误，不能输出！" << std :: endl;
            return;
        }
        for (int i = 1; i <= M; ++i)
        {
            for (int j = 1; j <= N; ++j)
                std ::cout << arr[i][j] << " ";
            std ::cout << std ::endl;
        }
    }
};

/// @brief 构建系数矩阵 A 和常数矩阵 b 的增广矩阵
template <typename DT>
Matrix <DT> buildAugmented (Matrix <DT> A, Matrix <DT> b) {
    Matrix <DT> mAug;
    
    if (A.M != b.M || A.N != b.N) {
        mAug._errMessage = 1;
        return mAug;
    }

    mAug.M = A.M;
    mAug.N = A.N + 1;

    for (int i = 1; i <= A.M; ++ i)
        for (int j = 1; j <= A.N; ++ j)
            mAug.arr [i][j] = A.arr [i][j];
    
    for (int i = 1; i <= A.M; ++ i)
        mAug.arr [i][A.N + 1] = b.arr [i][1];
    
    return mAug;
}

/// @brief 通过前代法解下三角矩阵为系数矩阵 A 的线性方程组，b 是常数矩阵（此函数由个人完成，未经常数优化）
template <typename DT> 
Matrix <DT> forwardSub (Matrix <DT> A, Matrix <DT> b) {
    Matrix <DT> ret;
    ret.M = b.M;
    ret.N = 1;

    if (!A.isLowerTriangular () || b.M != A.M || b.N != 1) {
        ret._errMessage = 1;
        return ret;
    }

    for (int i = 1; i <= A.M; ++ i) {
        ret.arr [i][1] = b.arr [i][1] / A.arr [i][i];
        for (int j = 1; j < i; ++ j) 
            ret.arr [i][1] -= A.arr [i][j] * ret.arr [j][1] / A.arr [i][i]; 
    }

    return ret;
}

/// @brief 通过回代法/后代法解上三角矩阵为系数矩阵 A 的线性方程组，b 是常数矩阵（此函数由个人完成，未经常数优化）
template <typename DT>
Matrix <DT> backwardSub (Matrix <DT> A, Matrix <DT> b) {
    Matrix <DT> ret;
    ret.M = b.M;
    ret.N = 1;

    if (!A.isUpperTriangular () || b.M != A.M || b.N != 1) {
        ret._errMessage = 1;
        return ret;
    }

    for (int i = A.M; i >= 1; -- i) {
        ret.arr [i][1] = b.arr [i][1] / A.arr [i][i];
        for (int j = i + 1; j <= A.M; ++ j)
            ret.arr [i][1] -= A.arr [i][j] * ret.arr [j][1] / A.arr [i][i];
    }

    return ret;
}

/// @brief 利用 Gauss 消元法，解方程组 Ax=b 
template <typename DT>
Matrix <DT> solveGauss (Matrix <DT> A, Matrix <DT> b) {
    Matrix <DT> ret, tmp;
    if (A.M != A.N || A.M != b.M || b.N != 1) {
        ret._errMessage = 1;
        return ret;
    }

    A.GaussLU ();
    tmp.M = tmp.N = A.M;

    for (int i = 1; i <= A.M; ++ i)
        for (int j = 1; j <= i; ++ j)
            tmp.arr [i][j] = (i == j ? 1 : A.arr [i][j]);
    
    b = forwardSub (tmp, b);

    memset (tmp.arr, 0, sizeof (tmp.arr));

    for (int i = 1; i <= A.M; ++ i)
        for (int j = i; j <= A.M; ++ j)
            tmp.arr [i][j] = A.arr [i][j];

    b = backwardSub (tmp, b);

    return b;
}

template <typename DT>
Matrix <DT> solveCompletePivotGauss (Matrix <DT> A, Matrix <DT> b) {
    Matrix <DT> ret;
    if (A.M != A.N || A.M != b.M || b.N != 1) {
        ret._errMessage = 1;
        return ret;
    }

    int p, q, maxVal, u [MAXN], v [MAXN];

    for (int k = 1; k < A.M; ++ k) {
        maxVal = -1;
        for (int i = k; i <= A.M; ++ i)
            for (int j = k; j <= A.M; ++ j)
                if (fabs (A.arr [i][j]) >= maxVal) {
                    maxVal = fabs (A.arr [i][j]);
                    p = i;
                    q = j;
                }
        for (int i = 1; i <= A.M; ++ i)
            std :: swap (A.arr [k][i], A.arr [p][i]);
        for (int i = 1; i <= A.M; ++ i)
            std :: swap (A.arr [i][k], A.arr [i][q]);
        
        u [k] = p;
        v [k] = q;
        if (A.arr [k][k] != 0) {
            for (int i = k + 1; i <= A.M; ++ i)
                A.arr [i][k] /= A.arr [k][k];
            for (int i = k + 1; i <= A.M; ++ i)
                for (int j = k + 1; j <= A.M; ++ j)
                    A.arr [i][j] -= A.arr [i][k] * A.arr [k][j];
        } else {
            ret._errMessage = 3; // 矩阵奇异
            return ret;
        }
    }

    Matrix <DT> tmp;
    tmp.M = tmp.N = A.M;

    for (int i = 1; i <= A.M; ++ i)
        for (int j = 1; j <= i; ++ j)
            tmp.arr [i][j] = (i == j ? 1 : A.arr [i][j]);
    
    for (int i = 1; i < A.M; ++ i)
        std :: swap (b.arr [i][1], b.arr [u [i]][1]);

    b = forwardSub (tmp, b);

    memset (tmp.arr, 0, sizeof (tmp.arr));

    for (int i = 1; i <= A.M; ++ i)
        for (int j = i; j <= A.M; ++ j)
            tmp.arr [i][j] = A.arr [i][j];
    
    b = backwardSub (tmp, b);

    for (int i = A.M - 1; i >= 1; -- i)
        std :: swap (b.arr [i][1], b.arr [v [i]][1]);
    
    return b;
}

template <typename DT>
Matrix <DT> solveColumnPivotGauss (Matrix <DT> A, Matrix <DT> b) {
    Matrix <DT> ret;
    if (A.M != A.N || A.M != b.M || b.N != 1) {
        ret._errMessage = 1;
        return ret;
    }

    int p, maxVal, u [MAXN];

    for (int k = 1; k < A.M; ++ k) {
        maxVal = -1;
        for (int i = k; i <= A.M; ++ i)
            if (fabs (A.arr [i][k]) >= maxVal) {
                maxVal = fabs (A.arr [i][k]);
                p = i;
            }
        for (int i = 1; i <= A.M; ++ i)
            std :: swap (A.arr [k][i], A.arr [p][i]);
        
        u [k] = p;
        if (A.arr [k][k] != 0) {
            for (int i = k + 1; i <= A.M; ++ i)
                A.arr [i][k] /= A.arr [k][k];
            for (int i = k + 1; i <= A.M; ++ i)
                for (int j = k + 1; j <= A.M; ++ j)
                    A.arr [i][j] -= A.arr [i][k] * A.arr [k][j];
        } else {
            ret._errMessage = 3; // 矩阵奇异
            return ret;
        }
    }

    Matrix <DT> tmp;
    tmp.M = tmp.N = A.M;

    for (int i = 1; i <= A.M; ++ i)
        for (int j = 1; j <= i; ++ j)
            tmp.arr [i][j] = (i == j ? 1 : A.arr [i][j]);
    
    for (int i = 1; i < A.M; ++ i)
        std :: swap (b.arr [i][1], b.arr [u [i]][1]);

    b = forwardSub (tmp, b);

    memset (tmp.arr, 0, sizeof (tmp.arr));

    for (int i = 1; i <= A.M; ++ i)
        for (int j = i; j <= A.M; ++ j)
            tmp.arr [i][j] = A.arr [i][j];
    
    b = backwardSub (tmp, b);
    
    return b;
}

#endif