//
// Created by Alone on 2021/8/2.
//

#include "LinkMap.h"
//头插法解决
void LinkMap::add(int u, int v, int w) {
    Linklist* t = new Linklist(v,w);
    t->next = head[u]->next;
    head[u]->next = t;
}
Linklist * LinkMap::get_head(int num) {
    return head[num]->next;
}
//析构函数
LinkMap::~LinkMap() {
    for(int i=0;i<head.size();i++){
        Linklist* cur = head[i];
        while (cur){
            Linklist* pre = cur;
            cur = cur->next;
            delete pre;
        }

    }
}