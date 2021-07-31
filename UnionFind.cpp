//
// Created by Alone on 2021/7/31.
//

#include "UnionFind.h"
UnionFind::UnionFind(int size) {
    root = new int[size];
    rank = new int[size];
    length = size;
    for(int i=0;i<length;i++){
        root[i] = i;
        rank[i] = 1;
    }
}
UnionFind::~UnionFind() {
    delete[] root;
    delete[] rank;
}
int UnionFind::find(int x) {
    if(root[x]==x)
        return x;
    return root[x]=find(root[x]);
}
void UnionFind::merge(int x, int y) {
    int rootX = find(x);
    int rootY = find(y);
    if(rootX!=rootY){
        if(rank[rootX]<rank[rootY]){
            root[rootX] = rootY;
        } else if (rank[rootX]>rank[rootY]){
            root[rootY] = rootX;
        } else{
            root[rootX] = rootY;
            rank[rootY]++;
        }
    }
}
bool UnionFind::isConnected(int x, int y) {
    return find(x)==find(y);
}