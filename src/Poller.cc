/*
	* File     : Poller.cc
	* Author   : *
	* Mail     : *
	* Creation : Fri 25 Dec 2020 08:50:48 PM CST
*/

#include <cstdio>
#include <iostream>
#include <sys/epoll.h>
#include "../include/Poller.h"
#include "../include/Channel.h"


const int kNew = -1;
const int kAdded = 1;
const int kDeleted = 2;


Poller::Poller() : 
    epoll_fd_(::epoll_create1(EPOLL_CLOEXEC)),
    events_(32)
{

}

Poller::~Poller(){
    ::close(epoll_fd_);
}

void Poller::update_channel(Channel *channel){
    int index = channel->index();
    int fd = channel->fd();
    printf("ctl channel %d channel index: %d \n", channel->fd(), channel->index());
        
    if(index == kNew || index == kDeleted){
        if(index == kNew){
            channels_[fd] = channel;
        }
        else{

        }
        channel->set_index(kAdded);
        update(EPOLL_CTL_ADD, channel);
        printf("ctl add channel %d\n", channel->fd());
    }
    else{
        int fd = channel->fd();
        if(channel->is_nonevent()){
            update(EPOLL_CTL_DEL, channel);
            channel->set_index(kDeleted);
            printf("ctl del channel %d\n", channel->fd());
        }
        else{
            update(EPOLL_CTL_MOD, channel);
        }
    }
}

void Poller::remove_channel(Channel *channel){
    int fd = channel->fd();
    int index = channel->index();
    
    size_t n = channels_.erase(fd);
    (void)n;

    if(index == kAdded){
        update(EPOLL_CTL_DEL, channel);
    }
    channel->set_index(kNew);
}



void Poller::fill_active_events(std::vector<Channel *> *active_channels, int num){
    for(int i = 0; i < num; ++i){
        Channel *channel = static_cast<Channel *>(events_[i].data.ptr);
        channel->set_revent(events_[i].events);
        active_channels->push_back(channel);
    }
}

void Poller::update(int operation, Channel *channel){
    struct epoll_event event;
    memset(&event, 0, sizeof event);
    event.events = channel->events();
    event.data.ptr = channel;

    int fd = channel->fd();

    if(::epoll_ctl(epoll_fd_, operation, fd, &event) < 0){
        std::cout << "epoll do operation" << std::endl;
        std::cout << operation << std::endl;
    }
    else{

    }
}
