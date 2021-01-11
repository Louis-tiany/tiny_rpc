/*
	* File     : client.cc
	* Author   : *
	* Mail     : *
	* Creation : Sun 10 Jan 2021 08:00:23 PM CST
*/

#include <functional>
#include <iostream>

#include "../../include/TcpClient.h"
#include "../../include/EventLoop.h"

#include "../../include/protobuf/codec.h"
#include "../../include/protobuf/dispatcher.h"

#include "proto/query.pb.h"

using EmptyPtr = std::shared_ptr<rpc::Empty>;
using AnswerPtr = std::shared_ptr<rpc::Answer>;

google::protobuf::Message *message_to_send = nullptr;

class QueryClient{
public:
    QueryClient(EventLoop *loop, const InetAddress addr) : 
        loop_(loop),
        client_(loop, addr),
        dispatcher_(std::bind(&QueryClient::on_unknowed_message, this, std::placeholders::_1, std::placeholders::_2)),
        codec_(std::bind(&ProtobufDispather::on_protobuf_message, &dispatcher_, std::placeholders::_1, std::placeholders::_2))
    {
        dispatcher_.register_message_callback<rpc::Answer>(std::bind(&QueryClient::on_answer, this, std::placeholders::_1, std::placeholders::_2));
        dispatcher_.register_message_callback<rpc::Empty>(std::bind(&QueryClient::on_empty, this, std::placeholders::_1, std::placeholders::_2));

        client_.set_conn_callback(std::bind(&QueryClient::on_connection, this, std::placeholders::_1));
        client_.set_message_callback(std::bind(&ProtobufCodec::on_message, &codec_, std::placeholders::_1, std::placeholders::_2));
    }

    void connect(){
        client_.connect();
    }

private:
    void on_connection(const TcpConnectionPrt &conn){
        if(conn->connected()){
            printf("send message, %s %ld\n", message_to_send->GetTypeName().c_str(), message_to_send->ByteSizeLong());
            codec_.send(conn, *message_to_send);
        }
        else{

        }
    }

    void on_unknowed_message(const TcpConnectionPrt &conn, const MessagePtr &message){
        printf("message type %s \n", message->GetTypeName().c_str());
    }

    void on_answer(const TcpConnectionPrt &conn, const AnswerPtr &message){
        printf("rpc message from server%s\n", message->DebugString().c_str());
    }

    void on_empty(const TcpConnectionPrt &conn, const EmptyPtr &message){

    }

private:
    EventLoop *loop_;
    TcpClient client_;
    ProtobufDispather dispatcher_;
    ProtobufCodec codec_;
};

int main(int argc, char *argv[])
{

    int32_t n = 1;
    n = Socket::host_to_network32(n);
    printf("2conversion : %x\n", Socket::network_to_host32(n));
    printf("1conversion : %x\n", n);


    EventLoop loop;
    InetAddress addr("127.0.0.1", 9999);
    
    rpc::Query query;
    query.set_id(1);
    query.set_questioner("kkkk");
    query.add_question("who?");

    rpc::Empty empty;
    message_to_send = &query;

    QueryClient client(&loop, addr);
    client.connect();
    loop.loop();


    return 0;
}

