//
// Created by BZH on 2024/1/6.
//

#ifndef SHORTESTPATH_H
#define SHORTESTPATH_H

namespace pc1 {
    using namespace std;

    struct Edge {
        int from, to, w, c = 1, next = -1;
    };

    class SPFA {
    public:
        int n, m, s;
        vector<int> head;
        vector<Edge> edges;
        vector<long long> dis;
        vector<int> inq, cnt;

        SPFA() {
            input();
        }

        bool run() {
            queue<int> q;
            dis[s] = 0;
            q.push(s);
            inq[s] = 1;
            while(!q.empty()) {
                auto now = q.front();
                q.pop();
                inq[now] = 0;
                for(auto eg = head[now];eg >= 0;eg = edges[eg].next) {
                    int to = edges[eg].to, w = edges[eg].w;
                    if(dis[to] > dis[now] + w) {
                        dis[to] = dis[now] + w;
                        if(!inq[to]) {
                            q.push(to);
                            inq[to] = 1;
                            cnt[to] = cnt[now] + 1;
                            if(cnt[to] >= n)
                                return false;
                        }
                    }
                }
            }
            return true;
        }

        void output() {
            for(int i=1;i<=n;i++)
                cout << dis[i] << " ";
            cout << endl;
        }

        void input() {
            cin >> n >> m >> s;
            head.resize(n+1, -1); // vertex index start from 1
            edges.resize(m);
            dis.resize(n+1, LLONG_MAX / 2);  // note: overflow
            inq.resize(n+1, 0);
            cnt.resize(n+1, 0);
            int u, v, w;
            for(int i=0;i<m;i++) {
                cin >> u >> v >> w;
                edges[i] = {u, v, w, 1, head[u]};
                // edges[i+1] = {v, u, 0, 1, head[v]};
                head[u] = i;
            }
        }
    };
}

#endif //SHORTESTPATH_H
