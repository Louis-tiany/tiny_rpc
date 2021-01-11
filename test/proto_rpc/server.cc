/*
    * File     : test/proto_rpc/server.cc
    * Author   : *
    * Mail     : *
    * Creation : Sun 10 Jan 2021 03:44:03 PM CST
*/

#include <functional>
#include <iostream>
#include <memory>
#include "../../include/protobuf/codec.h"
#include "../../include/protobuf/dispatcher.h"

#include "../../include/TcpServer.h"
#include "../../include/EventLoop.h"
#include "./proto/query.pb.h"

using QueryPtr = std::shared_ptr<rpc::Query>;
using AnswerPtr = std::shared_ptr<rpc::Answer>;


class QueryServer{
public:
    QueryServer(EventLoop *loop, const InetAddress addr):
        server_(loop, addr),
        dispather_(std::bind(&QueryServer::on_unknowed_message, this, std::placeholders::_1, std::placeholders::_2)),
        codec_(std::bind(&ProtobufDispather::on_protobuf_message, &dispather_, std::placeholders::_1, std::placeholders::_2))
    {  
        dispather_.register_message_callback<rpc::Query>(std::bind(&QueryServer::on_query, this, std::placeholders::_1, std::placeholders::_2));
        dispather_.register_message_callback<rpc::Answer>(std::bind(&QueryServer::on_answer, this, std::placeholders::_1, std::placeholders::_2));
        server_.set_connection_callback(std::bind(&QueryServer::on_connection, this, std::placeholders::_1));
        server_.set_message_callback(std::bind(&ProtobufCodec::on_message, &codec_, std::placeholders::_1, std::placeholders::_2));
    }


    void start(){
        server_.start();
    }


private:
    void on_connection(const TcpConnectionPrt &conn){

    }

    void on_unknowed_message(const TcpConnectionPrt &conn, const MessagePtr &message){

    }

    void on_query(const TcpConnectionPrt &conn, const MessagePtr &message){
        printf("receive query %s\n", message->GetTypeName().c_str());
        rpc::Answer answer;
        answer.set_id(1);
        answer.set_questioner("louis");
        answer.set_answerer("proto rpc");
        answer.add_solution("gogogo");
        answer.add_solution("yyyyy");
        codec_.send(conn, answer);
        conn->shutdown();
    }


    void on_answer(const TcpConnectionPrt &conn, const AnswerPtr &message){
        conn->shutdown();
    }


private:
    TcpServer server_;
    ProtobufDispather dispather_;
    ProtobufCodec codec_;
};


int main(int argc, char *argv[])
{
    EventLoop loop;
    InetAddress addr("0.0.0.0",9999);
    QueryServer server(&loop, addr);
    server.start();
    loop.loop();
    return 0;
}
