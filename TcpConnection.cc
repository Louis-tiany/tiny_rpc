/*
	* File     : TcpConnection.cc
	* Author   : *
	* Mail     : *
	* Creation : Fri 25 Dec 2020 10:04:51 PM CST
*/

#include <cstdlib>
#include <functional>
#include <iostream>
#include "TcpConnection.h"

TcpConnection::TcpConnection(EventLoop *loop, int sockfd) : 
    loop_(loop),
    socket_(new Socket(sockfd)),
    channel_(new Channel(loop, sockfd))
{
    channel_->set_read_callback(std::bind(&TcpConnection::handle_read, this));
    channel_->set_write_callback(std::bind(&TcpConnection::handle_write, this));
    channel_->set_close_callback(std::bind(&TcpConnection::handle_close, this));

    socket_->set_keep_alive(true);
}

void TcpConnection::send(void *data, size_t len){
    if(state_ == kConnected){
        send_in_loop(data,len);
    }
}


void TcpConnection::send_in_loop(void *data, size_t len){
    size_t remaining = len;
    bool fault_err = false;

    ssize_t wrote_num = 0;

    if (state_ == kDisconnected) {
        return;
    }
    
    if(!channel_->is_writing()){
        wrote_num = socket_->write(data, len);
    }
}

void TcpConnection::handle_read(){
    memset(input_buffer_, 0, 1024);
    int n = socket_->read(input_buffer_, 1024);
    if(n > 0){
        //std::cout << input_buffer_ << std::endl;
        message_callback_(shared_from_this(), input_buffer_);
    }
    else if(n == 0){
        handle_close();
        std::cout << "0 to read" << std::endl;
    }
    else{

    }
}


void TcpConnection::handle_write(){
    if(channel_->is_writing()){
        if(write_callback_){
            write_callback_(shared_from_this());
        }
        channel_->disable_writing();
    }
}

void TcpConnection::handle_close(){
    set_state(kDisconnected);
    channel_->disable_all();
    if(close_callback_){
        printf("close event\n");
        close_callback_(shared_from_this());
    }
}

void TcpConnection::connection_destroy(){
    if(state_ == kConnected){
        channel_->disable_all();
    }

}

void TcpConnection::conn_established(){
    channel_->set_read_callback(std::bind(&TcpConnection::handle_read, this));
    channel_->set_write_callback(std::bind(&TcpConnection::handle_write, this));
    channel_->set_close_callback(std::bind(&TcpConnection::handle_close, this));
    set_state(kConnected);
    channel_->enable_reading();
    if(connection_callback_){
        connection_callback_(shared_from_this());
    }
    printf("%s : new conn enable_reading\n", __FUNCTION__);
}


