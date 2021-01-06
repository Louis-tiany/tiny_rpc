/*
    * File     : httpserver_test.cc
    * Author   : *
    * Mail     : *
    * Creation : Thu 31 Dec 2020 12:12:27 PM CST
*/

#include <iostream>
#include <string>
#include "../include/HttpResponse.h"
#include "../include/HttpServer.h"
#include "../include/HttpRequest.h"


void on_request(const HttpRequest &request, HttpResponse *response){
    std::cout << "header content:" << std::endl;
    if(request.path() == "/"){
        printf("send content to browser\n");
        response->set_state_code(HttpResponse::k200Ok);
        response->set_state_message("OK");
        response->set_content_type("Application/json");
        response->add_header("Server","MyServer");
        response->set_body("{\"msg\":\"hello world\"}");
    }
    else{
        response->set_state_code(HttpResponse::k404NotFound);
        response->set_state_message("Not Found");
        response->set_close_connection(true);
    }
}


int main(int argc, char *argv[])
{
    InetAddress addr("0.0.0.0", 8888);
    EventLoop loop;
    HttpServer server(&loop, addr);

    server.set_http_callback(on_request);

    server.start();
    loop.loop();
    return 0;
}
