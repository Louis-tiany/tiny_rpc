/*
	* File     : test.cc
	* Author   : *
	* Mail     : *
	* Creation : Sat 26 Dec 2020 08:57:19 PM CST
*/

#include <iostream>
#include <string>
#include "include/EventLoop.h"
#include "include/TcpServer.h"
#include "include/Timer.h"
#include "include/TimerQueue.h"

int main(int argc, char *argv[])
{
    MessageCallback f = [&](const TcpConnectionPrt &conn, std::string &input_buffer){
        char buf[16] = "trailing\n";
        printf("message: %s\n", input_buffer.c_str());
        conn->send((void *)buf, strlen(buf));
        printf("after write in message_callback\n");
    };

    TimerCallback timeout = [](){
        TimeStamp now = TimeStamp::now();
        std::string tmp = now.to_format_string();
        int num = 0;
        printf("server timeout %d %s\n", num++, tmp.c_str());
    };

    EventLoop loop;//add_time(TimeStamp::now(), 1),
    //loop.run_every(10, timeout);
    printf("now time %s\n", TimeStamp::now().to_format_string().c_str());
    loop.run_at(add_time(TimeStamp::now(), 1.0), timeout);
    TcpServer server(&loop);
    server.set_message_callback(f);
    server.start();
    loop.loop();

    return 0;
}
