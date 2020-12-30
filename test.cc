/*
	* File     : test.cc
	* Author   : *
	* Mail     : *
	* Creation : Sat 26 Dec 2020 08:57:19 PM CST
*/

#include <iostream>
#include "EventLoop.h"
#include "TcpServer.h"
#include "Serilazer.h"

int main(int argc, char *argv[])
{
    A *a = nullptr;
    MessageCallback f = [&](const TcpConnectionPrt &conn, char *input_buffer){
        a = A::deserilaze(input_buffer);

        printf("client index:%d val%d\n", a->index_, a->val_);
        char buf[16] = "trailing\n";
        snprintf(buf, 16, "send: %d\t%d\n", a->index_, a->val_);
        conn->send((void *)buf, strlen(buf));
        printf("after write in message_callback\n");
    };

    EventLoop loop;
    TcpServer server(&loop, f);
    server.start();
    loop.loop();
    
    return 0;
}
