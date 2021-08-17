//
// Created by Alone on 2021/7/20.
//
#include <vector>

#ifndef BINARYSEARCH_H
#define BINARYSEARCH_H

struct TreeNode {
    TreeNode *left;
    TreeNode *right;
    int val;

    TreeNode(int x) : left(nullptr), right(nullptr), val(x) {}
};

class BinarySearch {
public:
    BinarySearch();

    ~BinarySearch();

    void insert(int val);

    bool count(int val);

    void print();

private://内存池,方便管理动态分配的内存
    std::vector<TreeNode *> __node_pool;

    void node_insert(TreeNode *root, TreeNode *target);

    bool node_check(TreeNode *root, int target);

    void inorder_print(TreeNode *root);
};


#endif //UNTITLED27_BINARYSEARCH_H
