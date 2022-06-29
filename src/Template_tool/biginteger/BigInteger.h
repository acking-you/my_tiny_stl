//
// Created by Alone on 2022-4-2.
//

#ifndef BIGINTEGER_BIGINTEGER_H
#define BIGINTEGER_BIGINTEGER_H
#include <string>
#include <vector>

using std::vector;
using std::string;
using ull = unsigned long long;
class BigInteger {
    string multi(string const& a,string const& b){
        string ret;
        ull sz_a = a.size(),sz_b = b.size();
        ret.reserve(sz_a+sz_b+1);
        container.clear();
        container.resize(sz_a+sz_b+1); //a*b肯定不会超过它们的长度和

        ull index = 0,upper=0;
        for (int i = 0; i < sz_a; ++i) {//TODO 计算乘法
            ull tmp_index = index;
            for (int j = 0; j < sz_b; ++j) {
                container[tmp_index++] += (a[i]-'0')*(b[j]-'0');
            }
            ++index;
        }
        //TODO 去除末尾的0
        while (!container.empty()&&container.back()==0)container.pop_back();

        //TODO 记录答案
        for(int i=0;i<container.size()||upper;i++){
            if(i<container.size())
                upper += container[i];
            ret.push_back(char(upper%10+'0'));
            upper /= 10;
        }
        return ret;
    }
    bool reverseCheck();
    [[nodiscard]] int signedCheck(string &b) const;
    [[nodiscard]] int signedCheck(int sign) const;
public:
    BigInteger();
    explicit BigInteger(ull number);
    explicit BigInteger(string  number);
    BigInteger& setSign(int);
    BigInteger& setFlag(int);
//TODO 由于怕使用const&导致check flag操作还得重新copy一个数据，所以用了&&，但由于不是模板推导，所以&&不算万能了😂
    BigInteger operator*(BigInteger && src);
    BigInteger& operator*=(BigInteger &&src);
    BigInteger operator*(BigInteger& src);
    BigInteger& operator*=(BigInteger&src);
    BigInteger operator*(ull src);
    BigInteger& operator*=(ull src);
    BigInteger operator*(string src);
    BigInteger& operator*=(string src);

    friend std::ostream& operator<<(std::ostream& os,BigInteger&& obj);
    friend std::ostream& operator<<(std::ostream& os,BigInteger& obj);
private:
    string bigNumber;
    vector<int> container;
    int flag = -1;//TODO 用于判断当前是否处于逆序状态
    int sign;//TODO 用于判断当前的符号
};


#endif //BIGINTEGER_BIGINTEGER_H
