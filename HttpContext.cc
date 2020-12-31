/*
	* File     : HttpContext.cc
	* Author   : *
	* Mail     : *
	* Creation : Wed 30 Dec 2020 08:59:37 PM CST
*/

#include <algorithm>
#include <iostream>
#include <string.h>
#include "HttpContext.h"

const char HttpContext::kCRLF[] = "\r\n";

bool HttpContext::parse_request_line(const char *begin, const char *end){
    bool success = false;
    const char *start = begin;
    const char *space = std::find(start, end, ' ');

    if (space != end && request_.set_method(start, space)) {
        start = space + 1;
        space = std::find(start, end, ' ');
        if(space != end){
            const char *question = std::find(start, space, '?');
            if (question != space) {
                request_.set_path(start, question);
                request_.set_query(question, space);
            }
            else {
                request_.set_path(start, space);
            }
            start = space + 1;
            success = end - start == 8 && std::equal(start, end - 1, "HTTP/1.");
            if(success){
                if (*(end - 1) == '1') {
                    request_.set_version(HttpRequest::kHttp11);
                }
                else if(*(end - 1) == '0'){
                    request_.set_version(HttpRequest::kHttp10);
                }
                else{
                    success = false;
                }
            }
        }
    }

    printf("parse request line : %s\n", request_.path().c_str());
    return success;
}

bool HttpContext::parse_request(const char *buf){
    bool ok = true;
    bool has_more = true;
    int len = strlen(buf);
    const char *start = buf;
    const char *end = buf + len;
    while (has_more) {
        if (state_ == kExpectRequestLine) {
            const char *crlf = find_crlf(start, end);
            if (crlf) {
                ok = parse_request_line(start, crlf);
                if(ok){
                    start = crlf + 2;
                    state_ = kExpectHeaders;
                    printf("parse request line complete\n");
                }
                else {
                    has_more = false;
                }
            }
            else {
                has_more = false;
            }
        }
        else if(state_ == kExpectHeaders){
            printf("parse request header\n");
            printf("start:\n%s\n", start);
            const char *crlf = find_crlf(start, end);
            if (crlf) {
                const char *colon = std::find(start, crlf, ':');
                if(colon != crlf){
                    request_.add_header(start, colon, crlf);
                }
                else {
                    state_ = kGotAll;
                    has_more = false;
                }
                start = crlf + 2;
            }
        }
        else if(state_ == kExpectBody){

        }
    }

    printf("headers size %lu\n", request_.headers().size());
    for(auto &item : request_.headers()){
        printf("%s: %s\n", item.first.c_str(), item.second.c_str());
    }
    return ok;
}


