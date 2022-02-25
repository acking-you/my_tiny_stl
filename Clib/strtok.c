//
// Created by Alone on 2021/11/23.
//
#define NULL 0

typedef unsigned char uchar;

inline int get_pos(uchar x) {
    return x % 32;
}

char *strtok(char *src, const char *delimiters) {
    char *sbegin, *send;
    static char *ssave = NULL;
    sbegin = src ? src : ssave;           //如果src为NULL就继续上一次的缓存
    uchar cset[32] = {0};                 //用32个unsigned char对每个位进行bool运算可以更节省内存
    while ((*delimiters) != '\0') {       //更新set
        uchar t = (uchar) *delimiters++;
        cset[get_pos(t)] |= 1 << (t / 32);//由于最大值255所以t/32为0~7
    }
    //让sbegin指向不在set中的位置
    while (*sbegin != '\0' && (cset[get_pos(*sbegin)] & (1 << (((uchar) *sbegin) / 32)))) {
        ++sbegin;
    }
    if (*sbegin == '\0') {
        ssave = NULL;
        return NULL;
    }
    int idx = 0;
    //相当于strcspn的功能了
    while (sbegin[idx] != '\0' && !(cset[get_pos(sbegin[idx])] & (1 << ((uchar) sbegin[idx] / 32)))) {
        ++idx;
    }
    send = sbegin + idx;
    if (*send != '\0')
        *send++ = '\0';                   //画上终止符
    ssave = send;                         //更新下一次处理的缓存位置
    return sbegin;
}
