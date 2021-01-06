/*
	* File     : test.cc
	* Author   : *
	* Mail     : *
	* Creation : Sat 26 Dec 2020 08:57:19 PM CST
*/

#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_set>
#include <vector>
#include <list>
#include <map>
#include "../include/EventLoop.h"
#include "../include/TcpConnection.h"
#include "../include/TcpServer.h"
#include "../include/Timer.h"
#include "../include/TimerQueue.h"


using WeakConnectionPtr = std::weak_ptr<TcpConnection>;
using ConnectionList = std::list<WeakConnectionPtr>;


class HeartBeat{
public:
    HeartBeat(EventLoop *loop, InetAddress addr, double seconds):
        loop_(loop),
        server_(loop, addr),
        seconds_(seconds)
    {  
        server_.set_connection_callback(std::bind(&HeartBeat::on_connection, this, std::placeholders::_1));
        server_.set_message_callback(std::bind(&HeartBeat::on_message, this, std::placeholders::_1, std::placeholders::_2));
        loop_->run_every(seconds_, std::bind(&HeartBeat::on_time, this));
    }

    void start(){
        server_.start();
    }


    void on_connection(const TcpConnectionPrt &conn){
        WeakConnectionPtr weak_conn(conn);
        connection_table_[conn] = 3;
        char buf[32] = "connection established\n";
        conn->send((void *)buf, 32);
    }

    void on_message(const TcpConnectionPrt &conn, std::string &input_buffer){
        WeakConnectionPtr weak_conn(conn);
        printf("message from client: %s\n", input_buffer.c_str());
        connection_table_[weak_conn] = 3;
    }

    void on_time(){
        for( auto &item : connection_table_ ){
            if(item.second == 0){
                if(!item.first.expired()){
                    printf("a conn not send message showdown the conn\n");
                    item.first.lock()->shutdown();
                    continue;
                }
            }
            else{
                char buf[32] = "pingpong\n";
                item.first.lock()->send(buf, 32);
                item.second--;
            }
        }
    }

private:
    std::map<WeakConnectionPtr, int, std::owner_less<std::weak_ptr<TcpConnection>>> connection_table_;
    EventLoop *loop_;
    TcpServer server_;
    double seconds_;

};




int main(int argc, char *argv[])
{
    InetAddress addr("0.0.0.0", 8888);
    EventLoop loop;//add_time(TimeStamp::now(), 1),
    HeartBeat server(&loop, addr, 3.0);
    server.start();
    loop.loop();

    return 0;
}
