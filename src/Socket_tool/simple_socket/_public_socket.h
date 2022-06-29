//
// Created by Alone on 2021/8/16.
//

#ifndef MY_TINY_STL__PUBLIC_SOCKET_H
#define MY_TINY_STL__PUBLIC_SOCKET_H

#ifdef _WIN32
#include <winsock2.h>
#pragma comment (lib, "ws2_32.lib")  //加载 ws2_32.dll
typedef SOCKET socket_t;
typedef SOCKADDR sockaddr;
#elifdef __linux__
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <netinet/in.h>  //sockaddr_in结构体
#include <arpa/inet.h>
#include<unistd.h>
#include <netdb.h>
typedef int socket_t;
#endif

#define ERR_EXIT(m) \
    do { \
        perror(m); \
        exit(1); \
    } while (0)

#define ERR_LOG(m) \
    do{ \
        perror(m);\
    }while(0)

#endif //MY_TINY_STL__PUBLIC_SOCKET_H
