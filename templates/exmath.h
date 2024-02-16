//
// Created by BZH on 24-2-16.
//

#ifndef EXMATH_H
#define EXMATH_H

#include <bits/stdc++.h>

namespace pc {
    using ll = long long;

    ll mypow(ll a, ll b, ll mod = LLONG_MAX) {
        a %= mod;
        b %= mod;
        if (b == 0)
            return 1;
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

    ll C(int n, int m, int mod) { // choose m from n
        if(2 * m > n)
            return C(n, n-m, mod);
        ll ans = 1, ans2 = 1;
        for(int i=n;i>n-m;i--)
            ans = (ans * i) % mod;
        for(int i=1;i<=m;i++)
            ans2 = (ans2 * i) % mod;
        return (ans * mypow(ans2, mod-2, mod)) % mod;
    }

    ll A(int n, int m, int mod) {
        ll ans = 1;
        for(int i=n;i>n-m;i--)
            ans = (ans * i) % mod;
        return ans;
    }
}

#endif //EXMATH_H
