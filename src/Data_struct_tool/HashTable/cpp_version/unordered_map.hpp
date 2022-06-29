//
// Created by L_B__ on 2021/11/25.
//
/*
 * 有关说明：参考Redis内的渐进式rehash实现。
 * 迭代器部分设计借鉴Java。
 * 本实现最新更新的版本为2022-6-29更新
 * */

//实现简单dict->渐进式多线程rehash的dict
//注意！：以下以C++20的标准实现（在函数原型中用到了auto&&

#ifndef MY_TINY_STL_UNORDERED_MAP_H
#define MY_TINY_STL_UNORDERED_MAP_H

#include<utility>
#include<iostream>
#include<thread>
#include<functional>
#include<cassert>

template<class K,class V>
class UnorderedMap;
template<class k, class v>
class Dict {
public:
    enum {
        SMALL_LOAD = 1,
        MID_LOAD = 5,
        BIG_LOAD = 10,
    };

    struct dictNode {
        std::pair<k, v> value;
        dictNode *next{};
    };
    using key_t = k;
    using value_t = v;
    using node_t = dictNode;

    friend class UnorderedMap<k,v>;  //友元类
    friend inline void swap(Dict& a,Dict& b){
        using std::swap;
        swap(a.m_table,b.m_table);
        swap(a.m_size,b.m_size);
        swap(a.m_used,b.m_used);
    }

    Dict() = default;

    explicit Dict(size_t capacity){
        init_data(capacity);
    }

    ~Dict(){
        destroy();
    }

    bool Insert(node_t* src){
        assert(src!= nullptr);
        if(push_node(src)==nullptr)return false;
        m_used++;
        return true;
    }

    node_t* Insert(std::pair<key_t,value_t>&&src){
        auto* node = new node_t();
        node->value = src;
        if(push_node(node) == nullptr){
            delete node;
            return nullptr;
        }
        m_used++;
        return node;
    }

    value_t& operator[](key_t && key){ //支持下标操作，如果不存在则创建默认零值
        auto* node = do_search(std::forward<key_t>(key));
        if(node == nullptr){
            auto* new_node = new node_t();
            new_node->value.first = key;
            push_node(new_node);
            m_used++;
            return new_node->value.second;
        }
        return node->value.second;
    }

    bool Update(std::pair<key_t,value_t>&& obj){
        auto* node = do_search(obj.first);
        if(node){
            node->value.second = obj.second;
            return true;
        }
        return false;
    }

    bool Delete(key_t&& key){
        auto node = poll_node(std::forward<key_t>(key));
        if(node){
            delete node;
            m_used--;
            return true;
        }
        return false;
    }

    value_t Search(std::pair<key_t,value_t>&& obj){
        auto* node = do_search(obj.first);
        if(node){
            return node->value.second;
        }
        return value_t(); //返回对应类型的零值
    }

    bool Empty(){
        return m_used == 0;
    }

    size_t Size(){
        return m_used;
    }

    void Clear(){
        clear_table();
    }

private:
    node_t* push_node(node_t* node){   //返回成功操作的
        auto index = get_index(std::forward<key_t>(node->value.first));//获取位置
        auto* dst = do_search(std::forward<key_t>(node->value.first)); //根据key查找是否先前存在

        if(dst != nullptr){//已经存在
            return nullptr;
        }

        auto& head = m_table[index]; //注意用引用，为了修改head
        node->next = head;
        head = node;
        return node;
    }

    node_t* poll_node(key_t&& key){   //返回成功操作的
        auto index = get_index(std::forward<key_t>(key));//获取位置
        node_t*& head = m_table[index];
        if(head == nullptr) return nullptr; //不存在
        node_t* cur_node = head;
        node_t* pre_node = nullptr;
        if(cur_node&&cur_node->value.first!=key){ //如果cur_node不是目标则继续寻找
            while(cur_node){
                pre_node = cur_node;    //过程中记录前一个节点
                cur_node = cur_node->next;
                if(cur_node->value.first==key)
                    break;
            }
        }
        //开始删除操作：更新链表结构，并返回需要删除的指针
        if(!pre_node){   //若目标元素是头部
            head = head->next;
            return cur_node;
        }
        pre_node->next = cur_node->next;
        cur_node->next = nullptr;
        return cur_node;
    }

