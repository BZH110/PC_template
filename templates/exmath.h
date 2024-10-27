//
// Created by BZH on 24-2-16.
//

#ifndef EXMATH_H
#define EXMATH_H

#include <bits/stdc++.h>

namespace pc {
    using ll = long long;

    long long mypow(long long a, long long b, long long mod = LLONG_MAX) {
        a %= mod;
        if (b == 0)
            return 1;
        if (b == 1)
            return a;
        if (b % 2 == 0)
            return mypow((a * a) % mod, b / 2, mod);
        return (a * mypow((a * a) % mod, b / 2, mod)) % mod;
    }

    ll factor(int n, int mod) {
        ll ret = 1;
        for(int i=2;i<=n;i++)
            ret = (ret * i) % mod;
        return ret;
    }

    ll C(int n, int m, int mod = INT_MAX) { // choose m from n
        if(n < m)
            return 0;
        if(2 * m > n)
            return C(n, n-m, mod);
        ll ans = 1, ans2 = 1;
        for(int i=n;i>n-m;i--)
            ans = (ans * (i % mod)) % mod;
        for(int i=1;i<=m;i++)
            ans2 = (ans2 * (i % mod)) % mod;
        return (ans * mypow(ans2, mod-2, mod)) % mod;
    }

    ll A(int n, int m, int mod = INT_MAX) {
        ll ans = 1;
        for(int i=n;i>n-m;i--)
            ans = (ans * (i % mod)) % mod;
        return ans;
    }

    // 将n个不同的小球随机放到m个不同盒子中，且每个盒子都不为空的问题，使用组合数学中的“第二类斯特林数”和“排列数”来解决
    // ref: https://oi-wiki.org/math/combinatorics/stirling/

}

#endif //EXMATH_H
