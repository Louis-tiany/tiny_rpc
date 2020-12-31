/*
    * File     : TcpServer.cc
    * Author   : *
    * Mail     : *
    * Creation : Fri 25 Dec 2020 10:02:50 PM CST
*/
#include <iostream>
#include "TcpServer.h"
#include <functional>
#include <memory>
#include "Socket.h"
TcpServer::TcpServer(EventLoop *loop):
    loop_(loop),
    acceptor_(new Acceptor(loop)),
    connection_callback_()
{ 
    acceptor_->set_new_conn_callback(std::bind(&TcpServer::new_conn, this, std::placeholders::_1));
    acceptor_->get_channel()->set_index(-1);
}


void TcpServer::start(){
    loop_->run_in_loop(std::bind(&Acceptor::listen,acceptor_.get()));
    loop_->poller->update_channel(acceptor_->get_channel());
}


void TcpServer::new_conn(int sockfd){
    std::cout << "new conn in tcpserver" << std::endl;
    TcpConnectionPrt conn(new TcpConnection(loop_, sockfd));
    connections_[sockfd] = conn;

    conn->set_message_callback(message_callback_);
    conn->set_conn_callback(connection_callback_);
    conn->set_write_callback(write_callback_);
    conn->set_close_callback(std::bind(&TcpServer::remove_conn, this, std::placeholders::_1));
    loop_->run_in_loop(std::bind(&TcpConnection::conn_established, conn));
}

void TcpServer::remove_conn(const TcpConnectionPrt &conn){
    remove_conn_inloop(conn);
}

void TcpServer::remove_conn_inloop(const TcpConnectionPrt &conn){
    connections_.erase(conn->fd());
    loop_->run_in_loop(std::bind(&TcpConnection::connection_destroy, conn));
}


