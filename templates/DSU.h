//
// Created by Ziheng Bao on 2024/3/8.
//

#ifndef PC_TEMPLATE_DSU_H
#define PC_TEMPLATE_DSU_H

#include "bits/stdc++.h"

namespace pc{
    using namespace std;

    class DSU{
    public:
        vector<int> pa, size;
        DSU(int n){
            pa.resize(n);
            size.resize(n, 1);
            iota(pa.begin(), pa.end(), 0);
        }

        int find(int x){
            return pa[x] == x ? x : (pa[x] = find(pa[x]));
        }

        void merge(int x, int y){ // x -> y
            x = find(x);
            y = find(y);
            if(x == y)
                return;
            pa[x] = y;
            size[y] += size[x];
        }
    };
}

#endif //PC_TEMPLATE_DSU_H
