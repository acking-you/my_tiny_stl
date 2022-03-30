//
// Created by L_B__ on 2021/11/24.
//
//底层的表长都用2的次方，然后-1后可以得到低位掩码
//该设计理念急于java1.7的源代码，本来是想基于1.8的实现，
// 因为1.8巧妙太多，比如对rehash尽量能不动的就不动，再比如对于链比较长的结构直接转红黑树。可惜能力不能及
/**
 * 简单说明：static修饰的函数为单文件的中间委托功能函数，不对外公开
 * 简单的功能函数介绍：
 * init()得到一个默认表长的哈希表
 * put()插入键值，内部自动进行内存的申请
 * get()得到key对应的val的地址，若不存在该键值对返回NULL
 * insert()外界已经分配好node的内存和key&val对，进行哈希运算后直接插入即可
 * destroy()把整个哈希表牵扯的所有内存释放
 * **/
#include <assert.h>
#include <stdlib.h>

#ifndef MY_TINY_STL_HASHMAP_C_H
#define MY_TINY_STL_HASHMAP_C_H
#define DEFAULT_CAPACITY 64 //初始的表长
#define DEFAULT_FACTOR 0.75f //初始的装载因子
/*类型定义 和 装载因子初始化*/
typedef int key_t;
typedef int val_t;
static const float factor = DEFAULT_FACTOR; //装载因子
typedef struct node {//每个哈希表的键值对
    key_t key;
    val_t val;
    struct node *next;
} Node;
typedef struct {
    size_t size;       //记录已经存下的键值对数目
    size_t capacity;   //记录表长
    Node **buckets; //桶子：用于记录的哈希桶，桶子中每个元素是Node*
} HashMap;


/*函数的声明*/
HashMap *init();

void put(HashMap *, key_t, val_t);

void insert(HashMap *, Node *);                           //直接把已经分配好的内存插入哈希表
static void putVal(key_t, val_t, Node **, size_t *, size_t); //这个是put的委托函数,用于直接更新桶子，并更新HashMap的size
static inline size_t getHashcode(key_t);              //得到key对应的扰动函数
static inline size_t strHashcode(char *);               //得到字符串的哈希值，用的java的31为底的算法，这个哈希值再经过扰动函数
static inline size_t getIndex(key_t, size_t);           //通过桶的大小和key映射位置，算是包含了关键的哈希函数：由于C不支持泛型也就无法针对不同类型作出不同的哈希了，我这里默认key为int
static void resize(HashMap *);                          //如果插入的元素过多，*2进行重新哈希分配
static void rehash(HashMap *, Node **);                   //重新设置长度则需要重新哈希一些key的位置
val_t *get(HashMap *, key_t);                            //得到key对应的val
static void del_nodes(Node *);                          //把单个链表销毁
void destroy(HashMap *);                                //把哈希表的内存销毁



/*函数实现*/
HashMap *init() {    //初始化得到一个哈希表
    HashMap *ret = (HashMap *) malloc(sizeof(HashMap));
    assert(ret != NULL);
    ret->size = 0;
    ret->capacity = DEFAULT_CAPACITY;
    ret->buckets = (Node **) calloc(DEFAULT_CAPACITY, sizeof(Node *));
    assert(ret->buckets != NULL);
    return ret;
}

void insert(HashMap *map, Node *node) {
    assert(map != NULL && node != NULL);
    size_t index = getIndex(node->key, map->capacity);
    if (map->buckets[index] == NULL) {
        node->next = NULL;
        map->buckets[index] = node;
    } else {
        node->next = map->buckets[index];
        map->buckets[index] = node;
    }
}

void put(HashMap *map, key_t key, val_t val) {
    assert(map != NULL);
    //判断是否需要扩容
    if (map->size >= map->capacity * factor) resize(map);
    putVal(key, val, map->buckets, &map->size, map->capacity);
}

static inline size_t strHashcode(char *key) {
    size_t hash = 0;
    size_t index = 0;
    while (key[index] != '\0') {
        hash = hash * 31 + key[index++];
    }
    return hash;
}

static inline size_t getHashcode(key_t key) {
    return key ^ (key >> 16);//这是32位数的扰动函数
}

static inline size_t getIndex(key_t key, size_t bucket_size) {//由于bucketsize一定是2的次方，所以size-1和key相与得到的就是下标
    return getHashcode(key) & (bucket_size - 1);
}

static void putVal(key_t key, val_t val, Node **buckets, size_t *returnSize, size_t bucketSize) {
    //获取位置
    size_t index = getIndex(key, bucketSize);
    Node *node = buckets[index];
    if (node == NULL) {//插入位置为空
        node = (Node *) malloc(sizeof(Node));
        assert(node != NULL);
        node->val = val;
        node->key = key;
        node->next = NULL;
        buckets[index] = node;
        (*returnSize)++;    //哈希表内的元素增加
        return;
    }
    //插入位置不为空，说明发生冲突，使用链地址法，遍历链表
    while (node != NULL) {
        //如果key相同就覆盖
        if (node->key == key) {
            node->val = val;
            return;
        }
        node = node->next;
    }
    //当前的key不在链表中，则插入链表头部
    Node *newNode = (Node *) malloc(sizeof(Node));
    assert(newNode != NULL);
    newNode->next = buckets[index];
    buckets[index] = newNode;
    (*returnSize)++; //哈希表内元素增加
}


static void resize(HashMap *map) {
    map->capacity <<= 1;            //扩大两倍容量，相当于左移一位
    Node **tmp = map->buckets;     //存下之前的内存地址
    map->buckets = (Node **) calloc(map->capacity, sizeof(Node *)); //重新分配
    assert(map->buckets != NULL);
    rehash(map, tmp);//重新哈希处理
    free(tmp);                                          //释放之前的内存
}


static void rehash(HashMap *map, Node **preTable) {//采取java1.7的方式进行rehash也就是最简单直接的直接重新哈希插入
    size_t preCap = map->capacity / 2; //改变前的有效区域
    for (size_t i = 0; i < preCap; i++) {
        if (preTable[i] != NULL) {//判断对应的key是否需要重新换位置,如果对最新掩码多出来的1敏感则需要rehash
            Node *preNode;
            Node *curNode = preTable[i];
            while (curNode != NULL) {
                preNode = curNode;
                curNode = curNode->next;
                insert(map, preNode);
            }
        }
    }
}


val_t *get(HashMap *map, key_t key) {//前面的写好后，那么get就很好写了
    int index = getIndex(key, map->capacity);
    Node *node = map->buckets[index];
    while (node != NULL) {
        if (node->key == key) {
            return &(node->val);
        }
        node = node->next;
    }
    return NULL;//没找到返回NULL指针
}

static void del_nodes(Node *head) {//删除单条链表
    Node *pre;
    Node *cur = head;
    while (cur != NULL) {
        pre = cur;
        cur = cur->next;
        free(pre);
    }
}

void destroy(HashMap *map) {//销毁整个哈希表
    size_t sz = map->capacity;
    Node **tmp = map->buckets;
    for (size_t i = 0; i < sz; i++) {
        if (tmp[i] != NULL)
            del_nodes(tmp[i]);
    }
    free(tmp);
    free(map);
}

#endif //MY_TINY_STL_HASHMAP_C_H