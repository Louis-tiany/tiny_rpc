/*
	* File     : TcpClient.h
	* Author   : *
	* Mail     : *
	* Creation : Tue 29 Dec 2020 04:48:19 PM CST
*/

#ifndef _TCPCLIENT_H
#define _TCPCLIENT_H
#include "Connector.h"
#include "TcpConnection.h"
#include <memory>
#include <string>

typedef std::shared_ptr<Connector> ConnectorPtr;

typedef std::shared_ptr<TcpConnection> TcpConnectionPrt;
class TcpClient {
public:
    typedef std::function<void(const TcpConnectionPrt &)>  ConnectionCallback;
    typedef std::function<void(const TcpConnectionPrt &)>  CloseCallback;
    //write complete callback
    typedef std::function<void(const TcpConnectionPrt &)>  WriteCallback;
    typedef std::function<void(const TcpConnectionPrt &, char *buf)>  MessageCallback;
public:
    TcpClient(EventLoop *loop, std::string ip, int port);
    ~TcpClient();

    void connect();
    void disconnect();
    void stop();

    TcpConnectionPrt connection() { return connection_; }

    void set_message_callback(const MessageCallback &message_callback)
    { message_callback_ = message_callback; }
    void set_write_callback(const WriteCallback &write_callback)
    { write_callback_ = write_callback; }
    void set_conn_callback(const ConnectionCallback conn_callback)
    { connection_callback_ = conn_callback; }

private:
    void new_connection(int sockfd);
    void remove_connection(const TcpConnectionPrt &conn);


private:
    EventLoop *loop_;
    std::string ip_;
    int port_;
    ConnectorPtr connector_;
    bool connect_;

    TcpConnectionPrt connection_;

    ConnectionCallback connection_callback_;
    MessageCallback message_callback_;
    WriteCallback write_callback_;
};


#endif
