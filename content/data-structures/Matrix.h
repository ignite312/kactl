/**
 * Author: Ulf Lundstrom
 * Date: 2009-08-03
 * License: CC0
 * Source: My head
 * Description: Basic operations on square matrices.
 * Usage: Matrix<int, 3, 3> A;
 *  A.d = {{{{1,2,3}}, {{4,5,6}}, {{7,8,9}}}};
 *  vector<int> vec = {1,2,3};
 *  vec = (A^N) * vec;
 * Status: tested
 */
#pragma once

template<class T, int N, int M> struct Matrix {
    typedef Matrix Mx;
    array<array<T, M>, N> d{};
    // Matrix multiplication
    template<int P>
    Matrix<T, N, P> operator*(const Matrix<T, M, P>& m) const {
        Matrix<T, N, P> a;
        for (int i = 0; i < N; i++) 
            for (int j = 0; j < P; j++)
                for (int k = 0; k < M; k++)
                    a.d[i][j] += d[i][k] * m.d[k][j];
        return a;
    }
    // Matrix-vector multiplication
    vector<T> operator*(const vector<T>& vec) const {
        vector<T> ret(N, 0);
        for (int i = 0; i < N; i++)
            for (int j = 0; j < M; j++)
                ret[i] += d[i][j] * vec[j];
        return ret;
    }
    // Matrix exponentiation
    Matrix<T, N, N> operator^(ll p) const {
        static_assert(N == M);assert(p >= 0);
        Matrix<T, N, N> a, b(*this);
        for (int i = 0; i < N; i++) a.d[i][i] = 1; // Identity matrix
        while (p) {
            if (p & 1) a = a * b;
            b = b * b;
            p >>= 1;
        }
        return a;
    }
};
