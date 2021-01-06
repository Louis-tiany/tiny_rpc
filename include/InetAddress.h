/*
	* File     : InetAddress.h
	* Author   : *
	* Mail     : *
	* Creation : Sun 03 Jan 2021 03:50:56 PM CST
*/

#ifndef _INETADDRESS_H
#define _INETADDRESS_H
#include <iostream>
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>

class InetAddress{
public:
    InetAddress(std::string ip, std::uint16_t port);

    explicit InetAddress(const struct sockaddr_in &addr);

    const struct sockaddr* get_sock_addr() const {
        return ( struct sockaddr * )(&addr_);
    }


    const std::string ip() const { return ip_; }
    const uint16_t port() const { return port_; }



private:
    struct sockaddr_in addr_;
    std::string ip_;
    uint64_t port_;
};
#endif
