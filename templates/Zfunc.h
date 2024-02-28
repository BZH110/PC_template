//
// Created by Ziheng Bao on 2024/2/28.
//

#ifndef PC_TEMPLATE_ZFUNC_H
#define PC_TEMPLATE_ZFUNC_H

namespace pc{
    using namespace std;

    class Zfunc{
    public:
        string s;
        vector<int> z;
        Zfunc(string _s):s(_s){
            z.resize(s.size());
            cal();
        }

        void cal(){
            int n = s.size();
            z[0] = n;
            int r = 0, l = 0;
            for(int i=1;i<n;i++){
                if(i <= r)
                    z[i] = min(z[i-l], r - i + 1);
                while(i + z[i] < n && s[i + z[i]] == s[z[i]])
                    z[i]++;
                if(i + z[i] - 1 > r){
                    r = i + z[i] - 1;
                    l = i;
                }
            }
        }
    };
}

#endif //PC_TEMPLATE_ZFUNC_H
