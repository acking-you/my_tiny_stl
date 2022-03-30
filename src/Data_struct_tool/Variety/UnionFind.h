//
// Created by Alone on 2021/7/31.
//

#ifndef MY_TINY_STL_UNIONFIND_H
#define MY_TINY_STL_UNIONFIND_H


class UnionFind {
private:
    int *root;
    int *rank;
    int length;
public:
    UnionFind(int size);

    ~UnionFind();

    int find(int x);

    void merge(int x, int y);

    bool isConnected(int x, int y);
};


#endif //MY_TINY_STL_UNIONFIND_H
