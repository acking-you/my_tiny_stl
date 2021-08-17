//
// Created by Alone on 2021/8/16.
//

#ifndef MY_TINY_STL_TCP_SOCKET_SERVER_H
#define MY_TINY_STL_TCP_SOCKET_SERVER_H

#include "TCP_INTERFACE.h"

class TCP_SOCKET_SERVER : public TCP_INTERFACE {
public:
    TCP_SOCKET_SERVER();

    ~TCP_SOCKET_SERVER();

    bool Bind(int port);

    bool Listen();

    bool Accept();

    int Send(const void *buf, const int buflen);

    int Recv(void *buf, const int buflen);

    bool Close();

private:
    SOCKET servSock;
    SOCKET clntSock;
    sockaddr_in sockAddr;
};


#endif //MY_TINY_STL_TCP_SOCKET_SERVER_H
