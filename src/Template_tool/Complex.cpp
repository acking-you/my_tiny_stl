//
// Created by Alone on 2021/9/7.
//

#include "Complex.h"
Complex & Complex::operator+(const Complex &temp) {
    _x+=temp._x;
    _y+=temp._y;
    return *this;
}
Complex & Complex::operator-(const Complex &temp) {
    _x-=temp._x;
    _y-=temp._y;
    return *this;
}
Complex & Complex::operator*(const Complex &temp) {
    this->_x = (this->_x*temp._x- this->_y*temp._y);
    this->_y = (this->_y*temp._x+ this->_x*temp._y);
    return *this;
}
Complex & Complex::operator/(const Complex &temp) {
    this->_x = (this->_x*temp._x+ this->_y*temp._y)/(temp._x*temp._x+temp._y*temp._y);
    this->_y = (temp._x* this->_y- this->_x*temp._y)/(temp._x*temp._x+temp._y*temp._y);
    return *this;
}
std::ostream& operator<<(std::ostream& t1,Complex&t2){
    return t1<<t2._x<<'+'<<t2._y<<'i';
}
std::istream& operator>>(std::iostream& t1,Complex&t2){
    return t1>>t2._x>>t2._y;
}