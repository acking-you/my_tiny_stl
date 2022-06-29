//
// Created by Alone on 2021/8/17.
//

#ifndef MY_TINY_STL_TCP_INTERFACE_H
#define MY_TINY_STL_TCP_INTERFACE_H

#include "_public_socket.h"

class TCP_INTERFACE {
public:
    TCP_INTERFACE() {
#ifdef _WIN32
        //初始化 DLL
        WSADATA wsaData;
        WSAStartup(MAKEWORD(2, 2), &wsaData);
#endif
    }

    //返回值小于等于0时发生错误
    virtual int Send(socket_t clnt, const void *buf, const int buflen) = 0;

    virtual int Recv(socket_t clnt, void *buf, const int buflen) = 0;

    //closesocket返回值不为0则发生错误
    virtual void Close(socket_t clnt) = 0;

    virtual ~TCP_INTERFACE() {
#ifdef _WIN32
        WSACleanup();
#endif
    }

};


#endif //MY_TINY_STL_TCP_INTERFACE_H
