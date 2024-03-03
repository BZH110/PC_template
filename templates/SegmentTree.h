//
// Created by Ziheng Bao on 2023/12/9.
//

#ifndef PC_TEMPLATE_SEGMENTTREE_H
#define PC_TEMPLATE_SEGMENTTREE_H

#include <bits/stdc++.h>

namespace pc{
using namespace std;
using ll = long long;

    // mallain max value
    // 局部增加，局部查询最值
    class MaxAddSegTree{
    public:
        vector<ll>& data;
        vector<ll> t, mark;
        MaxAddSegTree(vector<ll>& a):data(a){
            ll n = data.size();
            t.resize(4 * n + 5, 0);
            mark.resize(4 * n + 5, 0);
            build(1, 0, n-1);
        }
        void build(ll o, ll l, ll r){
            if(l == r){
                t[o] = data[l];
                return;
            }
            ll m = (l + r) / 2;
            build(2 * o, l, m);
            build(2 * o + 1, m + 1, r);
            t[o] = max(t[2 * o], t[2 * o + 1]);
        }
        void modify(ll l, ll r, ll dif){
            modify(1, 0, (ll)data.size() - 1, l, r, dif);
        }
        void modify(ll o, ll lo, ll ro,ll l, ll r, ll dif){
            if(lo >= l && ro <= r){
                t[o] += dif;
                mark[o] += dif;
                return;
            }
            if(lo > r || ro < l)
                return;
            push_down(o);
            ll m = (lo + ro) / 2;
            modify(2 * o, lo, m, l, r, dif);
            modify(2 * o + 1, m+1, ro, l, r, dif);
            t[o] = max(t[2*o], t[2*o+1]);
        }
        ll query(ll l, ll r){
            return query(1, 0, (ll)data.size() - 1, l, r);
        }
        ll query(ll o, ll lo, ll ro, ll l, ll r){
            if(lo >= l && ro <= r)
                return t[o];
            if(lo > r || ro < l)
                return LLONG_MIN;
            push_down(o);
            ll m = (lo + ro) / 2;
            return max(query(2 * o, lo, m, l, r), query(2 * o + 1, m+1, ro, l, r));
        }

        void push_down(ll o){
            t[2 * o] += mark[o];
            t[2 * o + 1] += mark[o];
            mark[2 * o] += mark[o];
            mark[2 * o + 1] += mark[o];
            mark[o] = 0;
        }
    };

    // mallain max value
    // 局部修改覆盖，局部查询最值
    class MaxModifySegTree{
    public:
        vector<ll>& data;
        vector<ll> t, mark;
        MaxModifySegTree(vector<ll>& a):data(a){
            ll n = data.size();
            t.resize(4 * n + 5, 0);
            mark.resize(4 * n + 5, LLONG_MIN);
            build(1, 0, n-1);
        }
        void build(ll o, ll l, ll r){
            if(l == r){
                t[o] = data[l];
                return;
            }
            ll m = (l + r) / 2;
            build(2 * o, l, m);
            build(2 * o + 1, m + 1, r);
            t[o] = max(t[2 * o], t[2 * o + 1]);
        }
        void modify(ll l, ll r, ll val){
            modify(1, 0, (ll)data.size() - 1, l, r, val);
        }
        void modify(ll o, ll lo, ll ro, ll l, ll r, ll val){
            if(lo >= l && ro <= r){
                t[o] = val;
                mark[o] = val;
                return;
            }
            if(lo > r || ro < l)
                return;
            push_down(o);
            ll m = (lo + ro) / 2;
            modify(2 * o, lo, m, l, r, val);
            modify(2 * o + 1, m+1, ro, l, r, val);
            t[o] = max(t[2*o], t[2*o+1]);
        }
        ll query(ll l, ll r){
            return query(1, 0, (ll)data.size() - 1, l, r);
        }
        ll query(ll o, ll lo, ll ro, ll l, ll r){
            if(lo >= l && ro <= r)
                return t[o];
            if(lo > r || ro < l)
                return LLONG_MIN;
            push_down(o);
            ll m = (lo + ro) / 2;
            return max(query(2 * o, lo, m, l, r), query(2 * o + 1, m+1, ro, l, r));
        }
        void push_down(ll o){
            if(mark[o] != LLONG_MIN) {
                t[2 * o] = mark[o];
                t[2 * o + 1] = mark[o];
                mark[2 * o] = mark[o];
                mark[2 * o + 1] = mark[o];
            }
        }
    };

