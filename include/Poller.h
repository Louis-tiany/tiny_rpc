/*
	* File     : Poller.h
	* Author   : *
	* Mail     : *
	* Creation : Fri 25 Dec 2020 07:32:34 PM CST
*/

#ifndef _POLLER_H
#define _POLLER_H
#include <iostream>
#include <memory>
#include <ostream>
#include <string>
#include <vector>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>
#include <netinet/in.h>
#include <map>
#include <cstdlib>
#include <error.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <sys/poll.h>
#include <assert.h>

class Channel;

#define CONNECT_SIZE 100
class Poller{
    public:
        Poller();
        ~Poller();

        void poll(std::vector<Channel *> *active_channels){

            int nfd = ::epoll_wait(epoll_fd_, &(*events_.begin()), CONNECT_SIZE, -1);
            printf("%d channel: \n", nfd);
            assert(nfd != 0);
            if(nfd > 0){
                fill_active_events(active_channels, nfd);
            }
            else if(nfd == 0){

            }
            else{

            }
        }

        void update_channel(Channel *channel);
        void update(int operation, Channel *channel);

        void remove_channel(Channel *channel);

    private:
        void fill_active_events(std::vector<Channel *> *active_channels, int num);

    private:
        int epoll_fd_;
        int listen_socket_;
        struct epoll_event ev_;
        std::vector<struct epoll_event> events_;
        std::map<int, Channel *> channels_;
};
#endif
