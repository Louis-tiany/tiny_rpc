/*
	* File     : test.cc
	* Author   : *
	* Mail     : *
	* Creation : Sat 26 Dec 2020 08:57:19 PM CST
*/

#include <iostream>
#include <memory>
#include <string>
#include <unordered_set>
#include <vector>
#include <list>
#include "../include/EventLoop.h"
#include "../include/TcpConnection.h"
#include "../include/TcpServer.h"
#include "../include/Timer.h"
#include "../include/TimerQueue.h"




class HeartBeat{



private:

};



















using WeakConnectionPtr = std::weak_ptr<TcpConnection>;

struct Entry{
    explicit Entry(const WeakConnectionPtr weak_conn):
        weak_conn_(weak_conn)
    {  }

    ~Entry(){
        TcpConnectionPrt conn = weak_conn_.lock();
        if (conn) {
            conn->shutdown();
        }
    }
    WeakConnectionPtr weak_conn_;
};


using EntryPtr = std::shared_ptr<Entry>;
using WeakEntryPtr = std::weak_ptr<Entry>;
using Bucket = std::unordered_set<EntryPtr>;
using WeakConnectionList = std::vector<Bucket> ;
using ConnectionList = std::list<WeakConnectionPtr>;


ConnectionList connection_list_;

ConnectionCallback conn_cb = [](const TcpConnectionPrt &conn){
    connection_list_.push_back(conn);
};


void send_message(){
    for(auto &conn : connection_list_){
        char buf[10] = "pingpong";
        if(conn.expired()){
            continue;
        }
        conn.lock()->send(buf, 10);
    }
}


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
    loop.run_every(10, send_message);
//    printf("now time %s\n", TimeStamp::now().to_format_string().c_str());
//    loop.run_at(add_time(TimeStamp::now(), 1.0), timeout);
    TcpServer server(&loop);
    server.set_message_callback(f);
    server.set_connection_callback(conn_cb);
    server.start();
    loop.loop();

    return 0;
}
