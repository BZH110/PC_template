//
// Created by BZH on 2024/1/4.
//

#ifndef BIT_H
#define BIT_H

namespace pc {

    // 获取最低的一个bit
    int lowbit(int x) { return x & (-x); }

    // 枚举 n 元集合所有 k 元子集
    void GospersHack(int k, int n) {
        int cur = (1 << k) - 1;
        int limit = (1 << n);
        while (cur < limit)
        {
            // do something
            int lb = cur & -cur;
            int r = cur + lb;
            cur = ((r ^ cur) >> __builtin_ctz(lb) + 2) | r;
            // 或：cur = (((r ^ cur) >> 2) / lb) | r;
        }
    }

    // 枚举 x 的二进制子集
    void EnumSubset(int x) {
        while(x) {
            // do something
            x = x & (x - 1);
        }
    }
}

#endif //BIT_H
