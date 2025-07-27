//
// Created by Bao Ziheng on 2025/7/27.
//

#ifndef PC_TEMPLATE_LINEARBASIS_H
#define PC_TEMPLATE_LINEARBASIS_H

#include <vector>

using namespace std;

class LinearBasis {
public:
    vector<int> base;

    LinearBasis(const vector<int>& a) {
        int n = a.size();
        base.resize(61);
        for(int i=0;i<n;i++){
            int now = a[i];
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

    int GetHigh() {
        int ans = 0;
        for(int j=60;j>=0;j--){
            if((ans & (1LL << j)) == 0) {
                ans ^= base[j];
            }
        }
        return ans;
    }
};

#endif //PC_TEMPLATE_LINEARBASIS_H
