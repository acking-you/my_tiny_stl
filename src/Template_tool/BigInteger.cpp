//
// Created by Alone on 2022-4-2.
//

#include "BigInteger.h"
#include <algorithm>
#include <iostream>
#include <utility>
BigInteger::BigInteger():bigNumber(1,'1'),container(16) {
    sign = 0;
}

BigInteger::BigInteger(ull number):container(16) {
    bigNumber = std::move(std::to_string(number));
    if(number<0){
        sign = 1;
    }else
        sign = 0;
}

BigInteger::BigInteger(string number):bigNumber(std::move(number)) ,
container(16){
    sign = 0;
    sign = signedCheck(bigNumber);
}



bool BigInteger::reverseCheck()  {
    if(flag == -1){
        std::reverse(bigNumber.begin(), bigNumber.end());
        flag = 0;
    }
    return true;
}


BigInteger BigInteger::operator*(BigInteger&& src) {
    //TODO 相乘前保证两个是逆向的
    src.reverseCheck();
    reverseCheck();
    int n_sign = signedCheck(src.sign);
    return BigInteger(multi(bigNumber,src.bigNumber))
    .setSign(n_sign)
    .setFlag(0);
}

BigInteger& BigInteger::operator*=(BigInteger&&src) {
    //TODO 相乘前保证两者是逆向的
    src.reverseCheck();
    reverseCheck();
    sign = signedCheck(src.sign);
    bigNumber = std::move(multi(bigNumber,src.bigNumber));
    return *this;
}

BigInteger BigInteger::operator*(BigInteger &src) {
    src.reverseCheck();
    reverseCheck();
    int n_sign = signedCheck(src.sign);
    return BigInteger(multi(bigNumber,src.bigNumber))
    .setSign(n_sign)
    .setFlag(0);
}

BigInteger &BigInteger::operator*=(BigInteger &src) {
    src.reverseCheck();
    reverseCheck();
    sign = signedCheck(src.sign);

    bigNumber = std::move(multi(bigNumber,src.bigNumber));

    return *this;
}

BigInteger BigInteger::operator*(ull src) {
    auto str = std::to_string(src);
    int n_sign = signedCheck(str);

    std::reverse(str.begin(), str.end());

    reverseCheck();

    return BigInteger(multi(bigNumber, str))
    .setSign(n_sign)
    .setFlag(0);
}

BigInteger &BigInteger::operator*=(ull src) {
    auto str = std::to_string(src);
    sign = signedCheck(str);

    std::reverse(str.begin(), str.end());

    reverseCheck();
    bigNumber = std::move(multi(bigNumber, str));
    return *this;
}

BigInteger &BigInteger::operator*=(string src) {
    sign = signedCheck(src);
    std::reverse(src.begin(), src.end());
    reverseCheck();
    bigNumber = std::move(multi(bigNumber,src));
    return *this;
}

BigInteger BigInteger::operator*(string src) {
    auto n_sign = signedCheck(src);
    std::reverse(src.begin(), src.end());
    reverseCheck();
    return BigInteger(multi(bigNumber,src))
    .setSign(n_sign)
    .setFlag(0);
}

std::ostream &operator<<(std::ostream &os,BigInteger &&obj) {
    if(obj.flag==0)
        std::reverse(obj.bigNumber.begin(), obj.bigNumber.end());
    if(obj.sign == 1)
        os<<"-";
    os<<obj.bigNumber;
    return os;
}

std::ostream &operator<<(std::ostream &os, BigInteger &obj) {
    if(obj.flag==0)
        std::reverse(obj.bigNumber.begin(), obj.bigNumber.end());
    if(obj.sign==1)
        os<<"-";
    os<<obj.bigNumber;
    return os;
}

int BigInteger::signedCheck(string &b) const {
    int ret_sign;
    if(!b.empty()&&b.front()=='-'){
        b.erase(0,1);
        if(sign==1){
            ret_sign = 0;
        } else
            ret_sign = 1;
    }else{
        if(sign==1){
            ret_sign = 1;
        } else ret_sign = 0;
    }
    return ret_sign;
}

int BigInteger::signedCheck(int src_sign) const {
    int ret_sign;
    if(src_sign==1){
        if(sign==1){
            ret_sign = 0;
        } else
            ret_sign = 1;
    }else{
        if(sign==1){
            ret_sign = 1;
        } else ret_sign = 0;
    }
    return ret_sign;
}




BigInteger& BigInteger::setSign(int s) {
    sign = s;
    return *this;
}

BigInteger &BigInteger::setFlag(int t_flag) {
    flag = t_flag;
    return *this;
}








