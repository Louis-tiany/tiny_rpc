/*
    * File     : TcpServer.h
    * Author   : *
    * Mail     : *
    * Creation : Fri 25 Dec 2020 09:57:01 PM CST
*/

#ifndef _TCPSERVER_H
#define _TCPSERVER_H

#include "EventLoop.h"

#include "TcpConnection.h"
#include "Acceptor.h"
#include <memory>
typedef std::shared_ptr<TcpConnection> TcpConnectionPrt;
typedef std::function<void(const TcpConnectionPrt &)>  ConnectionCallback;
typedef std::function<void(const TcpConnectionPrt &)>  CloseCallback;
typedef std::function<void(const TcpConnectionPrt &)>  WriteCallback;
typedef std::function<void(const TcpConnectionPrt &, std::string &buf)>  MessageCallback;
typedef std::map<int ,TcpConnectionPrt > ConnectionMap;
class TcpServer{

public:
    
    TcpServer(EventLoop *loop);

    void start();

    void set_message_callback(const MessageCallback &message_callback)
    { message_callback_ = message_callback; }
    void set_connection_callback(const ConnectionCallback &connection_callback)
    { connection_callback_ = connection_callback; }
    void set_write_callabck(const WriteCallback &write_callback)
    { write_callback_ = write_callback; }

private:
    void new_conn(int sockfd);
    void remove_conn(const TcpConnectionPrt &conn);
    void remove_conn_inloop(const TcpConnectionPrt &conn);


private:

private:
    EventLoop *loop_;
    std::unique_ptr<Acceptor> acceptor_;

    ConnectionCallback connection_callback_;
    WriteCallback write_callback_;
    MessageCallback message_callback_;
    CloseCallback close_callback_;


    ConnectionMap connections_;

};


#endif
