/*
	* File     : Connector.cc
	* Author   : *
	* Mail     : *
	* Creation : Tue 29 Dec 2020 03:11:04 PM CST
*/

#include <asm-generic/errno.h>
#include <cerrno>
#include <functional>
#include <iostream>
#include <string>
#include "Connector.h"


Connector::Connector(EventLoop *loop, std::string ip, int port):
    loop_(loop),
    ip_(ip),
    port_(port),
    connect_(false),
    state_(kDisconnected)
{
    memset(&server_addr_, 0, sizeof(server_addr_));
    server_addr_.sin_family = AF_INET;
    server_addr_.sin_port = ::htons(port);
    inet_pton(AF_INET, ip.c_str(), &server_addr_.sin_addr);
    printf("Connector ctor\n");
}

Connector::~Connector(){

}

void Connector::start(){
    connect_ = true;
    loop_->run_in_loop(std::bind(&Connector::start_in_loop, this));
}

void Connector::start_in_loop(){
    if( connect_ ){
        connect();
    }
    else{
        printf("sign not connect_\n");
    }
}

void Connector::restart(){
    set_state(kDisconnected);
    connect_ = true;
    start_in_loop();
}

void Connector::stop(){
    connect_ = false;
    loop_->run_in_loop(std::bind(&Connector::stop_in_loop, this));
}

void Connector::stop_in_loop(){
    if(state_ == kConnecting){
        set_state(kDisconnected);
        remove_and_reset_channel();
    }
}

void Connector::reset_channel(){
    channel_.reset();
}


int Connector::remove_and_reset_channel(){
    channel_->disable_all();
    channel_->remove();
    int sockfd = channel_->fd();
    loop_->run_in_loop(std::bind(&Connector::reset_channel, this));
    return sockfd;
}


void Connector::connecting(int sockfd){
    set_state(kConnecting);
    channel_.reset(new Channel(loop_, sockfd));
    channel_->set_write_callback(std::bind(&Connector::handle_write, this));
    printf("connecting func %s\n", __FUNCTION__);
    channel_->enable_writing();
    //::write(sockfd, "wm\n", 3);
}

void Connector::connect(){
    int sockfd = Socket::create_nonblocking();
    printf("before connect\n");
    int ret =Socket::connect(sockfd, (struct sockaddr *)&server_addr_);
    printf("after connect\n");
    printf("ret %d\n errorno: %d\n", ret, errno);
    perror("connect func errnod");
    int err = (ret == 0) ? 0 : errno;
    switch (err) {
        case 0:
        case EINPROGRESS:
        case EINTR:
        case EISCONN:
            printf("connecting\n");
            connecting(sockfd);
            break;
        default:
            ::close(sockfd);
    }
}

void Connector::handle_write(){
    printf("handle write\n");
    if (state_ == kConnecting) {
        int sockfd = remove_and_reset_channel();
        int err = Socket::get_socket_error(sockfd);
        if (err) {

        }
        else {
            set_state(kConnected);
            if(connect_){
                if(new_conn_callback_){
                    new_conn_callback_(sockfd);
                }
            }
            else{
                ::close(sockfd);
            }
        }
    }
}

void Connector::handle_error(){
    if( state_ == kConnecting ){
        int sockfd = remove_and_reset_channel();
    }
}
