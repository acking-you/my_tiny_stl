//
// Created by Alone on 2021/8/3.
//
//静态字典树(前缀树)用二维数组来实现，第一维度表示结点，第二维度表示当前结点的表表指针。

#ifndef MY_TINY_STL_TRIE_STATIC_H
#define MY_TINY_STL_TRIE_STATIC_H
#include <cstring>
#include <string>
#define maxn 10000
using namespace std;
class Trie_static {
private:
    int tot;
    bool isEnd[maxn];
    int son[maxn][26];
    int searchPrifix(string word);
public:
    Trie_static(){
        tot = 0;
        memset(isEnd,0,sizeof(isEnd));
        memset(son,0,sizeof(son));
    }
    void insert(string word);
    bool search(string word);
    bool startWith(string word);
};


#endif //MY_TINY_STL_TRIE_STATIC_H
