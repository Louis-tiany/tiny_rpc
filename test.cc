/*
	* File     : test.cc
	* Author   : *
	* Mail     : *
	* Creation : Sat 26 Dec 2020 08:57:19 PM CST
*/

#include <iostream>
#include <string>
#include "EventLoop.h"
#include "TcpServer.h"


int main(int argc, char *argv[])
{
    MessageCallback f = [&](const TcpConnectionPrt &conn, char *input_buffer){
        char buf[16] = "trailing\n";
        printf("message: %s\n", input_buffer);
        conn->send((void *)buf, strlen(buf));
        printf("after write in message_callback\n");
    };

    EventLoop loop;
    TcpServer server(&loop, f);
    server.start();
    loop.loop();

    return 0;
}
