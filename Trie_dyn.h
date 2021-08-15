//
// Created by Alone on 2021/8/3.
//

#ifndef MY_TINY_STL_TRIE_DYN_H
#define MY_TINY_STL_TRIE_DYN_H
#include <cstring>
#include <string>
#include <vector>
using namespace std;
struct Trie{
    bool f;
    Trie* children[26];
    Trie():f(false){
        memset(children,0,sizeof(children));
    }
};
class Trie_dyn {
private:
    vector<Trie*>pool;
    Trie* searchPrefix(const string s);
public:
    Trie_dyn():pool(1){
        pool[0] = new Trie;
    }
    ~Trie_dyn();
    void insert(string word);
    bool search(string word);
    bool startWith(string prefix);
};


#endif //MY_TINY_STL_TRIE_DYN_H
