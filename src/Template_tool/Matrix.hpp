//
// Created by L_B__ on 2021/11/21.
//

#ifndef MY_TINY_STL_MATRIX_HPP
#define MY_TINY_STL_MATRIX_HPP

#include <cassert>
#include <algorithm>
#include <iostream>

//#define _MOD

template<typename T>
class Matrix {
    /*Type define*/
    typedef T data_t;
    typedef int ssize_t;
    /*data source*/
    data_t **data;
    ssize_t n;
    ssize_t m;
public:
    static const data_t MOD;
public:
    /*default construct*/
    Matrix() : m(0), n(0), data(nullptr) {}

    /*custom construct*/
    Matrix(data_t **mat, ssize_t n, ssize_t m) : data(mat), n(n), m(m) {}//外部申请内存传入内部
    Matrix(ssize_t n, ssize_t m) : data(nullptr), n(0), m(0) {//外部指定矩阵的行和列即可，内存初始化在内部进行
        assert(n > 0 && m > 0);
        setMemory(n,m);
    }

    /*copy construct*/
    Matrix(Matrix &src) : data(nullptr), n(src.n), m(src.m)//也可用const &引用类型，但这样很多右值的情况都不会调用移动构造了
    {
        assert(n > 0 && m > 0);
        data = new data_t *[n];
        for (int i = 0; i < n; ++i) {
            data[i] = new data_t[m];
            std::copy(src.data[i], src.data[i] + m, data[i]);
        }
    }

    /*move construct*/
    Matrix(Matrix<data_t> &&src) : n(src.n), m(src.m), data(nullptr) {
        assert(src.data != nullptr && n > 0 && m > 0);
        data = src.data;
        src.data = nullptr;
        src.n = src.m = 0;
    }

    /*destruct*/
    ~Matrix() {
        destroy();
    }

    void setMemory(size_t n,size_t m){
        if(data!= nullptr)
            return;
        assert(n > 0 && m > 0);
        this->n = n;
        this->m = m;
        data = new data_t *[n];
        for (int i = 0; i < n; i++) {
            data[i] = new data_t[m];
        }
        init(data, n, m);
    }

    /*overload*/
    //加上MOD的特殊版本
    #ifdef _MOD

    Matrix operator*(const Matrix<data_t> &src)//建议返回右值，返回左值的后续坑比较多，参数const &既可以接受左值也可接受右值
    {
        assert(data != nullptr && src.data != nullptr && m == src.n && m > 0 && n > 0 && src.m > 0);//进行矩阵乘法的必要条件
        data_t **tmp = new data_t *[n]; //为tmp申请动态内存，因为是传出参数
        for (int i = 0; i < n; ++i) {
            tmp[i] = new data_t[m];
        }
        for (int i = 0; i < n; ++i)//开始更新tmp
        {
            for (int j = 0; j < src.m; ++j) {
                data_t sum = 0;
                for (int k = 0; k < m; ++k) {
                    sum = (sum + data[i][k] * src.data[k][j]) % MOD;
                }
                tmp[i][j] = sum;
            }
        }
        //直接构造匿名对象返回
        return Matrix(tmp, n, src.m);;
    }

    Matrix &operator*=(const Matrix<data_t> &src)//*= 想一想我们平时的使用，就是返回一个左值
    {
        assert(data != nullptr && src.data != nullptr && m == src.n && m > 0 && n > 0 && src.m > 0);//进行矩阵乘法的必要条件
        data_t tmp[n][src.m];//静态内存就行，毕竟只是临时存数据的
        for (int i = 0; i < n; ++i)//开始更新tmp
        {
            for (int j = 0; j < src.m; ++j) {
                data_t sum = 0;
                for (int k = 0; k < m; ++k) {
                    sum = (sum + data[i][k] * src.data[k][j]) % MOD;
                }
                tmp[i][j] = sum;
            }
        }
        //由于此时的date内存可能不够容下tmp数据，所以可能需要重新进行内存申请
        //注意重新申请列内存的时候，需要把之前的内存释放
        if (m != src.m) {
            for (int i = 0; i < n; ++i) {
                delete[]data[i];
                data[i] = nullptr;
                data[i] = new data_t[src.m];
            }
        }
        for (int i = 0; i < n; ++i) {
            assert(data[i] != nullptr);
            std::copy(tmp[i], tmp[i] + src.m, data[i]);
        }
        return *this;
    }

    #endif

