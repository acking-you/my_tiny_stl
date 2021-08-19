//
// Created by Alone on 2021/8/16.
//

#include "TCP_SOCKET_SERVER.h"

//初始化操作
TCP_SOCKET_SERVER::TCP_SOCKET_SERVER() : servSock(0) {
    memset(&sockAddr, 0, sizeof(sockAddr));  //每个字节都用0填充
}

//绑定操作
void TCP_SOCKET_SERVER::Bind(int port) {
    servSock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    sockAddr.sin_family = PF_INET;  //使用IPv4地址
    sockAddr.sin_addr.s_addr = htonl(INADDR_ANY);  //具体的IP地址
    sockAddr.sin_port = htons(port);  //端口
    if (bind(servSock, (SOCKADDR *) &sockAddr, sizeof(SOCKADDR)) != 0) {
        error_die("bind");
    }
}

//置于监听状态
void TCP_SOCKET_SERVER::Listen() {
    if (servSock == 0)
        error_die("listen");
    if (listen(servSock, SOMAXCONN) != 0) {
        error_die("listen");
    }
}

//利用套接字的监听串口，接收客户端的请求，建立新的套接字进行存储信息
SOCKET TCP_SOCKET_SERVER::Accept() {
    SOCKADDR t;
    int nSize = sizeof(SOCKADDR);
    //后面两个参数为可选
    SOCKET clnt = accept(servSock, &t, &nSize);
    if (clnt <= 0)error_die("accept");
    return clnt;
}

//返回的是发送到缓冲区的字节长度
int TCP_SOCKET_SERVER::Send(SOCKET clnt, const void *buf, const int buflen) {
    return send(clnt, (const char *) buf, buflen, 0);
}

//返回已经接收的字节长度
int TCP_SOCKET_SERVER::Recv(SOCKET clnt, void *buf, const int buflen) {
    return recv(clnt, (char *) buf, buflen, 0);
}

//析构函数关闭socket
TCP_SOCKET_SERVER::~TCP_SOCKET_SERVER() {
    if (servSock != 0)closesocket(servSock);
}

void TCP_SOCKET_SERVER::Close(SOCKET clnt) {
    if (closesocket(clnt) != 0) {
        error_die("closesocket");
    }
}

void TCP_SOCKET_SERVER::error_die(const char *str) {
    printf("[hint]%s failed:%d", str, WSAGetLastError());
    exit(-1);
}