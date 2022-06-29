//
// Created by Alone on 2022-6-27.
//
#include"TCP_SOCKET_SERVER.h"
#include <iostream>

int main(){
    TCP_SOCKET_SERVER socketServer;
    socketServer.Bind(2222);
    socketServer.Listen();
    do{
        auto client = socketServer.Accept();
        while(1){
            char buffer[1024]{};
            int recvLen;
            if((recvLen = socketServer.Recv(client,(void*)buffer,1024))<0){
                ERR_LOG("recv");
                close(client);
                break;
            }
            if(socketServer.Send(client,(void*)buffer,recvLen)<0){
                ERR_LOG("send");
                close(client);
                break;
            }
        }
    }while(1);
}