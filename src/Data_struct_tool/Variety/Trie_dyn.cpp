//
// Created by Alone on 2021/8/3.
//

#include "Trie_dyn.h"

//每次入新的表需要把它们加入到内存池，方便最后析构函数的清理
void Trie_dyn::insert(string word) {
    Trie *node = pool[0];
    for (auto &&t:word) {
        if (!(node->children[t - 'a'])) {
            node->children[t - 'a'] = new Trie;
            pool.emplace_back(node->children[t - 'a']);
        }
        node = node->children[t - 'a'];
    }
    node->f = true;
}

Trie *Trie_dyn::searchPrefix(const string s) {
    Trie *node = pool[0];
    for (auto &&t:s) {
        if (!(node->children[t - 'a']))
            return nullptr;
        node = node->children[t - 'a'];
    }
    return node;
}

bool Trie_dyn::search(string word) {
    Trie *t = searchPrefix(word);
    return t != nullptr && t->f;
}

bool Trie_dyn::startWith(string prefix) {
    return searchPrefix(prefix) == nullptr ? false : true;
}

Trie_dyn::~Trie_dyn() {
    for (auto t:pool) {
        delete t;
    }
}