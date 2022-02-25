//
// Created by Alone on 2021/10/14.
//

#include "Treap.h"

node *Treap::rotateLeft(node *root) {
    node *son = root->rchild;
    root->rchild = son->lchild;
    son->lchild = root;
    root->update();//记得先更新底下的情况
    son->update();
    return son;
}

node *Treap::rotateRight(node *root) {
    node *son = root->lchild;
    root->lchild = son->rchild;
    son->rchild = root;
    root->update();
    son->update();
    return son;
}

node *Treap::insert(node *root, int val, int &size) {
    if (root == nullptr) {
        ++size;
        return new node(val);
    }
    if (root->val == val) {
        root->cnt++;
        size++;
    } else if (root->val > val) {
        root->lchild = insert(root->lchild, val, size);
        //根据优先级判断是否右旋，因为只可能在左边增加长度，通过维持优先级的大根堆
        if (root->priority < root->lchild->priority) root = rotateRight(root);
    } else if (root->val < val) {
        root->rchild = insert(root->rchild, val, size);
        if (root->priority < root->rchild->priority) root = rotateLeft(root);
    }
    root->update();
    return root;
}

node *Treap::remove(node *root, int val, int &size) {
    if (root == nullptr)return nullptr;//没找到
    if (root->val == val) {
        //含有多个相同值，直接操作cnt即可
        if (root->cnt > 1) {
            root->cnt--;
            --size;
        }
            //分为两类情况：叶子结点情况和非叶子结点情况
        else if (root->lchild != nullptr || root->rchild != nullptr) {
            //只有左子树或者左子树优先级大于右子树情况
            if (root->rchild == nullptr || root->lchild != nullptr && root->lchild->priority > root->rchild->priority) {
                root = rotateRight(root);//右旋后继续追杀
                root->rchild = remove(root->rchild, val, size);
            } else {//只有右子树或者右子树优先级大于左子树的情况
                root = rotateLeft(root);//左旋后继续追杀
                root->lchild = remove(root->lchild, val, size);
            }
        } else {//叶子结点情况，直接删除，然后把
            delete root;
            root = nullptr;
            --size;
        }
    } else if (root->val > val) {
        root->lchild = remove(root->lchild, val, size);
    } else if (root->val < val) {
        root->rchild = remove(root->rchild, val, size);
    }
    if (root)
        root->update();
    return root;
}

int Treap::queryRank(node *root, int val) {//相当于查询有多少个数小于等于val
    int rank = 0;
    while (root != nullptr) {
        if (root->val == val)return rank + getLength(root->lchild) + root->cnt;
        else if (root->val > val)root = root->lchild;
        else rank += getLength(root->lchild) + root->cnt, root = root->rchild;
    }
    return rank + 1;//如果未找到，则在原来的基础上+1
}

int Treap::queryValue(node *root, int rank) {//相当于得到第k大的数：支持重复元素是最骚的！！！
    while (root != nullptr) {
        if (getLength(root->lchild) + root->cnt > rank) {
            if (getLength(root->lchild) + 1 > rank)
                root = root->lchild;
            else
                return root->val;
        } else if (getLength(root->lchild) + root->cnt < rank) {
            rank -= getLength(root->lchild) + root->cnt;
            root = root->rchild;
        } else {//rank与左子树的大小相等的情况
            return root->val;
        }
    }
    return 0;
}

node *Treap::queryPre(node *root, int val) {//一样的道理：如果有左子树，就是左子树中最大的结点，如果没有则是最接近该结点的父节点(应在它的右侧
    node *res = nullptr;
    while (root != nullptr) {
        if (root->val < val)res = root, root = root->rchild;
        else root = root->rchild;
    }
    return res;
}

node *Treap::queryNext(node *root, int val) {//寻找后继
    node *res = nullptr;
    while (root != nullptr) {
        if (root->val > val)res = root, root = root->lchild;
        else root = root->rchild;
    }
    return res;
}

void Treap::inorder_print(node *root) {
    if (root == nullptr)
        return;
    inorder_print(root->lchild);
    printf("%d ", root->val);
    inorder_print(root->rchild);
}

void Treap::destroy(node *root) {
    if (root == nullptr)
        return;
    destroy(root->lchild);
    destroy(root->rchild);
    delete root;
    root = nullptr;
}

inline int Treap::getLength(node *root) {
    if (root == nullptr)
        return 0;
    return root->length;
}
