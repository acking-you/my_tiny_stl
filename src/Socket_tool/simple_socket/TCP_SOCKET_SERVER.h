//
// Created by Alone on 2021/8/16.
//

#ifndef MY_TINY_STL_TCP_SOCKET_SERVER_H
#define MY_TINY_STL_TCP_SOCKET_SERVER_H

#include "TCP_INTERFACE.h"

class TCP_SOCKET_SERVER : public TCP_INTERFACE {
public:
    TCP_SOCKET_SERVER();

    ~TCP_SOCKET_SERVER() override;

    void Bind(int port);

    void Listen();

    socket_t Accept();

    int Send(socket_t clnt, const void *buf, const int buflen) override;

    int Recv(socket_t clnt, void *buf, const int buflen) override;

    void Close(socket_t clnt) override;


private:
    socket_t servSock;
    sockaddr_in sockAddr;

};


#endif //MY_TINY_STL_TCP_SOCKET_SERVER_H
