//
// Created by Alone on 2021/8/2.
//

#ifndef MY_TINY_STL_LINKMAP_H
#define MY_TINY_STL_LINKMAP_H

#include <vector>

struct Linklist {
    int node;
    int weight;
    Linklist *next;

    Linklist() : node(0), weight(0), next(nullptr) {}

    Linklist(int node, int w) : node(node), weight(w), next(nullptr) {}
};

class LinkMap {
public:
    LinkMap(int node_sum) {
        head.resize(node_sum);
        for (int i = 0; i < node_sum; i++) {
            head[i] = new Linklist;
        }
    }

    ~LinkMap();

    void add(int u, int v, int w);

    Linklist *get_head(int num);

private:
    std::vector<Linklist *> head;
};


#endif //MY_TINY_STL_LINKMAP_H
