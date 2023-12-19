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

}

#endif //PC_TEMPLATE_SEGMENTTREE_H
