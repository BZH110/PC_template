#include <bits/stdc++.h>
#include "pc.h"

using namespace std;

int main() {
    Primes<100> p;
    for(auto i:p.p){
        cout << i << ' ';
    }
    return 0;
}
