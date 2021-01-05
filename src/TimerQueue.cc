/*
    * File     : src/TimerQueue.cc
    * Author   : *
    * Mail     : *
    * Creation : Mon 04 Jan 2021 04:38:14 PM CST
*/

#include <algorithm>
#include <cstdlib>
#include <functional>
#include <iostream>
#include "../include/TimerQueue.h"
#include "../include/EventLoop.h"
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <sys/timerfd.h>
#include <utility>
#include <vector>

//timer static num
//can't define in header file
//multiple define if in header file init
int64_t Timer::num_ = 0;

int create_timer_fd(){
    int timer_fd = ::timerfd_create(CLOCK_MONOTONIC, TFD_NONBLOCK | TFD_CLOEXEC);
    if(timer_fd < 0){
        abort();
    }
    return timer_fd;
}

struct timespec how_much_time_from_now(TimeStamp when){
    int64_t micro_seconds = when.micro_seconds_since_epoch() - TimeStamp::now().micro_seconds_since_epoch();

    printf("micro_seconds diff %ld \n", micro_seconds);

    if (micro_seconds < 100) {
        micro_seconds = 100;
    }

    struct timespec ts;

    ts.tv_sec = static_cast<time_t>(micro_seconds / TimeStamp::k_microsecond_per_second);
    ts.tv_nsec = static_cast<long>((micro_seconds % TimeStamp::k_microsecond_per_second) * 1000);
    return ts;
}

void read_timer_fd(int timer_fd, TimeStamp now){
    u_int64_t howmany;
    ssize_t n = ::read(timer_fd, &howmany, sizeof(howmany));
    if(n != sizeof howmany){
        printf("read timerfd n != howmany\n");
    }
    printf("read timer fd %s\n", now.to_format_string().c_str());
    (void)n;
}

void reset_timer_fd(int timer_fd, TimeStamp expiration){
    struct itimerspec new_value;
    struct itimerspec old_value;

    bzero(&new_value, sizeof(itimerspec));
    bzero(&old_value, sizeof(itimerspec));

    new_value.it_value = how_much_time_from_now(expiration);
    int ret = ::timerfd_settime(timer_fd, 0, &new_value, &old_value);
    (void)ret;
}

TimerQueue::TimerQueue(EventLoop *loop):
    loop_(loop),
    timer_fd_(create_timer_fd()),
    timer_fd_channel_(loop_, timer_fd_),
    timers_(),
    calling_expired_timer_(false)
{  
    timer_fd_channel_.set_read_callback(std::bind(&TimerQueue::handle_read, this));
    timer_fd_channel_.enable_reading();
}


TimerQueue::~TimerQueue(){
    timer_fd_channel_.disable_all();
    ::close(timer_fd_);
    for (const Entry& timer : timers_){
        delete timer.second;
    }
}


TimerID TimerQueue::add_timer(TimerCallback cb, TimeStamp when, double interval){
    Timer *timer = new Timer(std::move(cb), when, interval);
    loop_->run_in_loop(std::bind(&TimerQueue::add_timer_in_loop, this, timer));
    return TimerID(timer, timer->sequence());
}


void TimerQueue::cancel(TimerID timer_id){
    loop_->run_in_loop(std::bind(&TimerQueue::cancel_timer_in_loop, this, timer_id));
}



void TimerQueue::add_timer_in_loop(Timer *timer){
    bool changed = insert(timer);
    if (changed) {
        printf("changed timers fd\n");
        reset_timer_fd(timer_fd_, timer->expiration());
    }
}

void TimerQueue::cancel_timer_in_loop(TimerID timer_id){

    ActiveTimer timer = ActiveTimer(timer_id.timer(), timer_id.sequence());
    ActiveTimerSet::iterator it = active_timers_.find(timer);
    if(it != active_timers_.end()){
        size_t n = timers_.erase(Entry(it->first->expiration(), it->first));
        (void)n;
        delete it->first;
        active_timers_.erase(it);
    }
    else if(calling_expired_timer_){
        canceling_timers_.insert(timer);
    }
}



void TimerQueue::handle_read(){
    TimeStamp now(TimeStamp::now());
    read_timer_fd(timer_fd_, now);

    std::vector<Entry> expired = get_expired(now);

    calling_expired_timer_ = true;
    canceling_timers_.clear();

    for(const auto &it : expired){
        it.second->run();
    }
    calling_expired_timer_ = false;

    reset(expired, now);
}



std::vector<TimerQueue::Entry> TimerQueue::get_expired(TimeStamp now){
    std::vector<Entry> expired;
    Entry sentry(now, (Timer *)UINTPTR_MAX);

    TimerList::iterator end = timers_.lower_bound(sentry);
    
    std::copy(timers_.begin(), end, std::back_inserter(expired));

    timers_.erase(timers_.begin(), end);

    for(const Entry &it : expired){
        ActiveTimer timer(it.second, it.second->sequence());
        size_t n = active_timers_.erase(timer);
        (void)n;
    }
    return expired;
}


void TimerQueue::reset(const std::vector<Entry> &expired, TimeStamp now){
    TimeStamp next_expire;
    for(const Entry &it : expired){
        ActiveTimer timer(it.second, it.second->sequence());
        if(it.second->repeat() && canceling_timers_.find(timer) == canceling_timers_.end()){
            it.second->restart(now);
            insert(it.second);
        }
        else{
            delete it.second;
        }
    }

    if(!timers_.empty()){
        next_expire = timers_.begin()->second->expiration();
    }

    if(next_expire.valid()){
        reset_timer_fd(timer_fd_, next_expire);
    }
}



bool TimerQueue::insert(Timer *timer){
    bool changed = false;
    TimeStamp when = timer->expiration();

    TimerList::iterator it = timers_.begin();

    if(it == timers_.end() || when < it->first){
        changed = true;
    }

    timers_.insert(Entry(when, timer));
    active_timers_.insert(ActiveTimer(timer, timer->sequence()));
    return changed;
}


