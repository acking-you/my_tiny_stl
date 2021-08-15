//
// Created by Alone on 2021/8/2.
//注意如果没有边时我们这里都默认为-1，所以进行遍历时把-1当成链表中的null来处理

#include "Tarjan.h"
void Tarjan::add(int u, int v, int w) {
    edge[cnt].to = v;
    edge[cnt].w = w;
    edge[cnt].next = head[u];
    head[u] = cnt++;
}
int * Tarjan::get_head() {
    return head;
}
EDGE * Tarjan::get_edge() {
    return edge;
}
