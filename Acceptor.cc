/*
	* File     : Acceptor.cc
	* Author   : *
	* Mail     : *
	* Creation : Sat 26 Dec 2020 09:12:48 PM CST
*/

#include <functional>
#include <iostream>
#include "Acceptor.h"

int create_nonblocking();

Acceptor::Acceptor(EventLoop *loop):
    loop_(loop),
    accept_socket_(create_nonblocking()),
    accept_channel_(loop_, accept_socket_.fd())
{
    accept_socket_.set_reuse_addr(true);
    accept_socket_.set_reuse_port(true);
    accept_socket_.bind_addr("0.0.0.0", 8888);
    accept_channel_.set_read_callback(std::bind(&Acceptor::hand_read,this));
    accept_channel_.set_index(0);
}


int create_nonblocking(){
    int fd = ::socket(AF_INET, SOCK_STREAM| SOCK_NONBLOCK | SOCK_CLOEXEC, IPPROTO_TCP);
    return fd;
}
void Acceptor::hand_read(){
    struct sockaddr_in client_addr;
    (void)client_addr;
    std::cout<<"accepting in" << __FILE__<<std::endl;
    int conn = accept_socket_.accept();
    std::cout << "new conn:"<< conn << std::endl;
    if (conn > 0){
        new_conn_callback_(conn);
    }
    else {

    }
}


void Acceptor::listen(){
    accept_socket_.set_nonblock();
    accept_socket_.listen();
    accept_channel_.enable_reading();
}
