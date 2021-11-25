//
// Created by L_B__ on 2021/11/25.
//
/*
 * 有关说明：完全使用的java1.7的那套实现方法
 * 而由于暂时还没有实现迭代器，所以无法对外部开放遍历方法。
 * 实际上实现迭代器也不难，就是通过实现一个方法来构造一个内部的迭代器类
 * 设计一个迭代器类，在C++里面一般是一个内部封装类，然后实现next方法即可（实际表现为重载运算符）
 * 但不过很明显这里如果这样设计迭代器，会产生较大的额外消耗，所以暂不设计
 * */
#include <functional>
#include <utility>
#include <cassert>

#ifndef MY_TINY_STL_UNORDERED_MAP_H
#define MY_TINY_STL_UNORDERED_MAP_H
namespace L_B__ {
    template<typename K, typename V, typename H = std::hash<K>>
    class unordered_map {
/*类型声明*/
    private:
        typedef K key_t;
        typedef V val_t;
        typedef H hash_t;   //对应的哈希模板类型
    public:
        struct node {//单个节点
            key_t key;
            val_t val;
            node *next;

            node() : key(0), val(0), next(nullptr) {}

            node(key_t key, val_t val) : key(key), val(val), next(nullptr) {}
        };

        const float factor = 0.75f;//装载因子
/*数据定义*/
    public:
        size_t cnt;             //已经插入的键值对数目
        size_t capacity;         //当前最大容量
        node **map;              //一条哈希链的首地址

/*构造函数实现*/
    public:
        /*default construct*/
        unordered_map() : cnt(0), capacity(64), map(nullptr)//默认cap长度设置为16
        {
            map = new node *[capacity];
            for (int i = 0; i < capacity; i++) {
                map[i] = nullptr;
            }
        }

        /*copy construct*/
        unordered_map(unordered_map &src) : cnt(src.cnt), capacity(src.capacity), map(nullptr) {
            assert(capacity > 0);
            map = new node *[capacity];
            copy_map(map, src.map);//委托实现深拷贝
        }

        /*move construct*/
        unordered_map(unordered_map &&src) : cnt(src.cnt), capacity(src.capacity), map(src.map) {
            assert(capacity > 0 && map != nullptr);
            //已经成功进行内存转移，接下来只需要把原src的map赋值为nullptr便可防止调用析构函数销毁内存
            src.map = nullptr;
        }

        /*destruct*/
        ~unordered_map() {
            destroy();
        }

/*所有的对外功能实现*/
    public:
        void put(key_t key, val_t val) {
            if (cnt >= factor * capacity)resize();
            putVal(key, val);
        }

        void insert(node *src) {
            assert(src != nullptr);//外界必须已经分配内存
            size_t index = getIndex(src->key);
            if (map[index] == nullptr) {
                src->next = nullptr;
                map[index] = src;
            } else {
                src->next = map[index];
                map[index] = src;
            }
            cnt++;
        }

        void insert(std::pair<key_t, val_t> src) {//通过外界传入pair实现键值对传递
            put(src.first, src.second);
        }

        val_t &get(key_t key) {//当你调用get的时候就必须存在，否则会被断言
            val_t *ret = getVal(key);
            assert(ret != nullptr);
            return *ret;
        }

        bool count(key_t key) {
            return getVal(key) != nullptr;
        }

        void clear() {
            if (cnt == 0)
                return;
            assert(map != nullptr);
            for (int i = 0; i < capacity; i++) {
                if (map[i] != nullptr)
                    del_nodes(map[i]);
                map[i] = nullptr;
            }
            cnt = 0;//清空哈希表就是重置里面的数据
        }

        size_t &size() {
            return cnt;
        }
/*重载运算符更好操作*/
    public:
        val_t &operator[](key_t key) {
            val_t *val = getVal(key);
            if (val == nullptr)//按照STL的平时使用习惯，如果不存在key，则创建一片空间存储对应的0键值对
                put(key, val_t(0));
            else return *val;
            return get(key);
        }

        //接受左值的赋值运算符
        unordered_map &operator=(unordered_map &src) {
            assert(src.map != nullptr && src.capacity > 0);
            destroy();
            capacity = src.capacity;
            cnt = src.cnt;
            map = new node *[capacity];
            copy_map(map, src.map);
            return *this;
        }

        //接受右值的赋值运算符
        unordered_map &operator=(unordered_map &&src) {
            destroy();
            map = src.map;
            cnt = src.cnt;
            capacity = src.capacity;

            src.map = nullptr;
            return *this;
        }

/*不需要具体对象的函数*/
    public:
        static void del_nodes(node *src) {//释放单条链
            assert(src != nullptr);
            node *pre;
            node *cur = src;
            while (cur != nullptr) {
                pre = cur;
                cur = cur->next;
                delete pre;
            }
        }


/*一些不对外开放的内部委托函数*/
    private:
        val_t *getVal(key_t key) {//通用getval函数
            size_t index = getIndex(key);
            node *p = map[index];
            while (p != nullptr) {
                if (p->key == key)
                    return &(p->val);
                p = p->next;
            }
            return nullptr;
        }

        size_t getIndex(key_t key) {
            hash_t to_hash;
            size_t code = to_hash(key);//用对应的哈希仿函数得出hashcode
            code = code ^ (code >> 16);//扰动函数
            return code & (capacity - 1);//子掩码方式得出下标
        }

        void putVal(key_t key, key_t val) {
            size_t index = getIndex(key);
            node *tmp = map[index];
            if (tmp == nullptr) {//当前位置为空
                map[index] = new node(key, val);
                cnt++;
                return;
            }
            while (tmp != nullptr) {
                if (tmp->key == key) {//已经存在key，对val进行覆盖
                    tmp->val = val;
                    return;
                }
                tmp = tmp->next;
            }
            //如果这条链不存在对应的key，就直接头插
            node *p = new node(key, val);
            p->next = map[index];
            map[index] = p;
            cnt++;
        }

        void resize() {//注意每次resize需要rehash
            capacity <<= 1;//扩容两倍
            node **tmp = map;
            map = new node *[capacity];
            std::fill(map, map + capacity, nullptr);//C++14里面指针无法初始化为0，需要为nullptr
            rehash(tmp);
            delete[]tmp;
        }

        void rehash(node **preTable) {
            cnt = 0; //由于insert会重新把size计数的
            assert(preTable != nullptr);
            size_t preSize = capacity >> 1;
            for (size_t i = 0; i < preSize; ++i) {
                if (preTable[i] != nullptr) {
                    node *preNode;
                    node *curNode = preTable[i];
                    while (curNode != nullptr) {
                        preNode = curNode;
                        curNode = curNode->next;
                        insert(preNode);
                    }
                }
            }
        }

        void destroy() {
            if (map == nullptr)//曾经已经被清理过
                return;
            for (size_t i = 0; i < capacity; i++) {
                if (map[i] != nullptr)
                    del_nodes(map[i]);
                map[i] = nullptr;
            }
            delete[] map;
            map = nullptr;
        }

        void copy_map(node **_dest, node **_src) {
            assert(_dest != nullptr && _src != nullptr);
            for (size_t i = 0; i < capacity; i++) {
                _dest[i] = nullptr;
                if (_src[i] != nullptr) {
                    node *head = _src[i];
                    _dest[i] = new node(head->key, head->val);
                    node *p = _dest[i];
                    while (head != nullptr) {
                        head = head->next;
                        if (head != nullptr) {
                            p->next = new node(head->key, head->val);
                            p = p->next;
                        }
                    }
                }
            }
        }
    };
}


#endif //MY_TINY_STL_UNORDERED_MAP_H
