//
// Created by Alone on 2021/7/20.
//

#include "BinarySearch.h"
#include <stdio.h>

//默认构造函数就好
BinarySearch::BinarySearch() : head(nullptr) {}

BinarySearch::BinarySearch(int val) : head(new TreeNode(val)) {}

//析构函数把内存池中的内存释放
BinarySearch::~BinarySearch() {
    destroy(head);
}

//插入操作
void BinarySearch::insert(int val) {
    head = node_insert(head, val);
}

//与插入操作配套的操作
TreeNode *BinarySearch::node_insert(TreeNode *root, int val) {
    if (root == nullptr)
        return new TreeNode(val);
    if (val > root->val) {
        root->right = node_insert(root->right, val);
    } else {
        root->left = node_insert(root->left, val);
    }
    return root;
}

//查找操作
bool BinarySearch::count(int val) {
    return this->node_check(head, val);
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
    this->inorder_print(head);
}

//与中序打印配套的操作
void BinarySearch::inorder_print(TreeNode *root) {
    if (!root)
        return;
    inorder_print(root->left);
    printf("%d ", root->val);
    inorder_print(root->right);
}

void BinarySearch::destroy(TreeNode *node) {
    if (node == nullptr)
        return;
    destroy(node->left);
    destroy(node->right);
    delete node;
    node = nullptr;
}

