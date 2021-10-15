//
// Created by Alone on 2021/10/14.
//

#ifndef MY_TINY_STL_TREAP_H
#define MY_TINY_STL_TREAP_H

#include <cstdio>
#include <cstdlib>
#include <ctime>

struct node {
    int val, priority, length, cnt;
    node *lchild;
    node *rchild;

    node() : val(0), length(1), cnt(1), lchild(nullptr), rchild(nullptr) {
        srand((unsigned) time(NULL));//记得重新设定种子
        priority = rand();
    }

    node(int val) : val(val), length(1), cnt(1), lchild(nullptr), rchild(nullptr) {
        srand((unsigned) time(NULL));
        priority = rand();
    }

    void update() {
        length = cnt;
        if (lchild != nullptr)length += lchild->length;
        if (rchild != nullptr)length += rchild->length;
    }
};

class Treap {
    node *head;
    int length;
public:
    /*construct&destruct*/
    Treap() : head(nullptr), length(0) {}

    Treap(int val) : head(new node(val)), length(1) {}
    ~Treap(){
        destroy(head);
    }

public://内部类设计迭代器
    class iterator {
        node *head;
        node *root;
    public:
        /*迭代器部分*/
        iterator(node *head, node *root) : head(head), root(root) {}

        iterator &operator++() {
            root = queryNext(head, root->val);
            return *this;
        }

        iterator operator++(int) {
            iterator t = *this;
            root = queryNext(head, root->val);
            return t;
        }

        iterator &operator--() {
            root = queryPre(head, root->val);
            return *this;
        }

        iterator operator--(int) {
            iterator t = *this;
            root = queryPre(head, root->val);
            return t;
        }

        int operator*() {
            return root->val;
        }

        bool operator!=(const iterator &t) {
            return t.root != root;
        }
    };

private:
    /*static function*/
    /*rotate*/
    static node *rotateLeft(node *root);

    static node *rotateRight(node *root);

    /*insert&remove*/
    static node *insert(node *root, int val, int &size);

    static node *remove(node *root, int val, int &size);

    /*query rank&value*/
    static int getLength(node *root);

    static int queryRank(node *root, int val);//快速查询val的排名
    static int queryValue(node *root, int rank);//快速查询排名为rank的数
    /*query pre&next*/
    static node *queryPre(node *root, int val);

    static node *queryNext(node *root, int val);

    static void inorder_print(node *root);

    static void destroy(node *root);

public:
    /*public function*/
    /*insert&remove*/
    void insert(int val) {
        head = insert(head, val, length);
    }

    void remove(int val) {
        head = remove(head, val, length);
    }

    int size() {
        return length;
    }

    bool isEmpty() {
        return length == 0;
    }

    /*query rank&value*/
    int queryRank(int val) {
        return queryRank(head, val);
    }

    int queryValue(int rank) {
        return queryValue(head, rank);
    }

    void inorder_print() {
        inorder_print(head);
    }

    /*begin&end*/
    iterator begin() {
        node *t = head;
        while (t->lchild != nullptr) {
            t = t->lchild;
        }
        return iterator(head, t);
    }

    iterator end() {
        return iterator(head, nullptr);
    }
};


#endif //MY_TINY_STL_TREAP_H
