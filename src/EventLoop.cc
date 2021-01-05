/*
	* File     : EventLoop.cc
	* Author   : *
	* Mail     : *
	* Creation : Fri 25 Dec 2020 08:40:49 PM CST
*/

#include <iostream>
#include "../include/EventLoop.h"


EventLoop::EventLoop() : 
    loop_(false),
    poller(new Poller()),
    timer_queue_(new TimerQueue(this))
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
            printf("active_channels_.size: %lu\n", active_channels_.size());
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

TimerID EventLoop::run_at(TimeStamp time, TimerCallback cb){
    return timer_queue_->add_timer(std::move(cb), time, 0.0);
}


TimerID EventLoop::run_after(double delay, TimerCallback cb){
    TimeStamp time(add_time(TimeStamp::now(), delay));
    return run_at(time, std::move(cb));
}


TimerID EventLoop::run_every(double interval, TimerCallback cb){
    TimeStamp time(TimeStamp::now());
    return timer_queue_->add_timer(std::move(cb), time, interval);
}
void EventLoop::cancel_timer(TimerID timer_id){
    timer_queue_->cancel(timer_id);
}
