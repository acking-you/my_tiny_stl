//
// Created by Alone on 2021/7/20.
//
#ifndef UNTITLED24_HASHTABLE_H
#define UNTITLED24_HASHTABLE_H
#define MAX_HASH_TABALE_LEN 10103

struct ListNode {
    int val;
    ListNode *next;

    ListNode(int v) : val(v), next(nullptr) {}

    ListNode() : val(0), next(nullptr) {}
};

class sample_HashMap {
public:
    sample_HashMap();

    ~sample_HashMap();

    void insert(int value);

    bool count(int value);

    void remove(int value);

    void clear();

    void print();

private:
    //用数组索引代表哈希函数的返回值，而每个元素值代表一个表头,没必要定义成链表指针省的还得进行初始化
    ListNode _head[MAX_HASH_TABALE_LEN];

    int hash_func(int value);
};


#endif //UNTITLED24_HASHTABLE_H
