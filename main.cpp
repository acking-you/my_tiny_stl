#include <bits/stdc++.h>
#include "AVLTree.h"
#include "Treap.h"
#include "BinarySearch.h"
using namespace L_B__;
/*测试数据：一千万随机数据or极端数据
 * 第一轮：insert操作--随机情况Treap(看运气，毕竟随机事件)>=<AVL>>BST--极端情况AVL>>Treap BST直接暴毙
 * 第二轮: remove操作--Treap被AVL吊打，BST就别提了
 * 下面就没得继续展开的比较了，总结就是Treap相对好写一点，效率高不高看运气。
 *  还有就是Treap在直接处理第K大的值具有优势，以及按排位查找具有优势。
 *  优势：由于treap每个结点都含有它整个结点个数的记录，所以可以很快的查出值的排名和排名的值。
 * */
int main() {
    using namespace std;
    //Treap a;

    AVLTree a;
    Treap b; /*功能测试说明：按排位取值已经正常测试实现，但按值取排位仍未实现*/
    BinarySearch c;
    for(int i=1;i<2000;i++)
    {
        b.insert(i);
    }
    for(Treap::iterator it = b.begin();it != b.end();++it){
        printf("%d ",*it);
    }
    //for(int i=0;i<=1000;i++){
    //    b.insert(i);
    //}
    //printf("测试\n");
    //b.inorder_print();
    //printf("\n根据排名查值");
    //for(int i=1;i<=1000;i++){
    //    printf("%d ",b.queryValue(i));
    //}
    //printf("\n根据值查排名");
    //for (int i = 1; i <= 1000; ++i) {
    //    printf("%d ",b.queryRank(i));
    //}
    //cout<<endl;
    //for(int i=1;i<=4;i++){
    //    b.insert(i);
    //}
    //printf("Insert:\n");
    //auto start = clock();
    //for(int i=1;i<10000000;i++){
    //    int x = rand();
    //    b.insert(x);
    //}
    //cout<<clock()-start<<"ms"<<'\n';
    //start = clock();
    //for(int i=1;i<10000000;i++){
    //    int x = rand();
    //    a.insert(x);
    //}
    //
    //cout<<clock()-start<<"ms"<<'\n';
    //start = clock();
    //for(int i=1;i<10000000;i++){
    //    int x = rand();
    //    c.insert(x);
    //}
    //cout<<clock()-start<<"ms"<<'\n';
    //
    //
    //printf("remove\n");
    //start = clock();
    //for(int i=1;i<10000000;i++){
    //    int x = rand();
    //    b.remove(x);
    //}
    //cout<<clock()-start<<"ms"<<'\n';
    //start = clock();
    //for(int i=1;i<10000000;i++){
    //    int x = rand();
    //    a.remove(x);
    //}

    //cout<<clock()-start<<"ms"<<'\n';
    //start = clock();
    //for(int i=1;i<10000000;i++){
    //    int x = rand();
    //    c.(x);
    //}
    //cout<<clock()-start<<"ms"<<'\n';
    //a.inorder_print();
    return 0;
   
}