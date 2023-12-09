//
// Created by Ziheng Bao on 2023/12/9.
//

#ifndef PC_TEMPLATE_SEGMENTTREE_H
#define PC_TEMPLATE_SEGMENTTREE_H

#include <bits/stdc++.h>

namespace pc{

using namespace std;
using ll = long long;
    // maintain max value
    class MaxSegTree{
    public:
        vector<int>& data;
        vector<int> t, mark;
        MaxSegTree(vector<int>& a):data(a){
            int n = data.size();
            t.resize(4 * n + 5, 0);
            mark.resize(4 * n + 5, 0);
            build(1, 0, n-1);
        }
        void build(int o, int l, int r){
            if(l == r){
                t[o] = data[l];
                return;
            }
            int m = (l + r) / 2;
            build(2 * o, l, m);
            build(2 * o + 1, m + 1, r);
            t[o] = max(t[2 * o], t[2 * o + 1]);
        }
        void modify(int l, int r, int dif){
            modify(1, 0, data.size() - 1, l, r, dif);
        }
        void modify(int o, int lo, int ro,int l, int r, int dif){
            if(lo >= l && ro <= r){
                t[o] += dif;
                mark[o] += dif;
                return;
            }
            if(lo > r || ro < l)
                return;
            int m = (lo + ro) / 2;
            modify(2 * o, lo, m, l, r, dif);
            modify(2 * o + 1, m+1, ro, l, r, dif);
            t[o] = max(t[2*o], t[2*o+1]);
        }
        int query(int l, int r){
            return query(1, 0, data.size() - 1, l, r);
        }
        int query(int o, int lo, int ro, int l, int r){
            if(lo >= l && ro <= r)
                return t[o];
            if(lo > r || ro < l)
                return LLONG_MIN;
            int m = (lo + ro) / 2;
            t[2 * o] += mark[o];
            t[2 * o + 1] += mark[o];
            mark[o] = 0;
            return max(query(2 * o, lo, m, l, r), query(2 * o + 1, m+1, ro, l, r));
        }
    };

    template<ll MOD = LLONG_MAX>
    class SumSegTree{
    private:
        vector<int>& data;
        vector<int> t, mark;
        void build(int o, int l, int r){
            if(l == r){
                t[o] = data[l];
                return;
            }
            int m = (l + r) / 2;
            build(2 * o, l, m);
            build(2 * o + 1, m + 1, r);
            t[o] = (t[2 * o] + t[2 * o + 1]) % MOD;
        }
    public:
        SumSegTree(vector<int>& a):data(a) {
            int n = data.size();
            t.resize(4 * n + 5, 0);
            mark.resize(4 * n + 5, 0);
            build(1, 0, n - 1);
        }
        void modify(int l, int r, int dif){
            modify(1, 0, data.size() - 1, l, r, dif);
        }
        void modify(int o, int lo, int ro, int l, int r, int dif){
            if(lo >= l && ro <= r){
                t[o] += (dif * (ro - lo + 1)) % MOD;
                t[o] %= MOD;
                mark[o] += dif;
                return;
            }
            if(lo > r || ro < l)
                return;
            int m = (lo + ro) / 2;
            modify(2 * o, lo, m, l, r, dif);
            modify(2 * o + 1, m+1, ro, l, r, dif);
            t[o] = (t[2 * o] + t[2 * o + 1]) % MOD;
        }
        int query(int l, int r){
            return query(1, 0, data.size() - 1, l, r);
        }
        int query(int o, int lo, int ro, int l, int r){
            if(lo >= l && ro <= r)
                return t[o];
            if(lo > r || ro < l)
                return 0;
            int m = (lo + ro) / 2;
            t[2 * o] += (mark[o] * (m - lo + 1)) % MOD;
            t[2 * o] %= MOD;
            t[2 * o + 1] += (mark[o] * (ro - m)) % MOD;
            t[2 * o + 1] %= MOD;
            mark[o] = 0;
            return (query(2 * o, lo, m, l, r) + query(2 * o + 1, m+1, ro, l, r)) % MOD;
        }
    };

}

#endif //PC_TEMPLATE_SEGMENTTREE_H
