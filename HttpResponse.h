/*
    * File     : HttpResponse.h
    * Author   : *
    * Mail     : *
    * Creation : Thu 31 Dec 2020 10:49:35 AM CST
*/

#ifndef _HTTPRESPONSE_H
#define _HTTPRESPONSE_H

#include <map>
#include <string>
class HttpResponse{
public:
    enum HttpResponseState{ kUnknown, k200Ok = 200, k301MovePermanently = 301, k400BadRequest = 400, k404NotFound = 404, };

    explicit HttpResponse(bool close):
        state_(kUnknown)
    {  }

    void set_state_code(HttpResponseState code){
        state_ = code;
    }

    void set_state_message(const std::string &message){
        state_message_ = message;
    }
    
    void set_close_connection(bool on){
        close_connection_ = on;
    }

    bool close_connection() const {
        return close_connection_;
    }

    void set_content_type(const std::string &content_type){
        add_header("Content-Type", content_type);
    }

    void add_header(const std::string &key, const std::string &val){
        headers_[key] = val;
    }

    void set_body(const std::string &body){
        body_ = body;
    }

    void append_buffer(std::string &output) const ;



private:
    std::map<std::string, std::string> headers_;
    HttpResponseState state_;
    std::string state_message_;
    bool close_connection_;
    std::string body_;

};



#endif
