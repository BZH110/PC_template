//
// Created by Bao Ziheng on 2025/7/27.
//

#ifndef PC_TEMPLATE_LINEARBASIS_H
#define PC_TEMPLATE_LINEARBASIS_H

#include <vector>

using namespace std;

class LinearBasis {
public:
    int base[61]{0};

    LinearBasis(const vector<long long>& a) {
        int n = a.size();
        for(int i=0;i<n;i++){
            auto now = a[i];
            for(int j=60;j>=0;j--){
                if((1LL << j) > now)
                    continue;
                if(base[j] != 0) {
                    now ^= base[j];
                    continue;
                }
                base[j] = now;
                break;
            }
        }
    }

    long long GetHigh() {
        long long ans = 0;
        for(int j=60;j>=0;j--){
            if((ans & (1LL << j)) == 0) {
                ans ^= base[j];
            }
        }
        return ans;
    }
};

#endif //PC_TEMPLATE_LINEARBASIS_H
