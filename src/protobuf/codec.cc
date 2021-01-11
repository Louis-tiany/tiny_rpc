/*
	m* File     : codec.cc
	* Author   : *
	* Mail     : *
	* Creation : Fri 08 Jan 2021 03:12:30 PM CST
*/

#include <bits/stdint-intn.h>
#include <google/protobuf/message_lite.h>
#include <google/protobuf/stubs/port.h>
#include <iostream>
#include "codec.h"
#include <string>
#include <zlib.h>

void ProtobufCodec::fill_empty_buffer(Buffer *buf, const google::protobuf::Message &message){
    const std::string &type_name = message.GetTypeName();
    int32_t name_len = static_cast<int32_t>(type_name.size() + 1);
    buf->append_int32(name_len);
    buf->append(type_name.c_str(), name_len);

    int byte_len = google::protobuf::internal::ToIntSize(message.ByteSizeLong());
    buf->ensure_writable_bytes(byte_len);

    uint8_t  *start = reinterpret_cast<uint8_t  *>(buf->begin_write());
    uint8_t  *end = message.SerializeWithCachedSizesToArray(start);
    if (end - start != byte_len) {

    }

    buf->has_writen(byte_len);

    int32_t check_sum = static_cast<int32_t>(::adler32(1, 
                                                       reinterpret_cast<const Bytef *>(buf->peek()), 
                                                       static_cast<int>(buf->readable_bytes())));
    buf->append_int32(check_sum);
    int32_t len = Socket::host_to_network32(static_cast<int32_t>(buf->readable_bytes()));
    printf("client send message len1111: %d\n", Socket::network_to_host32(len));
    buf->prepend(&len, sizeof(int32_t));
    printf("client send message len: %ld\n", buf->readable_bytes());
}

void ProtobufCodec::default_error_callback(const TcpConnectionPrt &conn, const Buffer *buf, ErrorCode error_code){
    printf("error\n");
    if (conn && conn->connected()) {
        conn->shutdown();
    }
}


int32_t as_int32(const char *buf){
    int32_t host32 = 0;
    ::memcpy(&host32, buf, sizeof(int32_t));
    return Socket::network_to_host32(host32);
}


void ProtobufCodec::on_message(const TcpConnectionPrt &conn, Buffer &buf){
    printf("server on message\n %d\n", __LINE__);
    printf("buffer readable_bytes %ld\n", buf.readable_bytes());
    while (buf.readable_bytes() >= kMinMessageLen + kHeaderLen) {
        const int32_t len = buf.peek_int32();
        printf("server on message\n %d\n", __LINE__);
        printf("message len: %d and kMinMessageLen : %d\n", len, kMinMessageLen);
        if(len > kMaxMessageLen || len < kMinMessageLen){
            error_callback_(conn, &buf, ErrorCode::kInvalid);
            break;
        }
        else if(buf.readable_bytes() >= static_cast<size_t>(kHeaderLen + len)){
            printf("server on message\n %d\n", __LINE__);
            ErrorCode code;
            MessagePtr message = parse(buf.peek() + kHeaderLen, len, &code);
            if(code == ErrorCode::kNoError && message){
                message_callback_(conn, message);
                buf.retrieve(kHeaderLen + len);
            }
            else{
                error_callback_(conn, &buf, code);
                break;
            }
        }
        else{
            break;
        }
    }
}



google::protobuf::Message* ProtobufCodec::create_message(const std::string &type_name){
    google::protobuf::Message *message = nullptr;
    const google::protobuf::Descriptor *descriptor = 
        google::protobuf::DescriptorPool::generated_pool()->FindMessageTypeByName(type_name);
    if (descriptor) {
        const google::protobuf::Message *prototype = 
            google::protobuf::MessageFactory::generated_factory()->GetPrototype(descriptor);
        if(prototype){
            message = prototype->New();
        }
    }
    return message;
}

MessagePtr ProtobufCodec::parse(const char *buf, int len, ErrorCode *error_code){
    MessagePtr message;

    int32_t check_sum_expected = as_int32(buf + len - kHeaderLen);
    int32_t check_sum = static_cast<int32_t>(::adler32(1, 
                                                       reinterpret_cast<const Bytef *>(buf),
                                                       static_cast<int>(len - kHeaderLen)));
    if (check_sum == check_sum_expected) {
        int32_t name_len = as_int32(buf);
        if (name_len > 2 && name_len < len - 2*kHeaderLen) {
            std::string type_name(buf + kHeaderLen, buf + kHeaderLen + name_len - 1);
            message.reset(create_message(type_name));
            if (message) {
                const char *data = buf + kHeaderLen + name_len;
                int32_t data_len = len - name_len - 2*kHeaderLen;
                if (message->ParseFromArray(data, data_len)) {
                    *error_code = ErrorCode::kNoError;
                }
                else {
                    *error_code = ErrorCode::kParseError;
                }
            }
            else {
                *error_code = ErrorCode::kUnknowMessageType;
            }
        }
        else {
            *error_code = ErrorCode::kInvalid;
        }
    }
    else{
        *error_code = ErrorCode::kCheckSumError;
    }
    return message;
}

