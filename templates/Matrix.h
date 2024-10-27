//
// Created by BZH on 24-2-4.
//

#ifndef MATRIX_H
#define MATRIX_H

#include "pc.h"

namespace pc {
    template<int MOD>
    class matrix {
    public:
        vector<vector<long long>> data;
        int n;
        matrix(vector<vector<long long>> a):data(a), n(a.size()) {

        }
        matrix(int _n):n(_n) {
            data.resize(n, vector<long long>(n));
        }
        matrix operator*(matrix b) {
            matrix ret(n);
            for(int i=0;i<n;i++) {
                for(int j=0;j<n;j++) {
                    ret.data[i][j] = 0;
                    for(int k = 0;k < n;k++) {
                        ret.data[i][j] += data[i][k] * b.data[k][j];
                        ret.data[i][j] %= MOD;
                    }
                }
            }
            return ret;
        }
    };

    // 矩阵快速幂
    template<int MOD>
    matrix<MOD> mpow(matrix<MOD> a, int b) {
        if (b == 0)
            return matrix<MOD>(vector<vector<long long>>{{1,0},{0,1}});
        if (b % 2 == 0)
            return mpow((a * a), b / 2);
        return a * mpow((a * a), b / 2);
    }
}

#endif //MATRIX_H
