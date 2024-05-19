//
// Created by Bao Ziheng on 2024/5/19.
//

#ifndef PC_TEMPLATE_SCC_H
#define PC_TEMPLATE_SCC_H

#include <bits/stdc++.h>

namespace pc {
    using namespace std;

    // index start from 0
    class SCC {
    public:
        int n;
        vector<int> dfsn, low, instk, scc;
        int cnt = 0, cscc = 0;
        stack<int> stk;
        vector<vector<int>>& g;

        SCC (int n, vector<vector<int>>& g): n(n), g(g){
            dfsn.resize(n, 0);
            low.resize(n, 0);
            instk.resize(n, 0);
            scc.resize(n, 0);

            // build tarjan
            for(int i=0;i<n;i++){
                if(!dfsn[i])
                    tarjan(i);
            }
        }

        void tarjan(int p){
            low[p] = dfsn[p] = ++cnt;
            instk[p] = 1;
            stk.push(p); // 进栈
            for (auto q : g[p]) {
                if (!dfsn[q]) { // 未访问过
                    tarjan(q); // 递归地搜索
                    low[p] = min(low[p], low[q]);
                }
                else if (instk[q]) // 访问过，且q可达p
                    low[p] = min(low[p], dfsn[q]);
            }
            if (low[p] == dfsn[p]) { // 发现强连通分量的根
                int top;
                cscc++;
                do {
                    top = stk.top();
                    stk.pop();
                    instk[top] = 0;
                    scc[top] = cscc; // 记录所属的强连通分量
                } while (top != p); // 直到弹出p才停止
            }
        }
    };
}

#endif //PC_TEMPLATE_SCC_H
