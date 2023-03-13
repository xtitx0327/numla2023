#ifndef _LA
#define _LA

///@brief 矩阵的行列数上限
#define MAXN 15

#include <iostream>
#include <cstring>

template <typename DT>
class Matrix
{
private:
    /// @brief 用于传递错误信息的内部指标
    int _errMessage;

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
    /// @brief 对当前矩阵做行约化，并将结果返回
    Matrix rowReduction()
    {
        Matrix<DT> res;
        Matrix<DT> tmp;

        if (M != N)
        {
            res._errMessage = 1;
            return res;
        }

        res.M = M;
        res.N = N;
        for (int i = 1; i <= N; ++i)
            for (int j = 1; j <= N; ++j)
                res.arr[i][j] = arr[i][j];

        if (N == 1)
        {
            res.M = res.N = 1;
            res.arr[1][1] = arr[1][1];
            return res;
        }

        // 找到第一个首元素非零的行
        int flag = 0;
        for (int i = 1; i <= N; ++i)
            if (arr[i][1] != 0)
            {
                flag = i;
                break;
            }

        if (flag)
        {
            res.rowExchange(flag, 1);
            for (int i = 2; i <= N; ++i)
                res.rowAddition(i, 1, -1 * arr[i][1]);
        }

        tmp = res.getSubMatrix(2, 2, N - 1, N - 1);

        tmp.rowReduction();

        for (int i = 2; i <= N; ++i)
            for (int j = 2; j <= N; ++j)
                arr[i][j] = tmp.arr[i - 1][j - 1];

        return res;
    }

public:
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
        std ::cout << std ::endl;
        for (int i = 1; i <= M; ++i)
        {
            for (int j = 1; j <= N; ++j)
                std ::cout << arr[i][j] << " ";
            std ::cout << std ::endl;
        }
    }
};

#endif