#include <bits/stdc++.h>
#include "pc.h"

using namespace std;

void test() {
    vvi g{{1,2}, {0, 3, 5}, {0, 4}, {1}, {2}, {1}};
    LCA l(g);
    cout << l.get(1, 5);
}

signed main() {
    test();
    return 0;
}
