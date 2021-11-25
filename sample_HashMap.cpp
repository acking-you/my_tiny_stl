//
// Created by Alone on 2021/7/20.
//
#include <stdio.h>
#include "HashTable.h"

sample_HashMap::sample_HashMap() {}

sample_HashMap::~sample_HashMap() {
    clear();
}

int sample_HashMap::hash_func(int value) {
    return value % MAX_HASH_TABALE_LEN;
}

void sample_HashMap::insert(int value) {
    int t = this->hash_func(value);
    ListNode *node = new ListNode(value);
    node->next = _head[t].next;
    _head[t].next = node;
}

bool sample_HashMap::count(int value) {
    int t = hash_func(value);
    ListNode *head = _head[t].next;
    while (head) {
        if (head->val == value) {
            return true;
        }
        head = head->next;
    }
    return false;
}

void sample_HashMap::clear() {
    for (int t = 0; t < MAX_HASH_TABALE_LEN; t++) {
        ListNode *cur = _head[t].next;
        while (cur) {
            ListNode *pre = cur;
            cur = cur->next;
            delete pre;
        }
        _head[t].next = nullptr;
    }
}

void sample_HashMap::remove(int value) {
    int t = hash_func(value);
    ListNode *head = &_head[t];
    while (head) {
        ListNode *pre = head;
        head = head->next;
        if (head && head->val == value) {
            pre->next = head->next;
            delete head;
            head = pre;
        }
    }
}

void sample_HashMap::print() {
    for (int i = 0; i < MAX_HASH_TABALE_LEN; i++) {
        printf("[%d]:", i);
        ListNode *head = _head[i].next;
        while (head) {
            printf("->%d", head->val);
            head = head->next;
        }
        printf("\n");
    }

}