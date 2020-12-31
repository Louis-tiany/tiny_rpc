/*
	* File     : HttpRequest.h
	* Author   : *
	* Mail     : *
	* Creation : Wed 30 Dec 2020 09:04:13 PM CST
*/

#ifndef _HTTPREQUEST_H
#define _HTTPREQUEST_H
#include <iostream>
#include <string>
#include <map>

class HttpRequest{
    
public:
    enum Method { kInvalid, kGet, kPost, kPut, kDelete };
    enum Version { kUnknowed, kHttp10, kHttp11 };

public:
    HttpRequest():
        method_(kInvalid),
        version_(kUnknowed)
    {  }
        
    void set_version(Version version) { version_ = version; }
    Version get_version() const { return version_; }
    bool set_method(const char *start, const char *end){
        std::string m(start, end);
        if ( m == "GET" ){
            method_ = kGet;
        }
        else if (m == "POST") {
            method_ = kPost;
        }
        else if (m == "PUT") {
            method_ = kPut;
        }
        else if (m == "DELETE") {
            method_ = kDelete;
        }
        else {
            method_ = kInvalid;
        }
        return method_ != kInvalid;
    }


    void set_path(const char *start, const char *end){
        path_.assign(start, end);
    }

    const std::string& path() const {
        return path_;
    }


    void set_query(const char *start, const char *end){
        query_.assign(start, end);
    }
    const std::string& query() const {
        return query_;
    }

    void add_header(const char *start, const char *colon, const char *end){
        std::string field(start, colon);
        ++colon;
        while (colon < end && std::isspace(*colon)) {
            ++colon;
        }
        std::string val(colon, end);
        while (!val.empty() && std::isspace(val[val.size() - 1])) {
            val.resize(val.size() - 1);
        }
        headers_[field] = val;
    }

    std::string get_header(const std::string &field) const {
        std::string res; 
        auto iter = headers_.find(field);
        if(iter != headers_.end()){
            res = iter->second;
        }
        return res;
    }

    const std::map<std::string, std::string>& headers() const {
        return headers_;
    }

private:
        Method method_;
        Version version_;

        std::string path_;
        std::string query_;
        std::map<std::string, std::string> headers_;

};



#endif
