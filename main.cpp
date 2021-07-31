#include <iostream>
#include "UnionFind.h"
using namespace std;
int main(){
    UnionFind a(10);
    a.merge(1,2);
    a.merge(2,5);
    a.merge(5,6);
    a.merge(6,7);
    a.merge(3,8);
    a.merge(8,9);
    cout<<a.isConnected(1,5)<<' '<<a.isConnected(5,7)<<' ';
    cout<<a.isConnected(4,9)<<' ';
    a.merge(9,4);
    cout<<a.isConnected(4,9);
}