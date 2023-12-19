//
// Created by BZH on 2023/7/30.
//
#include <bits/stdc++.h>

namespace pc {
    using namespace std;
    using ll = long long;

// 输入的索引x都是原数组下标
    template<ll MOD = LLONG_MAX>
    class FenwickTree {
    private:
        vector<int> &a;
        vector<int> t;

        void build() {
            for (int i = 0; i < a.size(); i++)
                set(i, a[i]);
        }

    public:
        FenwickTree(vector<int> _a) : a(_a) {
            t.resize(a.size() + 1, 0);
            build();
        }

        int lowbit(int x) {
            return x & (-x);
        }

        int get(int x) {
            x++; // avoid x == -1
            int ret = 0;
            while (x > 0) {
                ret += t[x];
                ret %= MOD;
                x -= lowbit(x);
            }
            return ret;
        }

        void set(int x, int dif) {
            x++; // avoid x == -1
            while (x < t.size()) {
                t[x] += dif;
                t[x] %= MOD;
                x += lowbit(x);
            }
        }
    };

    void tree_array() {
        auto lowbit = [](int x) { return x & (-x); };
        int n;
        vector<int> a(n);
        vector<int> tree(4 * n + 5, 0);
        auto modify = [&](int x, int val) {
            int dif = val - a[x];
            while (x < tree.size()) {
                tree[x] += dif;
                x += lowbit(x);
            }
        };
        auto find = [&](int x) {
            int ret = 0;
            while (x) {
                ret += tree[x];
                x -= lowbit(x);
            }
            return ret;
        };
        for (int i = 0; i < n; i++) {
            modify(i, a[i]);
        }
        //
    }
}