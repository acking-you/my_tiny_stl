#include <iostream>
#include <memory>
#include <vector>
#include <algorithm>
#include<stack>
#include"../../../../BenchMark/Timer.h"

using namespace std;
int main() {
    //对函数栈的模拟过程
    //一个递归过程包含 ：1.栈指针和pc指针 2.栈空间（返回值空间、参数空间、代码块返回空间（用于恢复现场一般是PC值 3.入栈出栈
    //我们用结构体去模拟需要：参数空间、代码块索引、返回值空间
    auto fib = [](int n){
        int ret;    //用于临时承接递归向上返回的结果
        struct data
        {
            int a0,v0,ra; //a0为现场参数数据、v0为该层递归返回数据，ra记录下次此次需要执行的代码块
        };
        stack<data> S;
        S.push({n,0,0});
        while(!S.empty())
        {
            data now=S.top();S.pop();
            switch(now.ra)
            {
                case 0: //第一个递归函数
                {
                    if(now.a0==1||now.a0==2) //递归的终止条件
                    {
                        ret = 1; //向上返回
                    }
                    else
                    {
                        now.ra=1;       //由于已经要进入下层，故下次回到现场需要执行代码块1
                        S.push(now);    //本层入栈，保护现场
                        S.push({now.a0-1,0,0});//继续下一层
                    }
                    continue;
                }
                case 1: //第二个递归函数
                {
                    now.v0=ret; //第一次递归回来，用v0保存到函数栈中
                    now.ra=2;   //下次需要执行的代码块
                    S.push(now); //继续入栈，保护现场
                    S.push({now.a0-2,0,0}); //继续下一层
                    continue;
                }
                case 2:
                {
                    now.v0+=ret;//第二次递归回来将本次下层的返回值与在代码块1里面暂存的值相加
                    ret=now.v0; //返回上层
                    continue;
                }
            }
        }
        return ret;
    };

    auto fib2 = [](auto fib,int n){
        if(n==1||n==2)return 1;
        return fib(fib,n-1)+fib(fib,n-2);
    };

    for(int i=1;i<10;i++){
        {
            Timer t;
            fib(i);
        }
        {
            Timer t;
            fib2(fib2,i);
        }
    }
    return 0;
}
