#include <bits/stdc++.h>
#include "pc.h"

using namespace std;

void test() {
    vector<int> data(500005, 0);
    MaxAddSegTree tree(data);
    tree.modify(0, 1, 2);
    tree.modify(1, 3, 2);
    cout << tree.query(1, 3);
}

signed main() {
    test();
    return 0;
}
