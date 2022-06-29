//
// Created by Alone on 2021/9/7.
//
#include <iostream>
#ifndef MY_TINY_STL_COMPLEX_H
#define MY_TINY_STL_COMPLEX_H


class Complex {
public:
    Complex(double x = 0,double y = 0):_x(x),_y(y){};
    Complex& operator +(const Complex&temp);
    Complex& operator-(const Complex&temp);
    Complex& operator*(const Complex&temp);
    Complex& operator/(const Complex&temp);
    friend std::ostream& operator<<(std::ostream& t1,Complex&t2);
    friend std::istream& operator>>(std::iostream& t1,Complex&t2);
private:
    double _x;
    double _y;
};



#endif //MY_TINY_STL_COMPLEX_H
