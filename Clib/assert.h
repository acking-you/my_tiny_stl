//
// Created by Alone on 2021/12/18.
//
#include <stdio.h>
#include <stdlib.h>

#ifndef MY_TINY_STL_ASSERT_H
#define MY_TINY_STL_ASSERT_H
#ifdef NDEBUG   //当程序为发布状态时直接定义为下面这个空语句宏
    #define assert(expression) ((void)0)
#else
void __cdecl _assert(//错误信息打印
        const char *_Message,
        const char * _File,
        unsigned       _Line){
    printf("Assertion failed!\n");

    fputc('\n',stdout);

    printf("File: %s, Line %d\n",_File,_Line);

    fputc('\n',stdout);

    printf("Expression: %s",_Message);
    exit(3);
}


#define assert(expression) (void)( \
        (!!(expression))||         \
        (_assert(#expression,__FILE__,(unsigned)(__LINE__)),0)\
        )

#endif

#endif //MY_TINY_STL_ASSERT_H
