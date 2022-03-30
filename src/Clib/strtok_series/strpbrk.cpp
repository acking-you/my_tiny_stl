//
// Created by Alone on 2021/11/23.
//
#define NULL 0
#include <stdbool.h>
typedef unsigned char uchar;

inline int get_pos(uchar x) {
    return x % 32;
}

char *strpbrk(const char *s1, const char *s2) {
    if (s1 == NULL || s2 == NULL)
        return NULL;
    uchar cset[32] = {0};                        //用32个unsigned char对每个位进行bool运算可以更节省内存
    while ((*s2) != '\0') {                      //创建set,%32决定放入哪个盒子中，/32决定放入8位的哪个位
        uchar t = (uchar) *s2++;
        cset[get_pos(t)] |= 1 << (t / 32);       //由于最大值255所以t/32为0~31
    }
    while ((*s1) != '\0') {
        uchar t = (uchar) *s1;
        if (cset[get_pos(t)] & (1 << (t / 32))) {//bitmap的查找方式
            return (char *) s1;
        } else {
            ++s1;
        }
    }
    return NULL;
}
