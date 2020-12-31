/*
	* File     : httpserver_test.cc
	* Author   : *
	* Mail     : *
	* Creation : Thu 31 Dec 2020 12:12:27 PM CST
*/

#include <iostream>
#include <string>
#include "HttpResponse.h"
#include "HttpServer.h"
#include "HttpRequest.h"


void on_request(const HttpRequest &request, HttpResponse *response){
    std::cout << "header content:" << std::endl;
    if(request.path() == "/"){
        printf("send content to browser\n");
        response->set_state_code(HttpResponse::k200Ok);
        response->set_state_message("OK");
        response->set_content_type("text/plain");
        response->add_header("Server","MyServer");
        response->set_body("{\"msg\":\"hello world\"}");
    }
}


int main(int argc, char *argv[])
{
    EventLoop loop;
    HttpServer server(&loop, "0.0.0.0", 8888);

    server.set_http_callback(on_request);

    server.start();
    loop.loop();
    return 0;
}
