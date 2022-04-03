//
// Created by Alone on 2022-3-24.
//

#ifndef _VECTOR_H_
#define _VECTOR_H_
#include <utility>

namespace util{
    template<class point_t,class cmp_t>
    void _qsort(point_t begin,point_t end){
        if(begin>=end)return;

        static cmp_t cmp;

        size_t cmp_index = (((unsigned long long )end - (unsigned long long )begin + 1) / sizeof(*begin)) / 2;
        point_t p_begin = begin;
        point_t p_end = end;
        auto cmp_v = *(p_begin + cmp_index);

        while (p_begin <= p_end) {
            while (cmp(*p_begin,cmp_v))p_begin++;
            while (!cmp(*p_end,cmp_v)&&(*p_end != cmp_v))p_end--;
            if(p_begin<=p_end){
                using std::swap;
                swap(*p_begin,*p_end);
                p_begin++;
                p_end--;
            }
        }

        _qsort<point_t,cmp_t>(begin,p_end);
        _qsort<point_t,cmp_t>(p_begin,end);
    }

    template<class PointType,class CMP = std::less<>>
    void insertSort(PointType begin,PointType end){
        static CMP cmp;
        if(begin+1>=end)return;
        PointType cur_p = begin+1,tmp_p;
        while (cur_p < end){
            tmp_p = cur_p;
            auto tmp_v = *cur_p;
            while(cmp(tmp_v, *(tmp_p - 1)) && tmp_p > begin){
                *tmp_p = *(tmp_p - 1);
                tmp_p--;
            }
            *tmp_p = tmp_v;
            cur_p++;
        }
    }
}



template <typename T>
class Vector {
public:
    using size_t = unsigned int;
    using initializer_list = std::initializer_list<T>;
    using value_t = T;
    using point_t = T*;
    using reference_t = T&;

    class iterator{
    public:
        using value_t = T;
        using point_t = T*;
        using reference_t = T&;
        explicit iterator(point_t point):m_data(point){}
        point_t base()noexcept{
            return m_data;
        }

        iterator& operator++(){
            ++m_data;
            return *this;
        }
        iterator operator+(int n){
            return iterator{m_data+n};
        }
        iterator operator-(int n){
            return iterator{m_data-n};
        }

        unsigned long long operator+(iterator const &p){
            return (unsigned long long )m_data + (unsigned long long )p.m_data;
        }
        unsigned long long operator-(iterator const& p){
            return (unsigned long long )m_data - (unsigned long long)p.m_data;
        }

        iterator operator++(int ){
            iterator ret_val = *this;
            ++(*this);
            return ret_val;
        }
        bool operator!=(iterator const& obj) const {
            return obj.m_data != this->m_data;
        }
        bool operator==(iterator const& obj) const {
            return m_data==obj.m_data;
        }
        reference_t operator*(){
            return *m_data;
        }
    private:
        point_t m_data;
    };
    Vector(initializer_list args):Vector(){
        args.size();
        for (auto &&item: args) {
            PushBack(item);
        }
    }
    Vector(){ ReAlloc(2); }
    ~Vector() {
        Clear();
        ::operator delete(m_Data, m_Capacity * sizeof(T));
    }

    void PushBack(const T& value) {
        // check the space
        if (m_Size >= m_Capacity){
            ReAlloc(m_Size <<1);
        }

        // push the value back and update the size
        //TODO 注意有些数据是必须调用构造函数后，才能正常赋值
        new (&m_Data[m_Size++]) T(value);
    }

    void PushBack(T&& value) {
        // check the space
        if (m_Size >= m_Capacity){
            ReAlloc(m_Size <<1);
        }


        // push the value back and update the size
        //TODO 注意有些数据是必须调用构造函数后，才能正常赋值
        new (&m_Data[m_Size++]) T(std::forward<T>(value));
    }

    template<typename... Args>
    T& EmplaceBack(Args&&... args) {
        // check the space
        if (m_Size >= m_Capacity){
            ReAlloc(m_Size <<1 );
        }

        // Placement new
        new (&m_Data[m_Size]) T(std::forward<Args>(args)...);
        return m_Data[m_Size++];
    }

    void PopBack() {
        if (m_Size > 0) {
            --m_Size;
            m_Data[m_Size].~T();
        }
    }

    void Clear() {
        for (int i = 0; i < m_Size; ++i)
            m_Data[i].~T();
        m_Size = 0;
    }

    T& operator[](size_t index) { return m_Data[index]; }
    const T& operator[](size_t index) const { return m_Data[index]; }
    iterator begin(){
        return iterator{m_Data};
    }
    iterator end(){
        return iterator{m_Data+m_Size};
    }
    [[nodiscard]] size_t Size() const { return m_Size; }

    void sort()noexcept{
        if(m_Size<100){
            util::insertSort(begin().base(),end().base());
            return;
        }
        sort(begin(),end());
    }

    template<class IterType,class CMP = std::less<int>>
    static void sort(IterType begin,IterType end){
        if(begin+1==end)
            return;
        point_t cbegin = begin.base();
        point_t cend = end.base()-1;
        CMP cmp;
        util::_qsort<typename IterType::point_t,CMP>(cbegin,cend);
    }

private:
    void ReAlloc(size_t newCapacity) {
        // allocate space for new block
        T* newBlock = (T*)::operator new(sizeof(T)*newCapacity);
        auto p_Size = m_Size;
        // ensure no overflow
        if (newCapacity < p_Size)
            p_Size = newCapacity;

        // move all the elements to the new block
        for (int i = 0; i < p_Size; ++i)
            new(&newBlock[i]) T(std::move(m_Data[i]));

        // delete the old space and update old members
        Clear();
        ::operator delete(m_Data, m_Capacity * sizeof(T));
        m_Data = newBlock;
        m_Capacity = newCapacity;
        m_Size = p_Size;
    }

private:
    T* m_Data = nullptr;

    size_t m_Size = 0;
    size_t m_Capacity = 0;

};







#endif  // !_VECTOR_H_
