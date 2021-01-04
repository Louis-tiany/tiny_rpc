/*
	* File     : TcpClient.cc
	* Author   : *
	* Mail     : *
	* Creation : Tue 29 Dec 2020 04:48:23 PM CST
*/

#include <functional>
#include <iostream>
#include "../include/TcpClient.h"

TcpClient::TcpClient(EventLoop *loop, std::string ip, int port):
    loop_(loop),
    ip_(ip),
    port_(port),
    connector_(new Connector(loop, ip, port)),
    connect_(false)
{
    connector_->set_new_conn_callback(std::bind(&TcpClient::new_connection, this, std::placeholders::_1));
}

TcpClient::~TcpClient(){

}

void TcpClient::connect(){
    connect_ = true;
    connector_->start();
}

void TcpClient::disconnect(){
    connect_ = false;
    //should shutdown tcpconnection
}

void TcpClient::stop(){
    connect_ = false;
    connector_->stop();
}

void TcpClient::new_connection(int sockfd){
    TcpConnectionPrt conn(new TcpConnection(loop_, sockfd));
    conn->set_conn_callback(connection_callback_);
    conn->set_message_callback(message_callback_);
    conn->set_write_callback(write_callback_);
    conn->set_close_callback(std::bind(&TcpClient::remove_connection, this, std::placeholders::_1));
    printf("new conn\n %s", __FUNCTION__);
    
    connection_ = conn;
    conn->conn_established();
}

void TcpClient::remove_connection(const TcpConnectionPrt &conn){
    connection_.reset();
    loop_->run_in_loop(std::bind(&TcpConnection::connection_destroy, conn));
}

