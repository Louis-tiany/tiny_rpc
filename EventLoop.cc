/*
	* File     : EventLoop.cc
	* Author   : *
	* Mail     : *
	* Creation : Fri 25 Dec 2020 08:40:49 PM CST
*/

#include <iostream>
#include "EventLoop.h"


EventLoop::EventLoop() : 
    loop_(false),
    poller(new Poller())
{
}



void EventLoop::loop(){
    loop_ = true;
    while (loop_) {
        std::cout << "before clear" << std::endl;
        active_channels_.clear();
        std::cout << "before poll" << std::endl;
        poller->poll(&active_channels_);
        std::cout << "event loop loop after poll" << std::endl;

        for(auto channel : active_channels_){
            current_channel_ = channel;
            std::cout << current_channel_->fd() << std::endl;
            std::cout << active_channels_.size() << std::endl;
            current_channel_->handle_event();
        }
        std::cout << "end one loop" << std::endl;
   }
}


void EventLoop::update_channel(Channel *channel){
    poller->update_channel(channel);
}

void EventLoop::run_in_loop(Functor cb){
    if(cb){
        cb();
    }
}


void EventLoop::remove_channel(Channel *channel){
    poller->remove_channel(channel);
}
