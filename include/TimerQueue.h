/*
    * File     : include/TimerQueue.h
    * Author   : *
    * Mail     : *
    * Creation : Mon 04 Jan 2021 04:38:05 PM CST
*/

#ifndef TIMERQUEUE_H
#define TIMERQUEUE_H

#include "../include/Timer.h"
#include "../include/Channel.h"
#include <utility>
#include <set>
#include <vector>

class EventLoop;




class TimerQueue{
public:
    using Entry = std::pair<TimeStamp, Timer *>;

    explicit TimerQueue(EventLoop *loop);
    ~TimerQueue();

    TimerID add_timer(TimerCallback cb, TimeStamp when, double interval = 0.0);
    void cancel(TimerID timer_id);

private:
    using TimerList = std::set<Entry>;
    using ActiveTimer = std::pair<Timer *, int64_t>;
    using ActiveTimerSet = std::set<ActiveTimer> ;

    void add_timer_in_loop(Timer *timer);
    void cancel_timer_in_loop(TimerID timer_id);
    void handle_read();

    std::vector<Entry> get_expired(TimeStamp now);
    void reset(const std::vector<Entry> &expired, TimeStamp now);

    bool insert(Timer *timer);

    EventLoop *loop_;
    const int timer_fd_;
    Channel timer_fd_channel_;

    TimerList timers_;
    ActiveTimerSet active_timers_;
    bool calling_expired_timer_;
    ActiveTimerSet canceling_timers_;
};



#endif
