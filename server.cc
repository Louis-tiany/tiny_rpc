/*
 * File     : server.cc
 * Author   : *
 * Mail     : *
 * Creation : Sat 05 Dec 2020 04:24:28 PM CST
 */

#include <iostream>
#include <memory>
#include <ostream>
#include <string>
#include <vector>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>
#include <netinet/in.h>
#include <cstdlib>
#include <error.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <sys/poll.h>
#include <sys/types.h>
#include <assert.h>
#include <functional>

#include "EventLoop.h"




template<class ConnectionProcessor, class Poller = int>
class TcpServer : public ConnectionProcessor{
    public:
        TcpServer(int port,const char *ip=nullptr,int queue_len=100):
            ip_(nullptr),port_(port),queue_len_(queue_len)
    {
        if(ip!=nullptr){
            int len=strlen(ip);
            ip_=new char[len+1];
            strcpy(ip_,ip);
        }
    }
        virtual ~TcpServer(){
            if(ip_!=nullptr){
                delete [] ip_;
            }
        }

        void run(){
            int listen_socket=::socket(AF_INET,SOCK_STREAM,0);
            check_error(listen_socket);

            sockaddr_in server_addr;
            bzero(&server_addr,sizeof(sockaddr_in));

            server_addr.sin_family=AF_INET;
            if(ip_==nullptr){
                server_addr.sin_addr.s_addr=htonl(INADDR_ANY);
            }
            else{
                check_error(::inet_pton(AF_INET,ip_,&server_addr.sin_addr));
            }

            server_addr.sin_port=htons(port_);

            check_error(::bind(listen_socket,(sockaddr *)&server_addr,sizeof(sockaddr_in)));
            check_error(::listen(listen_socket,queue_len_));

            sockaddr_in client_addr;
            socklen_t client_addr_len;

            while (true) {
                int conn=::accept(listen_socket,(sockaddr *)&client_addr,&client_addr_len);

                ConnectionProcessor *processor=static_cast<ConnectionProcessor *>(this);
                processor->func(conn);
                close(conn);
            }
        }
    private:
        void check_error(int n){
            if(n==-1){
                abort();
            }
        }
    private:
        int port_;
        char *ip_;
        int queue_len_;
        Poller poller_;
};

class MyTcpServer{
    public:
        MyTcpServer() {}
        virtual ~MyTcpServer() {  }

        void func(int conn){
            char buf[1024];
            memset(buf,'\0',sizeof(buf));
            ::read(conn,buf,sizeof(buf));
            parse_request_line(buf);


            char *res = "HTTP/1.1 200 OK\n\
                         Date: Mon, 27 Jul 2009 12:28:53 GMT\n\
                         Server: Apache/2.2.14 (Win32)\n\
                         Last-Modified: Wed, 22 Jul 2009 19:15:56 GMT\n\
                         Content-Length: 88\n\
                         Content-Type: application/json\n\
                         Connection: Closed\
                         \r\n\r\n\
                         {\"msg\" : \"hello world\"}\0";

            ::write(conn, res, strlen(res));
        }

    private:
        int parse_request_line(char *text){
            std::cout << text << std::endl;
            url_ = strpbrk(text," ");

            //std::cout << url_ << std::endl;

            *url_++ = '\0';
            char *method = text;
            std::cout << url_ << std::endl;
            std::cout << method << std::endl;

            if (strcasecmp(method, "GET")) {
                method_ = Method::GET;
            }
            else if (strcasecmp(method,"POST")) {
                method_ = Method::POST;
            }
            else{

            }

            //url_ += strspn(url_," \t");

            version_ = strpbrk(url_," ");
            *version_++ = '\0';
            std::cout << version_ << std::endl;




        }

    private:
        char *url_;
        char *version_;

        enum Method { GET = 0,POST = 1 };
        Method method_;



};

int main(int argc, char *argv[])
{
    TcpServer<MyTcpServer> server(8080);
    server.run();

    return 0;
}

