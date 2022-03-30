//
// Created by Alone on 2021/10/7.
//

#include "BigInteger.h"
using namespace L_B__;
//@构造函数实现
BigInteger::BigInteger(const char *n) : length(strlen(n)), f(false) { //用于初始值的构造函数
    int start = 0;
    if (n[0] == '-') {
        f = true;
        start++;
    }
    while (start < length && n[start] == '0')start++;
    capacity = length * 10;
    nums = new char[capacity];
    std::copy(n + start, n + length, nums);
    length = length - start;
}

BigInteger::BigInteger(const BigInteger &a) {  //拷贝构造函数
    capacity = a.capacity;
    length = a.length;
    f = a.f;
    nums = new char[capacity];
    std::copy(a.nums, a.nums + length, nums);
}

BigInteger::BigInteger(BigInteger &&a) : length(0) { //移动构造函数
    *this = a;
}

//@静态函数实现
void BigInteger::Swap(BigInteger &a, BigInteger &b) {
    std::swap(a.length, b.length);
    std::swap(a.capacity, b.capacity);
    std::swap(a.f, b.f);
    std::swap(a.nums, b.nums);
}

bool BigInteger::compare(const BigInteger &a, const BigInteger &b) {
    int n1 = a.length;
    int n2 = b.length;
    if (n1 != n2)return n1 > n2; //返回a和b哪个大，true则位a大
    int i = 0;
    while (i < n1 && a.nums[i] == b.nums[i])i++; //a b一样长的情况下，比较两个的值
    if (i == n1)
        return false;
    return a.nums[i] > b.nums[i];
}

bool BigInteger::isEqual(BigInteger &a, BigInteger &b) {
    if (a.f != b.f || (a.length != b.length))return false;
    int i = 0;
    while (i < a.length && a.nums[i] == b.nums[i])i++;
    return i == a.length && a.f == b.f;
}

BigInteger BigInteger::add(BigInteger &a, BigInteger &b) {
    a.reverse();//尾端对齐
    b.reverse();
    BigInteger t;
    int up = 0;
    int len = a.length > b.length ? a.length : b.length;
    for (int i = 0; i < len; i++) {
        int ta = i < a.length ? a[i] - '0' : 0;
        int tb = i < b.length ? b[i] - '0' : 0;
        int base = ta + tb + up;
        t.push_back(base % 10 + '0');
        up = base / 10;
    }
    if (up)
        t.push_back(up + '0');
    t.reverse();//返回原位
    a.reverse();
    b.reverse();
    return t;
}

BigInteger BigInteger::minus(BigInteger &a, BigInteger &b) {
    a.reverse();
    b.reverse();
    BigInteger t;
    int len = a.length > b.length ? a.length : b.length;
    for (int i = 0; i < len; i++) {
        int ta = i < a.length ? a[i] - '0' : 0;
        int tb = i < b.length ? b[i] - '0' : 0;
        int base = ta - tb;
        if (base < 0) {
            base += 10;
            a[i + 1]--;
        }
        t.push_back(base + '0');
    }
    t.reverse();
    a.reverse();
    b.reverse();
    return t;
}


//@运算符重载实现
BigInteger &BigInteger::operator=(const BigInteger &a) {
    if (length != 0)//如果不是初始化调用的 = ，则肯定需要先把原来的内存delete掉
        delete[]nums;
    capacity = a.capacity;
    length = a.length;
    f = a.f;
    nums = new char[capacity];
    std::copy(a.nums, a.nums + length, nums);
    return *this;
}

BigInteger BigInteger::operator+(BigInteger &a) {
    BigInteger res;
    bool flag;
    if (a.f && f) { //同为负数情况，直接相加，再改符号
        res = add(*this, a);
        flag = true;
    } else if (a.f && !f) {//左正右负
        if (compare(a, *this)) { //看负数对应的nums是否比正数大
            flag = true;
            res = minus(a, *this);
        } else {
            flag = false;
            res = minus(*this, a);
        }
    } else if (!a.f && f) {
        if (compare(*this, a)) { //与上一个相同
            flag = true;
            res = minus(*this, a);
        } else {
            flag = false;
            res = minus(a, *this);
        }
    } else { //同时为正数就是最简单的加法
        flag = false;
        res = add(*this, a);
    }
    res.f = flag;
    return res;
}

BigInteger BigInteger::operator-(BigInteger &a) {
    BigInteger res;
    bool flag;
    if (a.f && f) { //同为负数情况--左边-右边==(不看符号)右边-(不看符号)左边
        if (compare(a, *this)) {
            flag = false;
            res = minus(a, *this);
        } else {
            if (isEqual(*this, a))
                flag = false;
            else flag = true;
            res = minus(*this, a);
        }
    } else if (a.f && !f) { //左边为正，右边为负--左边-右边==左边+右边
        flag = false;
        res = add(a, *this);
    } else if (!a.f && f) { //右边为正，左边为负--左边-右边==两边为负的加法
        flag = true;
        res = add(a, *this);
    } else { //同时为正数--左边-右边==左边-右边(分类讨论正负
        if (compare(a, *this)) { //右边>左边,符号为负
            res = minus(a, *this);
            flag = true;
        } else { //右边<左边，符号为正
            res = minus(*this, a);
            flag = false;
        }
    }
    res.f = flag;
    return res;
}

bool BigInteger::operator<(const BigInteger &a) const {
    if (f && !a.f) { //其中一个为负数，则那个是更小的
        return true;
    } else if (!f && a.f)
        return false;
    if (f) { //两者都为负数的情况，左边的值要更大则为true
        return compare(*this, a);
    }//两者均为正数，则值更小的在左边为true
    return compare(a, *this);
}


//@基本成员函数
void BigInteger::reverse() {
    int l = 0, r = length - 1;
    while (l < r) {
        std::swap(nums[l], nums[r]);
        l++;
        r--;
    }
}

void BigInteger::push_back(char x) {
    if (length >= capacity) {
        capacity *= 2;
        char *t = nums;
        nums = new char[capacity];
        std::copy(t, t + length, nums);
        delete[]t;
    }
    nums[length++] = x;
}

void BigInteger::print() {
    if (f)
        printf("-");
    nums[length] = '\0';
    int i = 0;
    while (nums[i] == '0')i++;
    printf("%s", nums + i);
}

void BigInteger::read() {
    char c = getchar();
    if (c == '-') {
        f = true;
        c = getchar();
    }
    while (c == '0') c = getchar();//将前导0消耗掉
    while (c != '\n') {
        push_back(c);//不断的调用push_back即可
        c = getchar();
    }
}