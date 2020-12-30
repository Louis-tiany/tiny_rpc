/*
	* File     : EventLoop.h
	* Author   : *
	* Mail     : *
	* Creation : Fri 25 Dec 2020 07:00:53 PM CST
*/

#ifndef _EVENTLOOP_H
#define _EVENTLOOP_H
#include <functional>
#include <vector>
#include <memory>
#include "Poller.h"
#include "Channel.h"

class EventLoop{
    typedef std::function<void()> Functor;
    public:
        EventLoop();
        void loop();

        void update_channel(Channel *channel);

        void run_in_loop(Functor cb);


        void remove_channel(Channel *channel);

public:
        std::unique_ptr<Poller> poller;
    private:
        bool loop_;
        std::vector<Channel *> active_channels_;
        Channel *current_channel_;
};

#endif
