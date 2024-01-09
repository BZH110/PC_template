//
// Created by Ziheng Bao on 2023/12/19.
//

#ifndef PC_TEMPLATE_TRIE_H
#define PC_TEMPLATE_TRIE_H

#include <bits/stdc++.h>

namespace pc{
    using namespace std;

    template<int size>
    struct Node{
        Node* m[size];
        int end = 0;
        Node(){
            for(int i=0;i<size;i++)
                m[i] = nullptr;
        }
    };

    template<int size, char base>
    class Trie{
    public:
        Node<size>* root;
        Trie() {
            root = new Node<size>();
        }
        void add(string s){
            auto now = root;
            for(auto c:s){
                if(!now->m[c - base])
                    now->m[c] = new Node<size>();
                now = now->m[c];
            }
            now->end++;
        }
    };
}

#endif //PC_TEMPLATE_TRIE_H
