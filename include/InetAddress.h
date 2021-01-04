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

private:
    struct sockaddr_in addr_;
};
#endif
