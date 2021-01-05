/*
	* File     : Timer.h
	* Author   : *
	* Mail     : *
	* Creation : Sun 03 Jan 2021 03:11:19 PM CST
*/

#ifndef _TIMER_H
#define _TIMER_H
#include <bits/types/time_t.h>
#include <inttypes.h>
#include <iostream>
#include <sys/time.h>
#include <functional>
#include <string>


class TimeStamp;
class Timer;

class TimerID{
public:
    TimerID():
        timer_(nullptr),
        sequence_(0)
    {  }

    TimerID(Timer *timer, int64_t sequence):
        timer_(timer),
        sequence_(sequence)
    {}

    Timer* timer() const { return timer_; }
    int64_t sequence() const { return sequence_; }
    
private:
    Timer *timer_;
    int64_t sequence_;
};





class TimeStamp{
public:
    TimeStamp():
        micro_seconds_since_epoch_(0)
    {  }

    TimeStamp(std::int64_t micro_seconds_since_epoch) :
        micro_seconds_since_epoch_(micro_seconds_since_epoch)
    {  }

    bool valid() const { return micro_seconds_since_epoch_ > 0; }

    int64_t micro_seconds_since_epoch() const { return micro_seconds_since_epoch_; }

    static const int k_microsecond_per_second = 1000 * 1000;

    static TimeStamp now() {
        struct timeval tv;
        gettimeofday(&tv, nullptr);
        int64_t seconds = tv.tv_sec;
        return TimeStamp(seconds * k_microsecond_per_second + tv.tv_usec);
    }
    static TimeStamp invalid(){
        return TimeStamp();
    }

    static TimeStamp from_unix_time(time_t t){
        return from_unix_time(t, 0);
    }

    static TimeStamp from_unix_time(time_t t, int micro_seconds){
        return TimeStamp(static_cast<int64_t>(t) * k_microsecond_per_second + micro_seconds);
    }

    std::string to_string() const {
        char buf[32] = { '\0' };

        int64_t seconds = micro_seconds_since_epoch_ / k_microsecond_per_second;
        int64_t micro_seconds = micro_seconds_since_epoch_ % k_microsecond_per_second;

        snprintf(buf, sizeof(buf), "%" PRId64 ".%06" PRId64 "", seconds, micro_seconds);

        return buf;
    }

    std::string to_format_string(){
        char buf[64] = { '\0' };
        time_t seconds = static_cast<time_t>(micro_seconds_since_epoch_ / k_microsecond_per_second);
        int micro_seconds = static_cast<int>(micro_seconds_since_epoch_ % k_microsecond_per_second);
        struct tm tm_time;
        ::gmtime_r(&seconds, &tm_time);

        snprintf(buf, sizeof(buf), "%4d%02d%02d %02d:%02d:%02d.%06d",
                 tm_time.tm_year + 1900, tm_time.tm_mon + 1, tm_time.tm_mday, 
                 tm_time.tm_hour, tm_time.tm_min, tm_time.tm_sec, micro_seconds);

        return buf;
    }



private:
        std::int64_t micro_seconds_since_epoch_;
};

inline bool operator < (TimeStamp lhs, TimeStamp rhs){
    return lhs.micro_seconds_since_epoch() < rhs.micro_seconds_since_epoch();
}

inline bool operator == (TimeStamp lhs, TimeStamp rhs){
    return lhs.micro_seconds_since_epoch() == rhs.micro_seconds_since_epoch();
}

inline TimeStamp add_time(TimeStamp timestamp, double seconds){
    int64_t delta = static_cast<int64_t>(seconds * TimeStamp::k_microsecond_per_second);
    return TimeStamp(timestamp.micro_seconds_since_epoch() + delta);
}



using TimerCallback = std::function<void(void)>;

class Timer{
public:
    Timer(TimerCallback cb, TimeStamp when, double interval = 0.0):
        timer_callback_(std::move(cb)),
        expiration_(when),
        interval_(interval),
        repeat_(interval_ > 0.0),
        sequence_(num_++)
    {  }

    bool repeat() const { return repeat_; }
    int64_t sequence() const { return sequence_; }
    TimeStamp expiration() const { return expiration_; }

    void run() const { timer_callback_(); }
    void restart(TimeStamp now){
        if (repeat_) {
            expiration_ = add_time(now, interval_);
        }
        else{
            expiration_ = TimeStamp::invalid();
        }
    }


private:
    const TimerCallback timer_callback_;
    TimeStamp expiration_;
    const double interval_;
    const bool repeat_;
    const int64_t sequence_;
    static int64_t num_;
};



#endif
