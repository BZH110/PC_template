//
// Created by BZH on 2024/1/3.
//

#ifndef FLOW_H
#define FLOW_H

#include <bits/stdc++.h>

namespace pc {
    using namespace std;

    struct Edge {
        int from, to, w, c = 1, next = -1;
    };

    template <int MOD = LLONG_MAX>
    class MCMF {
    public:

    };

    template <int MOD = LLONG_MAX>
    class MaxFlow {
    public:
        int n, m, s, t;
        vector<int> head;
        vector<Edge> edges;
        vector<int> lv, cur;
        MaxFlow() {
            input();
        }

        void input() {
            cin >> n >> m >> s >> t;
            head.resize(n+1, -1); // vertex index start from 1
            edges.resize(2 * m);
            lv.resize(n+1);
            cur.resize(n+1);
            int u, v, w;
            for(int i=0;i<2*m;i+=2) {
                cin >> u >> v >> w;
                edges[i] = {u, v, w, 1, head[u]};
                edges[i+1] = {v, u, 0, 1, head[v]};
                head[u] = i;
                head[v] = i + 1;
            }
        }

        bool bfs() {
            fill(lv.begin(), lv.end(), -1);
            cur = head;
            lv[s] = 0;
            queue<int> q;
            q.push(s);
            while (!q.empty())
            {
                int p = q.front();
                q.pop();
                for (int eg = head[p]; eg >= 0; eg = edges[eg].next)
                {
                    int to = edges[eg].to, vol = edges[eg].w;
                    if (vol > 0 && lv[to] == -1)
                        lv[to] = lv[p] + 1, q.push(to);
                }
            }
            return lv[t] != -1;
        }

        int dfs(int p, int flow = 1e18) {
            if (p == t)
                return flow;
            int rmn = flow; // 剩余的流量
            for (int eg = cur[p]; eg >= 0 && rmn; eg = edges[eg].next) // 如果已经没有剩余流量则退出
            {
                cur[p] = eg; // 当前弧优化，更新当前弧
                int to = edges[eg].to, vol = edges[eg].w;
                if (vol > 0 && lv[to] == lv[p] + 1) // 往层数高的方向增广
                {
                    int c = dfs(to, min(vol, rmn)); // 尽可能多地传递流量
                    rmn -= c; // 剩余流量减少
                    edges[eg].w -= c; // 更新残余容量
                    edges[eg ^ 1].w += c; // 再次提醒，链式前向星的cnt需要初始化为1（或-1）才能这样求反向边
                }
            }
            return flow - rmn;
        }

        int dinic() {
            int ret = 0;
            while (bfs()) {
                ret += dfs(s);
                ret %= MOD;
            }
            return ret;
        }
    };

    inline int n, m, s, t;
    inline vector<int> head;
    inline vector<Edge> edges;
    void input() {
        cin >> n >> m >> s >> t;
        head.resize(n+1, -1); // vertex index start from 1
        edges.resize(2 * m);
        int u, v, w;
        for(int i=0;i<2*m;i+=2) {
            cin >> u >> v >> w;
            edges[i] = {u, v, w, 1, head[u]};
            edges[i+1] = {v, u, 0, 1, head[v]};
            head[u] = i;
            head[v] = i + 1;
        }
    }
}

#endif //FLOW_H
