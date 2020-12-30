/*
	* File     : Connector.h
	* Author   : *
	* Mail     : *
	* Creation : Tue 29 Dec 2020 03:11:00 PM CST
*/

#ifndef _CONNECTOR_H
#define _CONNECTOR_H
#include <iostream>
#include <functional>
#include <memory>
#include <string>
#include "EventLoop.h"
#include "Socket.h"

class Connector : public std::enable_shared_from_this<Connector> {
public:
    typedef std::function<void(int sockfd)> NewConnectionCallback;
    Connector(EventLoop *loop, std::string ip, int port);
    ~Connector();

    void set_new_conn_callback(const NewConnectionCallback & cb)
    { new_conn_callback_ = cb; }

    void start();
    void restart();
    void stop();


private:
    enum States { kDisconnected, kConnecting, kConnected };
    void set_state(States state) { state_ = state; }
    void connect();
    void connecting(int sockfd);
    void handle_write();
    void handle_error();
    void start_in_loop();
    void stop_in_loop();
    void reset_channel();
    int remove_and_reset_channel();


private:
    EventLoop *loop_;
    std::string ip_;
    int port_;
    struct sockaddr_in server_addr_;
    bool connect_;

    NewConnectionCallback new_conn_callback_;
    States state_;
    std::unique_ptr<Channel> channel_;
};

#endif
