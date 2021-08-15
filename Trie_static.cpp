//
// Created by Alone on 2021/8/3.
//
#include "Trie_static.h"
void Trie_static::insert(string word) {
    int p = 0;
    for(auto&&t:word){
        int&& ch = t-'a';
        if(!son[p][ch]){
            son[p][ch] = ++tot;
        }
        p = son[p][ch];
    }
    //标记单词结尾的结点
    isEnd[p] = true;
}
int Trie_static::searchPrifix(const string word) {
    int p = 0;
    for(auto && t:word){
        int&& ch = t-'a';
        if(!son[p][ch])
            return 0;
        p = son[p][ch];
    }
    return p;
}
bool Trie_static::search(string word) {
    int&& t = searchPrifix(word);
    return t&&isEnd[t];
}
bool Trie_static::startWith(string word) {
    return searchPrifix(word);
}