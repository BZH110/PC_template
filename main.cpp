#include <bits/stdc++.h>
#include "pc.h"

using namespace std;
#define int long long

void test() {
    vector<int> a{1, 2, 3, 4, 5};
    SumSegTree t(a);
    t.modify(0, 3, 2);
    t.modify(2, 3, 4);
    cout << t.query(0, 3);
}

signed main() {
    test();
    return 0;
}
