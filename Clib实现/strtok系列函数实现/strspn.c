//
// Created by Alone on 2021/11/23.
//
#define NULL 0
#include <stdbool.h>
int strspn(const char* s1,const char* s2){
    if(s1==NULL || s2==NULL)//处理特殊情况
        return 0;
    bool cset[256]={0};
    while((*s2)!='\0'){	//创建set
        cset[*s2] = 1;
        ++s2;
    }
    int idx = 0;
    while(s1[idx] != '\0'){//得到正确的idx位置
        if(cset[s1[idx]])
            idx++;
        else
            break;
    }
    return idx;
}
