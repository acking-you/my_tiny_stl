//
// Created by Alone on 2021/8/17.
//

#include "TCP_SOCKET_CLIENT.h"

//初始化
TCP_SOCKET_CLIENT::TCP_SOCKET_CLIENT() : clntSock(0) {
    memset(&sockAddr, 0, sizeof sockAddr);
}

//关闭套接字操作
bool TCP_SOCKET_CLIENT::Close() {
    if (clntSock == 0)
        return false;
    if (closesocket(clntSock) != 0)
        return false;
    clntSock = 0;
    return true;
}

//连接服务器操作
bool TCP_SOCKET_CLIENT::Connect(const char *IPAdrr, u_short port) {
    clntSock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    sockAddr.sin_family = PF_INET;
    sockAddr.sin_addr.s_addr = inet_addr(IPAdrr);
    sockAddr.sin_port = htons(port);
    if (connect(clntSock, (SOCKADDR *) &sockAddr, sizeof(sockAddr)) != 0) {
        closesocket(clntSock);
        clntSock = 0;
        return false;
    }
    return true;
}

//发送信息操作
int TCP_SOCKET_CLIENT::Send(const void *buf, const int bufSize) {
    return send(clntSock, (const char *) buf, bufSize, 0);
}

//接收信息操作
int TCP_SOCKET_CLIENT::Recv(void *buf, const int bufSize) {
    return recv(clntSock, (char *) buf, bufSize, 0);
}

//根据域名获取ip地址等信息
void TCP_SOCKET_CLIENT::Gethostbyname(const char *URL) {
    hostent *host = gethostbyname(URL);
    if (!host) {
        std::cout << "Get IP address error!\n";
        return;
    }
    //打印本命
    std::cout << URL << std::endl;
    //别名
    for (int i = 0; host->h_aliases[i]; i++) {
        printf("Aliases %d: %s\n", i + 1, host->h_aliases[i]);
    }
    //地址类型
    printf("Address type: %s\n", (host->h_addrtype == AF_INET) ? "AF_INET" : "AF_INET6");
    //IP地址,其中inet_ntoa()函数是将网络字节序转为本地的字节序，方便打印看懂
    for (int i = 0; host->h_addr_list[i]; i++) {
        printf("IP addr %d: %s\n", i + 1, inet_ntoa(*(struct in_addr *) host->h_addr_list[i]));
    }
}

//析构时需要确保所有东西已经关闭
TCP_SOCKET_CLIENT::~TCP_SOCKET_CLIENT() {
    if (clntSock != 0)
        closesocket(clntSock);
}
