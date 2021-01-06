/*
	* File     : src/InetAddress.cc
	* Author   : *
	* Mail     : *
	* Creation : Sun 03 Jan 2021 10:25:43 PM CST
*/

#include <iostream>
#include <string.h>
#include <arpa/inet.h>

#include "../include/InetAddress.h"



InetAddress::InetAddress(std::string ip, std::uint16_t port):
    ip_(ip),
    port_(port)
{
    ::bzero(&addr_, sizeof(addr_));
    addr_.sin_family = AF_INET;
    addr_.sin_port = htons(port);
    addr_.sin_port = ::inet_pton(AF_INET, ip.c_str(), &addr_.sin_addr);
}
