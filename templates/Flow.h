//
// Created by BZH on 2024/1/3.
//

#ifndef FLOW_H
#define FLOW_H

namespace pc {
    using namespace std;

    struct Edge {
        int from, to, w, c = 1, next = -1;
    };

    class MCMF2{
    public:
#ifndef INF
        long long INF = LLONG_MAX / 2;
#endif
        int n, m, s, t;
        vector<int> head, cur;
        vector<Edge> edges;
        vector<long long> dis;
        vector<int> vis;
        int maxf = 0, minc = 0;

        MCMF2(){
            input();
        }

        void add(int u, int v, int w, int c){
            edges.push_back({u, v, w, c, head[u]});
            head[u] = edges.size() - 1;
            edges.push_back({v, u, 0, -c, head[v]});
            head[v] = edges.size() - 1;
        }

        void input() {
            cin >> n >> m >> s >> t;
            head.resize(n + 1, -1); // vertex index start from 1
            dis.resize(n + 1, INF);
            vis.resize(n + 1, 0);

            int u, v, w, c = 1;
            for(int i = 0; i < m; i++) {
                cin >> u >> v >> w >> c;
                add(u, v, w, c);
                add(v, u, 0, -c);
            }
        }

        bool spfa(){
            fill(dis.begin(), dis.end(), INF);
            fill(vis.begin(), vis.end(), 0);
            cur = head; /* 当前弧优化 */
            queue<int> q;
            dis[s]=0;
            q.push(s);
            while(!q.empty()){
                int now=q.front();
                q.pop();
                vis[now] = 0;
                for(int i=head[now]; i >= 0; i=edges[i].next){
                    int v=edges[i].to, w = edges[i].w, c = edges[i].c;
                    if(dis[v] > dis[now] + edges[i].c && w){
                        dis[v] = dis[now] + c;
                        if(!vis[v]){
                            vis[v]=1;
                            q.push(v);
                        }
                    }
                }
            }
            return dis[t] != INF;
        }

        int dfs(int u, int t, int flow) {
            if (u == t) return flow;
            vis[u] = 1;
            int ans = 0;
            for (int& i = cur[u] /* 当前弧优化 */ ; i >= 0 && ans < flow; i = edges[i].next) {
                int v = edges[i].to, w = edges[i].w, c = edges[i].c;
                if (!vis[v] && w && dis[v] == dis[u] + c) {
                    int x = dfs(v, t, std::min(w, flow - ans));
                    if (x) minc += x * c, edges[i].w -= x, edges[i ^ 1].w += x, ans += x;
                }
            }
            vis[u] = 0;
            return ans;
        }

        void run(){
            maxf = minc = 0;
            while (spfa()) {
                int x;
                while ((x = dfs(s, t, INF))) maxf += x;
            }
        }
    };

    template <int MOD = LLONG_MAX>
    class MCMF {
    public:
        int n, m, s, t;
        vector<int> head;
        vector<Edge> edges;
        vector<long long> dis;
        vector<int> inq, cnt, h, pre;
        int maxf = 0, minc = 0;

        MCMF(){
            input();
        }

        void add(int u, int v, int w, int c){
            edges.push_back({u, v, w, c, head[u]});
            head[u] = edges.size() - 1;
        }

        void input() {
            cin >> n >> m >> s >> t;
            head.resize(n + 1, -1); // vertex index start from 1
            edges.resize(2 * m);
            dis.resize(n + 1, LLONG_MAX);
            h.resize(n + 1, LLONG_MAX);
            inq.resize(n + 1);
            cnt.resize(n + 1);
            pre.resize(n + 1);

            int u, v, w, c = 1;
            for(int i = 0; i < 2 * m; i+=2) {
                cin >> u >> v >> w >> c;
                edges[i] = {u, v, w, c, head[u]};
                edges[i+1] = {v, u, 0, -c, head[v]};
                head[u] = i;
                head[v] = i + 1;
            }
        }

        bool spfa() {
            queue<int> q;
            h[s] = 0;
            q.push(s);
            inq[s] = 1;
            while(!q.empty()) {
                auto now = q.front();
                q.pop();
                inq[now] = 0;
                for(auto eg = head[now]; eg >= 0; eg = edges[eg].next) {
                    int to = edges[eg].to, w = edges[eg].w, c = edges[eg].c;
                    if(w > 0 && h[to] > h[now] + c) {
                        h[to] = h[now] + c;
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

        using pii = pair<int, int>;

        bool dijk(){
            auto cmp = [](auto& a, auto& b){ return a.first > b.first; };
            priority_queue<pii, vector<pii>, decltype(cmp)> q(cmp);
            vector<int> visit(n+1, 0);
            fill(dis.begin(), dis.end(), LLONG_MAX);
            dis[s] = 0;
            q.push({0, s});
            while(!q.empty()){
                int u = q.top().second;
                q.pop();
                if(visit[u])
                    continue;
                visit[u] = 1;
                for(int i=head[u]; i>=0; i = edges[i].next){
                    int v = edges[i].to, nc = edges[i].c + h[u] - h[v];
                    if(edges[i].w > 0 && dis[v] > dis[u] + nc){
                        dis[v] = dis[u] + nc;
                        pre[v] = i;
                        q.push({dis[v], v});
                    }
                }
            }
            return dis[t] != LLONG_MAX;
        }

        void run(){
            if(!spfa()) // 求初始势能
                return;
            maxf = minc = 0;
            while(dijk()){
                long long minf = LLONG_MAX;
                for(int i = 1; i <= n; i++) h[i] += dis[i];
                for(int i = t; i != s; i = edges[pre[i]].from) minf = min(minf, edges[pre[i]].w);
                for(int i = t; i != s; i = edges[pre[i]].from) {
                    edges[pre[i]].w -= minf;
                    edges[pre[i] ^ 1].w += minf;
                }
                maxf += minf;
                minc += minf * h[t];
            }
        }
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
