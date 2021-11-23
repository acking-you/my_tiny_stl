//
// Created by Alone on 2021/11/23.
//

#ifndef MY_TINY_STL_QSORT_H
#define MY_TINY_STL_QSORT_H
#include <string.h>
typedef unsigned int _size_t;
//函数声明
void swap(char* a,char *b,int width);
void quickSort(char* base, _size_t size,_size_t left, _size_t right,int (*compar)(const void *, const void *));
void _qsort(void *base, _size_t nitems, _size_t size, int (*compar)(const void *, const void *));

/*函数实现*/
void swap(char* a,char *b,int width){//把一块width大小的内存分成一个字节的换
    char tmp;
    if(a!=b){//不是同一片内存才开始交换
        while (width--){
            tmp = *a;
            *a++ = *b;
            *b++ = tmp;
        }
    }
}
//快速排序真正的处理函数，一个字节一个字节的处理，而一个size大小的字节代表一个元素
//而关于比较部分的函数compar则是外部定义的回调函数，关于回调函数的标准，大于等于0表示
void quickSort(char* base, _size_t size,_size_t left, _size_t right,int (*compar)(const void *, const void *)) {
    if (left >= right)return;
    _size_t tl = left, tr = right;//拷贝一份左右指针，用于移动更新
    char cmp[size];
    //以中间的数为标准进行快排，用cmp存储，使得swap不会对cmp的内容作出任何改变
    memmove(cmp,(base + (tl+(tr-tl)/2)*size),size);
    while (tl <= tr) {
        while (compar(base+(tl*size),cmp)<0)tl++;//实际上可以直接根据0和1确定如何排序，然而C标准似乎是还需要利用到负数
        while (compar(cmp,base+(tr*size))<0)tr--;
        if (tl <= tr) {
            swap(base+(tl*size), base+(tr*size),size);
            tl++;
            tr--;
        }
    }
    /*递归分治完成*/
    quickSort(base,size, left, tr,compar);
    quickSort(base,size, tl, right,compar);
}

//快排入口
void _qsort(void *base, _size_t nitems, _size_t size, int (*compar)(const void *, const void *)) {
    quickSort((char*)base,size,0,nitems-1,compar);
}
#endif //MY_TINY_STL_QSORT_H
