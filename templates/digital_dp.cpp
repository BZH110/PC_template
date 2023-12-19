//
// Created by BZH on 2023/7/30.
//
#include <bits/stdc++.h>

using namespace std;

void digital_dp(){
    string limit = "A"; // 数字上限
    int n_status = 1; // 状态数
    vector<vector<int>> mem(limit.size(), vector<int>(n_status, -1)); // 记忆状态，只记录 !is_limit && is_number 的结果，这一部分存在大量重复
    function<int(int, bool, bool, int, string&)> dfs = [&](int index, bool is_limit, bool is_number, int status, string& limit)->int{
        if(index == limit.size()){
            return is_number ? 1: 0;
        }
        if(mem[index][status] != -1)
            return mem[index][status];
        int ret = 0;
        // is_limit 和 is_number不同状态分别加到ret上
        // ret += ...
        return ret;
    };
    int ret = dfs(0, false, true, 0, limit);
}
