//
// Created by BZH on 2024/5/27.
//

#ifndef CP_TEMPLATE_HASH_H
#define CP_TEMPLATE_HASH_H

#include<bits/stdc++.h>

namespace pc{
    using namespace std;

    void roll_hash(){
        auto rng = mt19937_64(random_device{}());
        int mod = 1e9 + 7, base = 135 + rng() % 114514;
        // do your hash here
    }
}

#endif //CP_TEMPLATE_HASH_H
