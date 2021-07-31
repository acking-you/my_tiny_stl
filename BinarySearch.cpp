//
// Created by Alone on 2021/7/20.
//

#include "BinarySearch.h"
#include <stdio.h>
//默认构造函数就好
BinarySearch::BinarySearch() {}
//析构函数把内存池中的内存释放
BinarySearch::~BinarySearch() {
    for (int i = 0; i < __node_pool.size(); ++i) {
        delete __node_pool[i];
    }
}
//插入操作
void BinarySearch::insert(int val) {
    TreeNode *node = new TreeNode(val);
    if (this->__node_pool.empty()) {
        __node_pool.emplace_back(node);
        return;
    }
    __node_pool.emplace_back(node);
    this->node_insert(__node_pool[0], node);
}
//与插入操作配套的操作
void BinarySearch::node_insert(TreeNode *root, TreeNode *target) {
    if (target->val > root->val) {
        if (root->right) {
            node_insert(root->right, target);
        } else {
            root->right = target;
        }
    } else {
        if (root->left) {
            node_insert(root->left, target);
        } else {
            root->left = target;
        }
    }
}
//查找操作
bool BinarySearch::count(int val) {
    if (this->__node_pool.empty())
        return false;
    return this->node_check(__node_pool[0], val);
}
//与查找操作配套的操作
bool BinarySearch::node_check(TreeNode *root, int target) {
    while (root) {
        if (target == root->val) {
            return true;
        } else if (target > root->val) {
            root = root->right;
        } else {
            root = root->left;
        }
    }
    return false;
}
//中序打印操作
void BinarySearch::print() {
    if (this->__node_pool.empty())
        return;
    this->inorder_print(__node_pool[0]);
}
//与中序打印配套的操作
void BinarySearch::inorder_print(TreeNode *root) {
    if (!root)
        return;
    inorder_print(root->left);
    printf("%d ", root->val);
    inorder_print(root->right);
}
