//
// Created by Alone on 2021/8/2.
//
//默认以0为起始结点的链式向前星。
#ifndef MY_TINY_STL_TARJAN_H
#define MY_TINY_STL_TARJAN_H
struct EDGE {
    int to;//边的指向结点
    int w;//边的权重
    int next;//属于同一条链的下一个结点
};

class Tarjan {
public:
    Tarjan(int len, int n) : maxl(len), sum_node(n), cnt(0) {
        edge = new EDGE[maxl];
        head = new int[sum_node];
        //初始化head表示还没有任何边的信息
        for (int i = 0; i < sum_node; i++)
            head[i] = -1;
    }

    ~Tarjan() {
        delete[]edge;
        delete[]head;
    }

    //添加边的方法
    void add(int u, int v, int w);

    //得到表的方法，得到表后遍历和链表的遍历是差不多的
    EDGE *get_edge();

    int *get_head();

private:
    int cnt;
    int maxl;
    int sum_node;
    EDGE *edge;
    int *head;
};


#endif //MY_TINY_STL_TARJAN_H
