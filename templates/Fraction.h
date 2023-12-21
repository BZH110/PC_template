//
// Created by Ziheng Bao on 2023/12/22.
//

#ifndef PC_TEMPLATE_FRACTION_H
#define PC_TEMPLATE_FRACTION_H

long long gcd(long long x, long long y){
    if(x == 0)
        return y;
    return gcd(y % x, x);
}

template <long long MOD = LLONG_MAX>
class Fraction{
public:
    long long x, y; // x / y
    Fraction(long long _x, long long _y){
        long long tx = _x % MOD, ty = _y % MOD;
        long long g = gcd(tx, ty);
        x = tx / g;
        y = ty / g;
    }
    Fraction operator+(Fraction r){
        int d = r.y * y / gcd(r.y, y);
        return Fraction((d / y * x + d / r.y * r.x) % MOD, d % MOD);
    }
    Fraction operator-(Fraction r){
        int d = r.y * y / gcd(r.y, y);
        return Fraction(((d / y * x - d / r.y * r.x) % MOD + MOD) % MOD, d % MOD);
    }
    Fraction operator*(Fraction r){
        long long tx = (x * r.x) % MOD, ty = (y * r.y) % MOD;
        long long g = gcd(tx, ty);
        return Fraction(tx / g, ty / g);
    }
    Fraction operator/(Fraction r){
        long long tx = (x * r.y) % MOD, ty = (r.x * y) % MOD;
        long long g = gcd(tx, ty);
        return Fraction(tx / g, ty / g);
    }
};

template <long long MOD = LLONG_MAX>
std::ostream& operator<<(std::ostream& out, Fraction<MOD> f){
    out << f.x << "/" << f.y;
    return out;
}

#endif //PC_TEMPLATE_FRACTION_H
