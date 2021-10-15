//
// Created by Alone on 2021/10/12.
//
#include <algorithm>
#include <cstdio>
#include <cassert>

#ifndef MY_TINY_STL_AVLTREE_H
#define MY_TINY_STL_AVLTREE_H
namespace L_B__ {
    struct node {
        int val;
        int depth;
        node *lchild;
        node *rchild;

        node() : val(0), lchild(nullptr), rchild(nullptr) {}

        node(int x) : val(x), lchild(nullptr), rchild(nullptr) {}
    };

    class AVLTree {
        /*date part*/
        node *head;
        int length;
    public:
        /*construct and destruct part*/
        AVLTree() : head(nullptr), length(0) {}

        AVLTree(int x) : head(new node(x)), length(1) {}

        ~AVLTree() {
            destroy(head);
        }

    public:
        /*iterator part*/
        class iterator {//封装迭代器：内部类--只能调用外部类的静态函数
            node *head;
            node *root;
        public:
            iterator(node *head, node *root) : head(head), root(root) {}

            iterator &operator++();

            bool operator==(const iterator &x);

            bool operator!=(const iterator &x);

            iterator operator++(int);

            iterator &operator--();

            iterator operator--(int);

            int operator*();
        };

    private:
        /*static member function*/
        /*Rotate Part*/
        static node *rotateRight(node *root);

        static node *rotateLeft(node *root);

        static node *rotateLeftRight(node *root);

        static node *rotateRightLeft(node *root);

        /*Destruct*/
        static void destroy(node *root);

        /*Getter*/
        static node *getNext(node *root, node *p);

        static node *getPre(node *root, node *p);

        static node *getMinNode(node *root);

        static node *getMaxNode(node *root);

        static int get_depth(node *root);

        static void update_depth(node *root);

        /*Insert&Remove*/
        static node *Insert(int x, node *root, int &size);

        static node *remove(int x, node *root, int &size);

        /*print_order*/
        static void inorder(node *root);

    public:
        /*public interface*/
        /*clear&empty*/
        void clear();

        bool isEmpty();

        /*find*/
        bool find(int x);

        /*insert&remove*/
        void insert(int x);

        void remove(int x);

        /*size*/
        int size();

        /*begin&end*/
        iterator begin();

        iterator end();

        /*print*/
        void inorder_print();
    };
}


#endif //MY_TINY_STL_AVLTREE_H
