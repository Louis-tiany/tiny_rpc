/*
    * File     : Acceptor.h
    * Author   : *
    * Mail     : *
    * Creation : Fri 25 Dec 2020 05:46:47 PM CST
*/

#ifndef _ACCEPTOR_H
#define _ACCEPTOR_H


#include <bits/types/__FILE.h>
#include <iostream>
#include <memory>
#include <ostream>
#include <string>
#include <vector>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>
#include <netinet/in.h>
#include <cstdlib>
#include <error.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <sys/poll.h>
#include <sys/types.h>
#include <assert.h>
#include <functional>

#include "Channel.h"
#include "Socket.h"

class EventLoop;
class Channel;
class Socket;


class Acceptor{
public:
    typedef std::function<void(int sockfd)> NewConnCallback;

    Acceptor(EventLoop *loop);
    void set_new_conn_callback(NewConnCallback new_conn_callback){
        new_conn_callback_ = std::move(new_conn_callback);
    }

    void listen();

    void hand_read();
    
    Channel *get_channel() { return &accept_channel_; }


private:
        EventLoop *loop_;
        NewConnCallback new_conn_callback_;
        Socket accept_socket_;
        Channel accept_channel_;
};

#endif
