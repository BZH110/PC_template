//
// Created by Ziheng Bao on 2023/12/19.
//

#ifndef PC_TEMPLATE_TRIE_H
#define PC_TEMPLATE_TRIE_H

#include <bits/stdc++.h>

namespace pc{
    using namespace std;

    struct Node{
        unordered_map<char, Node*> m;
        int end = 0;
    };

    class Trie{
    public:
        Node* root;
        Trie(){
            root = new Node();
        }
        void add(string s){
            auto now = root;
            for(auto c:s){
                if(!now->m.count(c))
                    now->m[c] = new Node();
                now = now->m[c];
            }
            now->end++;
        }
    };
}

#endif //PC_TEMPLATE_TRIE_H
