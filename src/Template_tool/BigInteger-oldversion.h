//
// Created by Alone on 2021/10/7.
//

#ifndef MY_TINY_STL_BIGINTEGER_OLDVERSION_H
#define MY_TINY_STL_BIGINTEGER_OLDVERSION_H

#include <algorithm>
#include <iostream>
#include <cstring>
namespace L_B__ {
    class BigInteger {
        bool f;
        char *nums;
        int length;
        int capacity;
    public:
        //构造函数
        BigInteger() : length(0), capacity(1), f(false) { //缺省构造函数
            nums = new char[capacity];
        }

        BigInteger(const char *n);

        BigInteger(const BigInteger &a);

        BigInteger(BigInteger &&a);

        ~BigInteger() { //析构函数
            delete[] nums;
        }

    public:
        //静态函数
        static void Swap(BigInteger &a, BigInteger &b);

        static bool compare(const BigInteger &a, const BigInteger &b);

        bool isEqual(BigInteger &a, BigInteger &b);

        static BigInteger add(BigInteger &a, BigInteger &b);

        static BigInteger minus(BigInteger &a, BigInteger &b);

    public:
        //运算符重载
        char &operator[](int i) {
            return nums[i];
        }

        BigInteger &operator=(BigInteger &&a) { //Swap&Copy方式实现右值赋值重载
            Swap(*this, a);
            return *this;
        }

        BigInteger &operator=(const BigInteger &a);

        bool operator<(const BigInteger &a) const;

        BigInteger operator+(BigInteger &a);

        BigInteger operator-(BigInteger &a);

    public:
        //对象的基本成员函数
        int getCap() {
            return capacity;
        }

        int getLength() {
            return length;
        }

        bool isNegative() {
            return f;
        }

        bool isEmpty() {
            return length == 0;
        }

        void reverse();

        void push_back(char x);

        void print();

        void read();
    };

}
#endif //MY_TINY_STL_BIGINTEGER_OLDVERSION_H
