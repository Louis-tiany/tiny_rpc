/*
	* File     : Socket.h
	* Author   : *
	* Mail     : *
	* Creation : Fri 25 Dec 2020 07:34:31 PM CST
*/

#ifndef _SOCKET_H
#define _SOCKET_H
#define MAXQUEUE 100
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string>
#include <iostream>
#include <fcntl.h>

class EventLoop;
class Channel;

class Socket{
public:
    explicit Socket(int fd) : 
        sockfd_(fd)
    {  }
    ~Socket(){
        ::close(sockfd_);
        printf("close fd %d\n", sockfd_);
    }
    static int create_nonblocking(){
        int fd = ::socket(AF_INET, SOCK_STREAM| SOCK_NONBLOCK | SOCK_CLOEXEC, IPPROTO_TCP);
        return fd;
    }

    int fd() {
        return sockfd_;
    }


    void bind_addr(const std::string ip, int port){
        struct sockaddr_in addr;
        memset(&addr, 0, sizeof(addr));
        addr.sin_family = AF_INET;
        addr.sin_addr.s_addr = htonl(INADDR_ANY);
        addr.sin_port = htons(port);
        int ret = ::bind(sockfd_, (sockaddr *)&addr, sizeof(addr));
        if (ret == -1) {
            std::cerr << "bind error" <<std::endl;
        }
    }

    void listen(){
        int ret = ::listen(sockfd_, MAXQUEUE);
        printf("%d listening\n", sockfd_);
        if (ret == -1) {
            std::cerr << "bind error" <<std::endl;
        }
    }

    int accept(){
        socklen_t addr_len;
        memset(&addr_len, 0, sizeof( socklen_t ));
        memset(&addr_, 0, sizeof(addr_));
        printf("%d accepting\n", sockfd_);
        int conn = ::accept4(sockfd_, (struct sockaddr *)&addr_, &addr_len, SOCK_NONBLOCK | SOCK_CLOEXEC);
        std::cout << "accept:" << std::endl;
        std::cout << conn << std::endl;
        printf("errorno %d\n", errno);
        perror("accpet errno");
        return conn;
    }

    void set_reuse_addr(bool on){
        int opt = on ? 1 : 0;
        ::setsockopt(sockfd_, SOL_SOCKET, SO_REUSEPORT,
                     &opt, static_cast<socklen_t>(sizeof(opt)));
    }

    void set_reuse_port(bool on){
        int opt = on ? 1 : 0;
        ::setsockopt(sockfd_, SOL_SOCKET, SO_REUSEPORT,
                     &opt, static_cast<socklen_t>(sizeof(opt)));
    }

    void set_keep_alive(bool on){
        int opt = on ? 1 : 0;
        ::setsockopt(sockfd_, SOL_SOCKET, SO_KEEPALIVE,
                     &opt, static_cast<socklen_t>(sizeof(opt)));
    }

    void set_nonblock(){
        int flags = ::fcntl(sockfd_, F_SETFD, 0);
        flags |= O_NONBLOCK;
        int ret = ::fcntl(sockfd_, F_SETFL, flags);

        flags = ::fcntl(sockfd_, F_GETFD, 0);
        flags |= FD_CLOEXEC;
        ret = ::fcntl(sockfd_, F_SETFL, flags);
        (void)ret;
    }

    int read(void *buf, size_t count){
        return ::read(sockfd_, buf, count);
    }

    int write(const void *buf, size_t count){
        return ::write(sockfd_, buf, count);
    }

    static int connect(int sockfd, const struct sockaddr *addr){
        return ::connect(sockfd, addr, sizeof(sockaddr_in));
    }

    static int get_socket_error(int sockfd){
        int opt;
        socklen_t optlen = static_cast<socklen_t>(sizeof opt);
        if(::getsockopt(sockfd, SOL_SOCKET, SO_ERROR, &opt, &optlen) < 0){
            return errno;
        }
        else{
            return opt;
        }
    }

private:
    int sockfd_;
    struct sockaddr_in addr_;
};

#endif