    node_t* do_search(auto&& key){ //找不到返回空，找到了返回找到的节点
        node_t* node = m_table[get_index(std::forward<key_t>(key))];
        while(node){
            if(node->value.first == key){
                return node;
            }
            node = node->next;
        }
        return node;
    }

    void del_nodelist(node_t* head){
        auto* cur_node = head;
        while(cur_node){
            auto* next_node = cur_node->next;
            delete cur_node;
            cur_node = next_node;
        }
    }

    void clear_table(){
        for(int i = m_size-1;i>=0;--i){
            if(m_table[i]){
                del_nodelist(m_table[i]);
                m_table[i] = nullptr;
            }
        }
        m_used = 0;
    }

    void destroy(){
        clear_table();
        delete[] m_table;
        m_table = nullptr;
    }

    size_t get_index(key_t&& key){
        std::hash<key_t> h;
        auto code = h(std::forward<key_t>(key));
        code = code ^ (code >> 16);//扰动函数
        return code&(m_size-1);
    }

    double get_loadFactor(){
        return (double)m_used/m_size;
    }

    inline size_t find_size(size_t need_size){
        size_t i = 2;
        do{
            i <<= 1;
        }while(i<need_size);
        return i;
    }

    void init_data(size_t cap){
        if((cap&(cap-1))!=0){ //如果不为2的幂，则找出大于它的最小二的幂
            cap = find_size(cap);
        }
        m_size = cap;
        m_table = new node_t*[cap]{};
        m_used = 0;
    }

    void _realloc(size_t cap){
        if(m_table){//销毁之前分配过的内存
            destroy();
        }
        init_data(cap);
    }

private:
    node_t **m_table{};
    size_t m_size{};
    size_t m_used{};
};

template<class K,class V>
class UnorderedMap{
public:
    using key_t = K;
    using value_t = V;
    using node_t = typename Dict<K,V>::node_t;
    enum {
        SPAN = 150  //每次渐进式的跨度
    };

    class iterator{ //用于迭代所有元素的容器
    private:
        explicit iterator(UnorderedMap<K,V>* src,std::pair<int,size_t> curOp,node_t* curNode):
                m_src(src),m_curOperate(std::move(curOp)),m_curNode(curNode){}
    public:
        friend class UnorderedMap<K,V>;
        bool hasNext(){
            m_curNode = _getNext();
            return m_curNode!=nullptr;
        }
        std::pair<key_t,value_t> next(){
            if(m_curNode)
                return m_curNode->value;
            throw std::runtime_error("next value nullptr");
        }
        void debug(){
            std::cout<<"bucket size:"<<m_src->m_dict.m_size<<" ele size:"<<m_src->m_dict.m_used<<
                     " idx:"<<m_src->m_rehashidx<<"\n";
        }
    private:
        node_t* _getNext(){
            //1.m_curNode还有下个节点
            //2.根据操作信息对表进行操作
            if(m_curNode&&m_curNode->next)
                return m_curNode->next;

            size_t index = m_curOperate.second;
            //操作第一张表
            if(m_curOperate.first==1){
                index++;
                while(index<m_src->m_dict.m_size){
                    if(m_src->m_dict.m_table[index]){
                        m_curOperate.second = index;
                        return m_src->m_dict.m_table[index];
                    }
                    index++;
                }

                //若前面没查到，继续查询表2
                index = 0;
                while(index<m_src->m_rehash_dict.m_size){
                    if(m_src->m_rehash_dict.m_table[index]){
                        m_curOperate.first = 2;
                        m_curOperate.second = index;
                        return m_src->m_dict.m_table[index];
                    }
                    index++;
                }

                //表2也没有，则没有东西可查，返回null
                return nullptr;
            }

            //继续操作第二张表
            if (m_curOperate.first==2){
                index++;
                while(index<m_src->m_rehash_dict.m_size){
                    if(m_src->m_rehash_dict.m_table[index]){
                        m_curOperate.second = index;
                        return m_src->m_rehash_dict.m_table[index];
                    }
                    index++;
                }
                return nullptr;
            }

            return nullptr;
        }

    private:
        UnorderedMap<K,V>* m_src;
        std::pair<int,size_t> m_curOperate;
        node_t* m_curNode;  //用于缓存
    };

    explicit UnorderedMap(size_t cap = 16):m_dict(cap){
    }

    //以下利用auto&&万能引用+完美转发自动生成两套代码


