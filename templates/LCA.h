//
// Created by Ziheng Bao on 2023/12/19.
//

#ifndef PC_TEMPLATE_LCA_H
#define PC_TEMPLATE_LCA_H

#include<bits/stdc++.h>

namespace pc{
    using namespace std;
    class LCA{
    public:
        vector<vector<int>> g;
        vector<vector<int>> up;
        vector<int> in, out;
        int T = 0;
        int n, k;

        void build(int now, int pre){
            in[now] = T++;
            up[now][0] = pre;
            for(int i=1;i<k;i++){
                up[now][i] = up[up[now][i-1]][i-1];
            }
            for(auto next:g[now]){
                if(next == pre)
                    continue;
                build(next, now);
            }
            out[now] = T++;
        }

        LCA(vector<vector<int>> _g, int root = 0):g(_g){
            n = g.size();
            k = log2(n) + 1;
            up = vector<vector<int>>(n, vector<int>(k));
            in.resize(n);
            out.resize(n);
            build(root, 0);
        }

        bool is_ancestor(int x, int y){ // x is ancestor of y
            return in[x] <= in[y] && out[x] >= out[y];
        }

        int get(int x, int y){
            if(is_ancestor(x, y)) return x;
            for(int i = up[0].size()-1;i>=0;i--){
                if(!is_ancestor(up[x][i], y))
                    x = up[x][i];
            }
            return up[x][0];
        }
    };
}

#endif //PC_TEMPLATE_LCA_H
