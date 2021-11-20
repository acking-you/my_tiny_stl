//
// Created by Alone on 2021/7/20.
//

#ifndef BINARYSEARCH_H
#define BINARYSEARCH_H
#include <queue>
struct TreeNode {
    TreeNode *left;
    TreeNode *right;
    int val;

    TreeNode(int x) : left(nullptr), right(nullptr), val(x) {}
};

class BinarySearch {
public:
    BinarySearch();

    BinarySearch(int val);

    ~BinarySearch();

    void insert(int val);

    bool count(int val);

    void print();
private://内存池,方便管理动态分配的内存
    TreeNode *head;

    void destroy(TreeNode *root);

    TreeNode *node_insert(TreeNode *root, int val);

    bool node_check(TreeNode *root, int target);
    void lever_print(TreeNode* root);
    void inorder_print(TreeNode *root);
};


#endif //UNTITLED27_BINARYSEARCH_H
