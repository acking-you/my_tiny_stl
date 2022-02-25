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

    void Bind(int port);

    void Listen();

    SOCKET Accept();

    int Send(SOCKET clnt, const void *buf, const int buflen);

    int Recv(SOCKET clnt, void *buf, const int buflen);

    void Close(SOCKET clnt);

    void error_die(const char *str);

private:
    SOCKET servSock;
    sockaddr_in sockAddr;

};


#endif //MY_TINY_STL_TCP_SOCKET_SERVER_H
