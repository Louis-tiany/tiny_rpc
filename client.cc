/*
	* File     : client.cc
	* Author   : *
	* Mail     : *
	* Creation : Tue 29 Dec 2020 05:42:15 PM CST
*/

#include <iostream>
#include "include/TcpClient.h"


int main(int argc, char *argv[])
{


    EventLoop loop;

    TcpClient client(&loop, "127.0.0.1", 8888);
    client.set_conn_callback([&](const TcpConnectionPrt &conn){
        printf("client do conn callback\n");
        char buf[64] = "message from client say : hello world~~~\n";
        conn->send(buf, 64);
    });
    client.set_message_callback([](const TcpConnectionPrt &conn, std::string &b){
        printf("receive message from server: %s\n", b.c_str());
        printf("client do message callback\n");
        char buf[64] = "client message callback\n";
        //conn->send((void *)buf, 64);
    });

    client.connect();
    loop.loop();
    
    return 0;
}


