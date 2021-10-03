#include "Heap.h"
#include <ctime>
#include <queue>
using namespace std;
#define MAX_SIZE 100000000

int main() {
    L_B__::Heap<int> a;
    priority_queue<int> Q;
    auto start = clock();
    //@push测试
    int step = 1;
    for(int i=1;i<MAX_SIZE;i++){
        Q.push(step%i);
        step += 2;
    }
    cout<<"STL Push:"<<clock()-start<<"ms"<<endl;
    start = clock();
    step = 1;
    for(int i=1;i<MAX_SIZE;i++){
        a.push(step%i);
        step += 2;
    }
    cout<<"My Push:"<<clock()-start<<"ms"<<endl;

    //@pop测试
    start = clock();
    for(int i=1;i<MAX_SIZE;i++){
        Q.pop();
    }
    cout<<"STL Pop:"<<clock()-start<<"ms"<<endl;
    start = clock();
    for(int i=1;i<MAX_SIZE;i++){
        a.pop();
    }
    cout<<"My Pop:"<<clock()-start<<"ms"<<endl;
}