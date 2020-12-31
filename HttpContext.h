/*
	* File     : HttpContext.h
	* Author   : *
	* Mail     : *
	* Creation : Wed 30 Dec 2020 08:59:34 PM CST
*/

#ifndef _HTTPCONTEXT_H
#define _HTTPCONTEXT_H
#include <iostream>
#include <algorithm>
#include "HttpRequest.h"


class HttpContext{

public:
    enum HttpRequestParseState { kExpectRequestLine, kExpectHeaders, kExpectBody, kGotAll, };


public:
    HttpContext():
        state_(kExpectRequestLine)
    {  }

    const HttpRequest request() const {
        return request_;
    }
    HttpRequest request() {
        return request_;
    }

    bool parse_request(const char *buf);
    bool got_all() const { return state_ == kGotAll; }
private:
    bool parse_request_line(const char *begin, const char *end);
    const char *find_crlf(const char *begin, const char *end) const {
        const char *crlf = std::search(begin, end, kCRLF, kCRLF + 2);
        return crlf == end ? nullptr : crlf;
    }
private:
    static const char kCRLF[];
    HttpRequestParseState state_;
    HttpRequest request_;
};

#endif
