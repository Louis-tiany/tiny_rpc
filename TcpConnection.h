/*
	* File     : TcpConnection.h
	* Author   : *
	* Mail     : *
	* Creation : Fri 25 Dec 2020 10:04:36 PM CST
*/

#ifndef _TCPCONNECTION_H
#define _TCPCONNECTION_H
#include "Channel.h"
#include "EventLoop.h"

#include "Socket.h"
#include <functional>
#include <memory>

class TcpConnection : public std::enable_shared_from_this<TcpConnection>{
public:


    typedef std::shared_ptr<TcpConnection> TcpConnectionPrt;
    typedef std::function<void(const TcpConnectionPrt &)>  ConnectionCallback;
    typedef std::function<void(const TcpConnectionPrt &)>  CloseCallback;
    //write complete callback
    typedef std::function<void(const TcpConnectionPrt &)>  WriteCallback;
    typedef std::function<void(const TcpConnectionPrt &, char *buf)>  MessageCallback;

    TcpConnection(EventLoop *loop, int sockfd);

    int fd() const { return socket_->fd(); }

    void set_channel_index(int index) { channel_->set_index(index); }
    void set_conn_callback(ConnectionCallback &cb){ connection_callback_ = cb; }
    void set_write_callback(WriteCallback &cb) { write_callback_ = cb; }
    void set_close_callback(const CloseCallback &cb) { close_callback_ = cb; }
    void set_message_callback(MessageCallback message_callback) { message_callback_ = message_callback; }
    void conn_established();

    char *InputBuffer() { return &input_buffer_[0]; }
    char *OutputBuffer() { return &output_buffer_[0]; }


    void handle_read();
    void handle_write();
    void handle_close();


    void send(void *data, size_t len);
    void send_in_loop(void *data, size_t len);
    void connection_destroy();
private:
    enum StateE { kDisconnected, kConnecting, kConnected, kDisconnecting };
    void set_state(StateE state) { state_ = state; }



private:
    EventLoop *loop_;
    bool reading_;
    StateE state_;

    std::unique_ptr<Socket> socket_;
    std::unique_ptr<Channel> channel_;

    ConnectionCallback connection_callback_;
    WriteCallback write_callback_;
    CloseCallback close_callback_;
    MessageCallback message_callback_;


    char input_buffer_[1024];
    char output_buffer_[1024];
};


#endif