    // 局部增加，局部求和
    template<ll MOD = LLONG_MAX>
    class SumSegTree{
    private:
        vector<ll>& data;
        vector<ll> t, mark;
        void build(ll o, ll l, ll r){
            if(l == r){
                t[o] = data[l];
                return;
            }
            ll m = (l + r) / 2;
            build(2 * o, l, m);
            build(2 * o + 1, m + 1, r);
            t[o] = (t[2 * o] + t[2 * o + 1]) % MOD;
        }
    public:
        SumSegTree(vector<ll>& a):data(a) {
            ll n = data.size();
            t.resize(4 * n + 5, 0);
            mark.resize(4 * n + 5, 0);
            build(1, 0, n - 1);
        }
        void modify(ll l, ll r, ll dif){
            modify(1, 0, data.size() - 1, l, r, dif);
        }
        void modify(ll o, ll lo, ll ro, ll l, ll r, ll dif){
            if(lo >= l && ro <= r){
                t[o] += (dif * (ro - lo + 1)) % MOD;
                t[o] %= MOD;
                mark[o] += dif;
                return;
            }
            if(lo > r || ro < l)
                return;
            push_down(o, lo, ro);
            ll m = (lo + ro) / 2;
            modify(2 * o, lo, m, l, r, dif);
            modify(2 * o + 1, m+1, ro, l, r, dif);
            t[o] = (t[2 * o] + t[2 * o + 1]) % MOD;
        }
        ll query(ll l, ll r){
            return query(1, 0, data.size() - 1, l, r);
        }
        ll query(ll o, ll lo, ll ro, ll l, ll r){
            if(lo >= l && ro <= r)
                return t[o];
            if(lo > r || ro < l)
                return 0;
            push_down(o, lo, ro);
            ll m = (lo + ro) / 2;
            return (query(2 * o, lo, m, l, r) + query(2 * o + 1, m+1, ro, l, r)) % MOD;
        }

        void push_down(ll o, ll lo, ll ro){
            ll m = (lo + ro) / 2;
            t[2 * o] += (mark[o] * (m - lo + 1)) % MOD;
            t[2 * o] %= MOD;
            t[2 * o + 1] += (mark[o] * (ro - m)) % MOD;
            t[2 * o + 1] %= MOD;
            mark[2 * o] += mark[o];
            mark[2 * o + 1] += mark[o];
            mark[o] = 0;
        }
    };

    // 单点更新线段树 通用模板
    template <typename T>
    class SegmentTree {
    public:
        using F = function<T(T &, T &)>;
        int n;
        vector<T> dat;
        T e;
        F query_func;
        F update_func;

        SegmentTree(vector<T> a, F query_func, F update_func, T e) : n(a.size()), query_func(query_func), update_func(update_func), e(e) {
            if (n == 0) {
                a.push_back(e);
                n++;
            }
            dat.resize(4 * n + 5);
            init(0, 0, n - 1, a);
        }

        void init(int k, int l, int r, vector<T> &a) {
            if (r == l) {
                dat[k] = a[l];
            } else {
                int lch = 2 * k + 1, rch = 2 * k + 2;
                init(lch, l, (l + r) / 2, a);
                init(rch, (l + r) / 2 + 1, r, a);
                dat[k] = query_func(dat[lch], dat[rch]);
            }
        }

        void update(int k, T a, int v, int l, int r) {
            if (r == l) {
                dat[v] = update_func(dat[v], a);
            } else {
                if (k <= (l + r) / 2)
                    update(k, a, 2 * v + 1, l, (l + r) / 2);
                else {
                    update(k, a, 2 * v + 2, (l + r) / 2 + 1, r);
                }
                dat[v] = query_func(dat[v * 2 + 1], dat[v * 2 + 2]);
            }
        }

        void update(int k, T a) {
            update(k, a, 0, 0, n - 1);
        }

        T query(int a, int b, int k, int l, int r) {
            if (r < a || b < l) {
                return e;
            }
            if (a <= l && r <= b) {
                return dat[k];
            } else {
                T ul = query(a, b, k * 2 + 1, l, (l + r) / 2);
                T ur = query(a, b, k * 2 + 2, (l + r) / 2 + 1, r);
                return query_func(ul, ur);
            }
        }

        T query(int a, int b) {
            return query(a, b, 0, 0, n - 1);
        }

        // maybe useless
        int find(int a, int b, int k, int l, int r, int x) {
            if (dat[k] < x || r < a || b < l) return -1;
            if (l == r) {
                if (dat[k] >= x)
                    return l;
                else
                    return -1;
            }
            int rv = find(a, b, 2 * k + 2, (l + r) / 2 + 1, r, x);
            if (rv != -1) return rv;
            return find(a, b, 2 * k + 1, l, (l + r) / 2, x);
        }
    };
}

#endif //PC_TEMPLATE_SEGMENTTREE_H
