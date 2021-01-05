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
#include "Timer.h"
#include "TimerQueue.h"

class EventLoop{
public:
typedef std::function<void()> Functor;
public:
        EventLoop();
        void loop();

        void update_channel(Channel *channel);

        void run_in_loop(Functor cb);

        void remove_channel(Channel *channel);

        TimerID run_at(TimeStamp time, TimerCallback cb);
        TimerID run_after(double delay, TimerCallback cb);
        TimerID run_every(double interval, TimerCallback cb);
        void cancel_timer(TimerID timer_id);

public:
        std::unique_ptr<Poller> poller;
private:
        std::unique_ptr<TimerQueue> timer_queue_;
        bool loop_;
        std::vector<Channel *> active_channels_;
        Channel *current_channel_;
};

#endif
