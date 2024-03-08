//
// Created by Ziheng Bao on 2023/12/9.
//

#ifndef PC_TEMPLATE_PRIME_H
#define PC_TEMPLATE_PRIME_H

#include <bits/stdc++.h>
namespace pc {
    using namespace std;
    using ll = long long;

    template<int LIMIT>
    class Primes{
    private:
        vector<bool> flag;
    public:
        vector<int> p;
        Primes(){
            flag.resize(LIMIT + 1, true);
            flag[0] = flag[1] = false;
            for(int i=2;i<=LIMIT;i++){
                if(flag[i])
                    p.push_back(i);
                for(int j=0;j<p.size();j++){
                    if(p[j] * i > LIMIT)
                        break;
                    flag[p[j] * i] = false;
                    if(i % p[j] == 0)
                        break;
                }
            }
        }
    };
}

#endif //PC_TEMPLATE_PRIME_H
