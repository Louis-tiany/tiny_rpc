/*
    * File     : HttpServer.h
    * Author   : *
    * Mail     : *
    * Creation : Wed 30 Dec 2020 03:31:20 PM CST
*/

#ifndef _HTTPSERVER_H
#define _HTTPSERVER_H
#include "EventLoop.h"
#include "TcpServer.h"
#include "HttpContext.h"
#include "HttpResponse.h"
#include <string>
typedef std::function<void(const HttpRequest&, HttpResponse*)> HttpCallback;

class HttpServer{

public:
    HttpServer(EventLoop *loop, std::string ip, int port);
    ~HttpServer();

    void set_http_callback(HttpCallback http_callback){
        http_callback_ = std::move(http_callback);
    }
    void start();

private:
    void on_connection(const TcpConnectionPrt &conn);
    void on_message(const TcpConnectionPrt &conn, std::string &buf);
    void on_request(const TcpConnectionPrt &conn, const HttpRequest &request);


private:
    TcpServer server_;
    HttpCallback http_callback_;
};



#endif
