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
        N(long long _x){
            x = (_x % MOD + MOD) % MOD;
        }
        N operator+(N n){return N((((x + n.x) % MOD) + MOD) % MOD);}
        void operator+=(N n){x = (((x + n.x) % MOD) + MOD) % MOD;}
        N operator-(N n){return N((((x - n.x) % MOD) + MOD) % MOD);}
        void operator-=(N n){x = (((x - n.x) % MOD) + MOD) % MOD;}
        N operator*(N n){return N((((x * n.x) % MOD) + MOD) % MOD);}
        void operator*=(N n){x = (((x * n.x) % MOD) + MOD) % MOD;}
        N operator/(N n){return N((((x * mypow(n.x, MOD - 2, MOD)) % MOD) + MOD) % MOD);}
        void operator/=(N n){x = (((x * mypow(n.x, MOD - 2, MOD)) % MOD) + MOD) % MOD;}

        N operator+(long long n){return *this + N(n);}
        void operator+=(long long n){*this += N(n);}
        N operator-(long long n){return *this - N(n);}
        void operator-=(long long n){*this -= N(n);}
        N operator*(long long n){return *this * N(n);}
        void operator*=(long long n){*this *= N(n);}
        N operator/(long long n){return *this / N(n);}
        void operator/=(long long n){*this /= N(n);}

        friend N operator+(long long ln, N rn){return N(ln) + rn;}
        friend N operator-(long long ln, N rn){return N(ln) - rn;}
        friend N operator*(long long ln, N rn){return N(ln) * rn;}
        friend N operator/(long long ln, N rn){return N(ln) / rn;}

#ifndef int
        N operator+(int n){return *this + N(n);}
        void operator+=(int n){*this += N(n);}
        N operator-(int n){return *this - N(n);}
        void operator-=(int n){*this -= N(n);}
        N operator*(int n){return *this * N(n);}
        void operator*=(int n){*this *= N(n);}
        N operator/(int n){return *this / N(n);}
        void operator/=(int n){*this /= N(n);}

        friend N operator+(int ln, N rn){return N(ln) + rn;}
        friend N operator-(int ln, N rn){return N(ln) - rn;}
        friend N operator*(int ln, N rn){return N(ln) * rn;}
        friend N operator/(int ln, N rn){return N(ln) / rn;}
#endif

        bool operator==(N n) {return this->x == n.x;}
        bool operator==(long long n) {return this->x == n;}

        friend ostream& operator<< (ostream& out, const N n){
            out << n.x;
            return out;
        }

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
    };
}

#endif //PC_TEMPLATE_SAFECAL_H
