/*
    * File     : HttpServer.cc
    * Author   : *
    * Mail     : *
    * Creation : Wed 30 Dec 2020 03:31:24 PM CST
*/

#include <iostream>
#include <functional>
#include "../include/HttpContext.h"
#include "../include/HttpServer.h"

static char BadRequest[] = "HTTP/1.1 400 Bad Request\r\n\r\n";


HttpServer::HttpServer(EventLoop *loop, InetAddress addr):
    server_(loop, addr)
{
    server_.set_connection_callback(std::bind(&HttpServer::on_connection, this, std::placeholders::_1));
    server_.set_message_callback(std::bind(&HttpServer::on_message, this, std::placeholders::_1, std::placeholders::_2));
}

HttpServer::~HttpServer()
{

}


void HttpServer::start(){
    printf("http server start\n");
    server_.start();
}

void HttpServer::on_connection(const TcpConnectionPrt &conn){
    printf("a browser connection\n");
    if (conn->connected()) {
        HttpContext *context = new HttpContext();
        conn->set_context((void *)context);
    }
}

void HttpServer::on_message(const TcpConnectionPrt &conn, Buffer &buf){
    printf("on message callback\n");
    HttpContext *context = (HttpContext *)conn->get_context();
    const char *buffer = buf.peek();
    //printf("buff in buf \n%s\n", buf.c_str());
    if (!context->parse_request(buffer)) {
        conn->send(BadRequest, sizeof(BadRequest));
    }

    if(context->got_all()){
        printf("parse success\n");
        on_request(conn, context->request());
        //conn->shutdown();
    }
}

void HttpServer::on_request(const TcpConnectionPrt &conn, const HttpRequest &request){
    const std::string& connection = request.get_header("Connection");
    printf("request conn : %s\n", connection.c_str());
    bool close = connection == "close" ||
        (request.get_version() == HttpRequest::kHttp10 && connection != "keep-alive");
    printf("close status %d \n", close);
    HttpResponse response(close);
    http_callback_(request, &response);
    std::string buf;
    response.append_buffer(buf);
    conn->send((void *)buf.c_str(), buf.size());
    if(response.close_connection()){
        conn->shutdown();
    }
}
