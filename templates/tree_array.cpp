//
// Created by BZH on 2023/7/30.
//
#include <bits/stdc++.h>

using namespace std;

void tree_array(){
    auto lowbit = [](int x){return x & (-x);};
    int n;
    vector<int> a(n);
    vector<int> tree(4*n + 5, 0);
    auto modify = [&](int x, int val){
        int dif = val - a[x];
        while(x < tree.size()){
            tree[x] += dif;
            x += lowbit(x);
        }
    };
    auto find = [&](int x){
        int ret = 0;
        while(x){
            ret += tree[x];
            x -= lowbit(x);
        }
        return ret;
    };
    for(int i=0;i<n;i++){
        modify(i, a[i]);
    }
    //
}