//
// Created by Alone on 2021/8/18.
//

#ifndef MY_TINY_STL_TCP_SOCKET_CLIENT_H
#define MY_TINY_STL_TCP_SOCKET_CLIENT_H

#include "TCP_INTERFACE.h"
#include <iostream>


class TCP_SOCKET_CLIENT : public TCP_INTERFACE {
public:
    TCP_SOCKET_CLIENT();

    ~TCP_SOCKET_CLIENT() override;

    socket_t Connect(const char *IPAdrr, u_short port);

    //用于利用URL(域名)查询IP地址
    static void Gethostbyname(const char *URL);

    //接口必须实现的函数
    int Send(socket_t clnt, const void *buf, const int bufSize)override;

    int Recv(socket_t clnt, void *buf, const int bufSize) override;

    void Close(socket_t clnt) override;

private:
    //由于一般客户端只需要一个套接字实现连接,然后还需要一个socketadrr_in连接内容的赋值
    socket_t clntSock;
    sockaddr_in sockAddr;
};


#endif //MY_TINY_STL_TCP_SOCKET_CLIENT_H
