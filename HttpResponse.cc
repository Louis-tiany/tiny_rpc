/*
	* File     : HttpResponse.cc
	* Author   : *
	* Mail     : *
	* Creation : Thu 31 Dec 2020 10:49:42 AM CST
*/

#include <cstdio>
#include <iostream>
#include "HttpResponse.h"



void HttpResponse::append_buffer(std::string &output) const {
    char buf[32] = {'\0'};
    std::snprintf(buf, sizeof(buf), "HTTP/1.1 %d", state_);
    output.append(buf);

    output.append(state_message_);
    output.append("\r\n");

    if(close_connection_){
        output.append("Connection: close\r\n");
    }
    else{
        std::snprintf(buf, sizeof(buf), "Connection-Length%zd\r\n", body_.size());
        output.append(buf);
        output.append("Connection: Keep-Alive\r\n");
    }
    
    for(const auto &header : headers_){
        output.append(header.first);
        output.append( ": " );
        output.append(header.second);
        output.append("\r\n");
    }
    output.append("\r\n");
    output.append(body_);
}

