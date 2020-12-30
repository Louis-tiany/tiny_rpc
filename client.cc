/*
	* File     : client.cc
	* Author   : *
	* Mail     : *
	* Creation : Tue 29 Dec 2020 05:42:15 PM CST
*/

#include <iostream>
#include "TcpClient.h"
#include "Serilazer.h"


int main(int argc, char *argv[])
{

    A a(1,2);

    EventLoop loop;

    TcpClient client(&loop, "127.0.0.1", 8888);
    client.set_conn_callback([&](const TcpConnectionPrt &conn){
        printf("client do conn callback\n");
        char buf[64] = "message from client say : hello world~~~\n";
        conn->send((void *)a.serilaze(), sizeof(a));
    });
    client.set_message_callback([](const TcpConnectionPrt &conn, char *b){
        printf("receive message from server: %s\n", b);
        printf("client do message callback\n");
        char buf[64] = "client message callback\n";
        //conn->send((void *)buf, 64);
    });

    client.connect();
    loop.loop();
    
    return 0;
}


