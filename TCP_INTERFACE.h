//
// Created by Alone on 2021/8/17.
//

#ifndef MY_TINY_STL_TCP_INTERFACE_H
#define MY_TINY_STL_TCP_INTERFACE_H

#include "_public_socket.h"

class TCP_INTERFACE {
public:
    TCP_INTERFACE() {
        //初始化 DLL
        WSADATA wsaData;
        WSAStartup(MAKEWORD(2, 2), &wsaData);
    }

    //返回值小于等于0时发生错误
    virtual int Send(const void *buf, const int buflen) = 0;

    virtual int Recv(void *buf, const int buflen) = 0;

    //closesocket返回值不为0则发生错误
    virtual bool Close() = 0;

    ~TCP_INTERFACE() {
        WSACleanup();
    }

};


#endif //MY_TINY_STL_TCP_INTERFACE_H