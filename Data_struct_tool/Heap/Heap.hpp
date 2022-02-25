//
// Created by Alone on 2021/10/2.
//

#ifndef MY_TINY_STL_HEAP_HPP
#define MY_TINY_STL_HEAP_HPP

#include <iostream>
#include <algorithm>
#include <stdexcept>
namespace L_B__ {
    template<typename T=int>//用于默认排序的仿函数，默认为大顶堆
    class cmp {
    public:
        bool operator()(T &a, T &b) {
            return a < b;
        }
    };

//@模板类的实现
    template<typename _T=int, typename _CMP = cmp<_T>>
    class Heap {
        //私有成员
        _T *nums;
        size_t length;
        size_t capacity;
    public://@静态成员函数，对外对内都能实现功能
        template<typename T>
        static void sift_down(T &nums, size_t start, size_t len, _CMP cmp) {//最小堆还是最大堆由cmp决定
            int end = len;
            int parent = start;
            int child = parent * 2 + 1;
            while (child < end) {
                if (child + 1 < end && cmp(nums[child], nums[child + 1]))
                    child++;
                if (!cmp(nums[parent], nums[child])) {
                    break;
                } else {
                    std::swap(nums[parent], nums[child]);
                    parent = child;
                    child = parent * 2 + 1;
                }
            }
        }

        template<typename T>
        static void sift_up(T &nums, size_t start, _CMP cmp) {//最小堆还是最大堆由cmp决定
            int end = 0;
            int child = start;
            int parent = (child - 1) / 2;
            while (child > end) {
                if (!cmp(nums[parent], nums[child])) {
                    break;
                } else {
                    std::swap(nums[parent], nums[child]);
                    child = parent;
                    parent = (child - 1) / 2;
                }
            }
        }

        template<typename T>
        static void heapify(T &nums, size_t len) {//用于对数组进行堆化
            for (int i = len - 1; i >= 0; i--) {
                sift_down<T>(nums, i, len, _CMP());
            }
        }

        template<typename T>
        static void print(T &nums, size_t length) {//专为打印原始数组
            for (int i = 0; i < length; i++) {
                std::cout << nums[i] << ' ';
            }
        }

    public://@基本的内部成员函数
        Heap() : length(0), capacity(1) {//暂时没有对构造函数拓展的打算
            nums = new _T[capacity];
        }

        ~Heap() {
            delete[]nums;
        }

        void push(_T val) {
            if (length >= capacity) {//两倍两倍的扩容
                _T *t = nums;
                capacity *= 2;
                nums = new _T[capacity];
                std::copy(t, t + length, nums);
                delete[] t;
            }
            nums[length] = val;
            sift_up(nums, length, _CMP());
            length++;
        }

        void pop() {
            if (length == 0)
                throw std::range_error("from pop :The Heap is empty!");
            length--;
            std::swap(nums[0], nums[length]);//实际上pop操作就相当于堆排的一次过程
            sift_down(nums, 0, length, _CMP());
        }

        _T top() {
            if(length==0){
                throw std::range_error("form top :The Heap is empty!");
            }
            return nums[0];
        }

        void print() {//内部print方便测试
            print(nums, length);
        }
    };
}

#endif //MY_TINY_STL_HEAP_HPP
