#include <bits/stdc++.h>
#include "pc.h"

using namespace std;

void test() {
    N n(1);
    cout << n << endl;
}

class MyType {
public:
    vector<int> a;

    MyType(int n) {
        a.resize(n, 0);
    }

    // 重载 '<' 运算符来定义对象之间的小于关系
    bool operator<(const MyType& other) const {
        for(int i=0;i<a.size();i++){
            if(a[i] < other.a[i])
                return true;
        }
        return false;
    }

    bool operator==(const MyType& other) const {
        for(int i=0;i<a.size();i++){
            if(a[i] != other.a[i])
                return false;
        }
        return true;
    }
};

signed main() {
    for(int i=0;i<1e5;i++){
        cout << i * 10 << " ";
    }
    cout << endl;
    for(int i=0;i<1e5;i++){
        cout << i + 2 << " ";
    }
    cout << endl;
    return 0;
}