    bool Insert(std::pair<key_t,value_t>&& src){
        return _insert(src) != nullptr;
    }

    bool Insert(std::pair<key_t,value_t>& src){
        return _insert(src) != nullptr;
    }

    bool Erase(key_t&& key){
        return _erase(std::forward<key_t>(key));
    }

    bool Erase(key_t& key){
        return _erase(std::forward<key_t>(key));
    }

    bool Exist(key_t&& key) {
        return _exist(std::forward<key_t>(key)) != nullptr;
    }

    bool Exist(key_t& key) {
        return _exist(std::forward<key_t>(key)) != nullptr;
    }

    value_t & operator[](key_t && key){
        return _get_value(std::forward<key_t>(key));
    }

    value_t & operator[](key_t & key){
        return _get_value(std::forward<key_t>(key));
    }


    size_t Size(){
        return _size();
    }

    iterator Iterator(){
        return iterator(this,{1,-1},nullptr);
    }

private:

    node_t* _insert(auto && src){
        //1.是否正在进行rehash扩容
        //2.判断是否需要rehash扩容

        node_t* ret;
        //正在进行rehash，则还需要进行rehash，且插入到第二张哈希表
        if(m_rehashidx>=0){
            ret = m_rehash_dict.Insert(std::forward<std::pair<key_t,value_t>>(src));
            rehash_round();
            return ret;
        }

        auto load_factor =  m_dict.get_loadFactor();
        if(load_factor>=(float)Dict<K,V>::MID_LOAD){
            m_rehashidx = 0;
            if(rehash_round()){
                return m_dict.Insert(std::forward<std::pair<key_t,value_t>>(src));
            }
            return m_rehash_dict.Insert(std::forward<std::pair<key_t,value_t>>(src));
        }

        return m_dict.Insert(std::forward<std::pair<key_t,value_t>>(src));
    }

    bool _erase(auto&& key){

        if(m_rehashidx>=0){
            bool r1 = m_dict.Delete(std::forward<key_t>(key));
            bool r2 = false;
            if(!r1)
                r2 = m_rehash_dict.Delete(std::forward<key_t>(key));
            rehash_round();
            return r2 || r1;
        }

        return m_dict.Delete(std::forward<key_t>(key));
    }


    node_t* _exist(auto && key){
        if(m_rehashidx>=0){
            auto node = m_dict.do_search(std::forward<key_t>(key));
            if(node==nullptr)
                node = m_rehash_dict.do_search(std::forward<key_t>(key));
            rehash_round();
            return node;
        }

        return m_dict.do_search(std::forward<key_t>(key));
    }


    value_t & _get_value(auto&& key){
        node_t* src_node = _exist(std::forward<key_t>(key));
        if(src_node){
            return src_node->value.second;
        }
        node_t* p = _insert(std::make_pair(key,value_t()));
        if(p)
            return p->value.second;
        throw std::runtime_error("push dict node error");
    }


    size_t _size(){
        if(m_rehash_dict.Empty()){
            return m_dict.m_used;
        }
        return m_dict.m_used+m_rehash_dict.m_used;
    }


    //根据跨度继续往下执行哈希操作
    bool rehash_round(){
        //若首次rehash需要申请内存
        if(m_rehashidx == 0){
            m_rehash_dict._realloc(m_dict.m_used*2);
        }

        int i = 0;
        auto& dict_size = m_dict.m_size;
        auto& src = m_dict.m_table;
        auto& used_size = m_dict.m_used;

        while(i<SPAN&&m_rehashidx+i<dict_size){
            node_t* node = src[m_rehashidx+i];
            while(node){
                auto* next_node = node->next;
                m_rehash_dict.Insert(node);
                used_size--;
                node = next_node;
            }
            src[m_rehashidx+i] = nullptr;
            i++;
        }

        //rehash执行完成
        if(m_rehashidx+i==dict_size){
            m_rehashidx = -1;
            delete src;
            src = nullptr;  //恢复初始状态
            dict_size = 0;
            used_size = 0;
            swap(m_dict,m_rehash_dict);
            return true;
        }
        //rehash还未执行完
        m_rehashidx += i;
        return false;
    }

private:
    Dict<K,V> m_dict;
    Dict<K,V> m_rehash_dict;
    int m_rehashidx = -1;
};


#endif //MY_TINY_STL_UNORDERED_MAP_H