    #ifndef _MOD
    Matrix operator*(const Matrix<data_t>&src)//建议返回右值，返回左值的后续坑比较多，参数const &既可以接受左值也可接受右值
    {
        assert(data!= nullptr&&src.data!= nullptr&&m==src.n&&m>0&&n>0&&src.m>0);//进行矩阵乘法的必要条件
        data_t** tmp = new data_t *[n]; //为tmp申请动态内存，因为是传出参数
        for (int i = 0; i < n; ++i) {
            tmp[i] = new data_t [m];
        }
        for(int i=0;i<n;++i)//开始更新tmp
        {
            for (int j = 0; j < src.m; ++j) {
                data_t sum = 0;
                for (int k = 0; k < m; ++k) {
                    sum = sum + data[i][k]*src.data[k][j];
                }
                tmp[i][j] = sum;
            }
        }
        //直接构造匿名对象返回
        return Matrix (tmp,n,src.m);
    }
    /*与乘法的唯一区别在于乘法是构造一个新的对象，而*=返回的是this*/
    Matrix &operator*=(const Matrix<data_t> &src)//*= 想一想我们平时的使用，就是返回一个左值
    {
        assert(data!= nullptr&&src.data!= nullptr&&m==src.n&&m>0&&n>0&&src.m>0);//进行矩阵乘法的必要条件
        data_t tmp[n][src.m];//静态内存就行，毕竟只是临时存数据的
        for(int i=0;i<n;++i)//开始更新tmp
        {
            for (int j = 0; j < src.m; ++j) {
                data_t sum = 0;
                for (int k = 0; k < m; ++k) {
                    sum = sum + data[i][k]*src.data[k][j];
                }
                tmp[i][j] = sum;
            }
        }
        //由于此时的date内存可能不够容下tmp数据，所以可能需要重新进行内存申请
        //注意重新申请列内存的时候，需要把之前的内存释放
        if(m!=src.m){
            for (int i = 0; i < n; ++i) {
                delete []data[i];
                data[i] = nullptr;
                data[i] = new data_t [src.m];
            }
        }
        for (int i = 0; i < n; ++i) {
            assert(data[i] != nullptr);
            std::copy(tmp[i],tmp[i]+src.m,data[i]);
        }
        return *this;
    }
    #endif


    //赋值号的重载需要对左右值情况进行分开处理以达到拷贝：该深则深，该浅则浅
    Matrix &operator=(Matrix &src)//如果右边是左值，则需要深拷贝（不拷贝指针
    {
        assert(src.data != nullptr && src.n > 0 && src.m > 0);
        destroy();//拷贝前进行内存的清除
        n = src.n;
        m = src.m;
        data = new data_t *[n];
        for (int i = 0; i < n; ++i) {
            assert(data[i] != nullptr);//其实没太大必要，因为new申请失败会抛出bad_alloc异常
            data[i] = new data_t[m];
            std::copy(src.data[i], src.data[i] + m, data[i]);
        }
        return *this;
    }

    Matrix &operator=(Matrix &&src)//如果右边是右值，则进行浅拷贝
    {
        assert(src.data != nullptr && src.n > 0 && src.m > 0);
        destroy();//拷贝前进行内存的清除
        n = src.n;
        m = src.m;
        data = src.data;

        src.data = nullptr;
        src.n = src.m = 0;
        return *this;
    }

    data_t *operator[](ssize_t i) {
        assert(i >= 0 && i < n);
        return data[i];
    }


    /*快速幂实现，面向对象的接口*/
    void quickPow(data_t c) {
        QPow(*this, c);
    }

    /*setter和getter实现*/
    Matrix<T>& setData(ssize_t x, ssize_t y, data_t src) {
        assert(x >= 0 && x < n && y >= 0 && y < m);
        data[x][y] = src;
        return *this;
    }

    data_t &getData(ssize_t x, ssize_t y) {
        //返回一个引用，可以在外界直接修改，当然外界也要用引用来接住，否则还只是一个拷贝
        assert(x >= 0 && x < n && y >= 0 && y < m);
        return data[x][y];
    }

    /*equals 方法*/
    friend std::ostream & operator<<(std::ostream& out,Matrix const&  src) {
        out<<'{';
        for (int i = 0; i < src.n; ++i) {
            if(i!=0)
                out<<' ';
            for (int j = 0; j < src.m; ++j) {
                out << src.data[i][j] << ',';
            }
            if(i!=src.n-1)
                out <<'\n';
        }
        out<<'}';
        return out;
    }

public:
    static void init(data_t **data, ssize_t n, ssize_t m) {
        assert(data != nullptr && n > 0 && m > 0);

        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (i == j)data[i][j] = 1;
                else data[i][j] = 0;
            }
        }
    }

    static void QPow(Matrix &_Dest, data_t n) {
        assert(n >= 0);
        Matrix tmp(_Dest);//制造一份拷贝，用于倍增
        init(_Dest.data, _Dest.n, _Dest.m);//初始化为单位矩阵
        if (n == 0)
            return;
        while (n) {
            if (n & 1) {
                _Dest *= tmp;
            }
            tmp *= tmp;
            n >>= 1;
        }
    }

private:
    void destroy() {
        if (data == nullptr)
            return;
        for (int i = 0; i < n; i++) {
            if (data[i] == nullptr)//如果这片内存中有nullptr，则说明之前已经被delete过了
                return;
            delete[] data[i];
            data[i] = nullptr;
        }
        delete[] data;
        data = nullptr;
    }
};



#endif //MY_TINY_STL_MATRIX_HPP
