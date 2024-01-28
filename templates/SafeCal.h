//
// Created by Ziheng Bao on 2024/1/28.
//

#ifndef PC_TEMPLATE_SAFECAL_H
#define PC_TEMPLATE_SAFECAL_H

namespace pc{
    using ll = long long;
    template<long long MOD = (int)(1e9 + 7)>
    class N{
    public:
        long long x;
        N(long long _x): x(_x){}
        N operator+(N n){return N((((x + n.x) % MOD) + MOD) % MOD);}
        void operator+=(N n){x = (((x + n.x) % MOD) + MOD) % MOD;}
        N operator-(N n){return N((((x - n.x) % MOD) + MOD) % MOD);}
        void operator-=(N n){x = (((x - n.x) % MOD) + MOD) % MOD;}
        N operator*(N n){return N((((x * n.x) % MOD) + MOD) % MOD);}
        void operator*=(N n){x = (((x * n.x) % MOD) + MOD) % MOD;}
        N operator/(N n){return N((((x * mypow(n.x, MOD - 2, MOD)) % MOD) + MOD) % MOD);}
        void operator/=(N n){x = (((x * mypow(n.x, MOD - 2, MOD)) % MOD) + MOD) % MOD;}

        ll mypow(ll a, ll b, ll mod = LLONG_MAX) {
            if (b == 0)
                return 1;
            if (b % 2 == 0)
                return mypow((a * a) % mod, b / 2, mod);
            return (a * mypow((a * a) % mod, b / 2, mod)) % mod;
        }
    };
}

#endif //PC_TEMPLATE_SAFECAL_H
