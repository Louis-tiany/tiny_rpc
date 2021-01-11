/*
	* File     : codec.h
	* Author   : *
	* Mail     : *
	* Creation : Fri 08 Jan 2021 03:12:24 PM CST
*/

#ifndef _CODEC_H
#define _CODEC_H

#include <cstdint>
#include <functional>
#include <google/protobuf/message.h>
#include <memory>
#include <string>
#include "../../include/TcpConnection.h"
#include "../../include/TcpServer.h"


using MessagePtr = std::shared_ptr<google::protobuf::Message>;

class ProtobufCodec{

public:
    enum class ErrorCode{ 
        kNoError = 0, kInvalid, kCheckSumError, kInvalidNameLen, kUnknowMessageType, kParseError 
    };

    using ProtobufMessageCallback = std::function<void(const TcpConnection::TcpConnectionPrt &, const MessagePtr&)>;
    using ErrorCallback = std::function<void(const TcpConnection::TcpConnectionPrt &, const Buffer*, ErrorCode)>;


    explicit ProtobufCodec(const ProtobufMessageCallback &message_callback):
        message_callback_(message_callback),
        error_callback_(default_error_callback)
    {  }

    ProtobufCodec(const ProtobufMessageCallback &message_callback, const ErrorCallback &error_callback):
        message_callback_(message_callback),
        error_callback_(error_callback)
    {  }


    void on_message(const TcpConnectionPrt &conn, Buffer &buf);
    void send(const TcpConnectionPrt &conn, const google::protobuf::Message &message){
        Buffer buf;
        fill_empty_buffer(&buf, message);
        conn->send((void *)buf.peek(), buf.readable_bytes());
    }

    static void fill_empty_buffer(Buffer *buf, const google::protobuf::Message &message);
    static google::protobuf::Message* create_message(const std::string &type_name);
    static MessagePtr parse(const char *buf, int len, ErrorCode *error_code);



private:
    static void default_error_callback(const TcpConnectionPrt &conn, const Buffer *buf, ErrorCode error_code);


    ProtobufMessageCallback message_callback_;
    ErrorCallback error_callback_;

    const static int kHeaderLen = sizeof(std::int32_t);
    const static int kMinMessageLen = 2 * kHeaderLen + 2;
    const static int kMaxMessageLen = 64 * 1024 * 1024;
};




#endif
