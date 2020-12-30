/*
	* File     : Channel.h
	* Author   : *
	* Mail     : *
	* Creation : Fri 25 Dec 2020 07:33:32 PM CST
*/

#ifndef _CHANNEL_H
#define _CHANNEL_H
#include <iostream>
#include <memory>
#include <ostream>
#include <string>
#include <vector>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>
#include <netinet/in.h>
#include <cstdlib>
#include <error.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <sys/poll.h>
#include <sys/types.h>
#include <assert.h>
#include <functional>


class EventLoop;
class Channel{
    static const int kNoneEvent;
    static const int kReadEvent;
    static const int kWriteEvent;
    public:
        typedef std::function<void(void)> ReadCallback; 
        typedef std::function<void(void)> WriteCallback; 
        typedef std::function<void(void)> CloseCallback; 

        Channel(EventLoop *loop, int fd):
            loop_(loop),
            fd_(fd),
            events_(0),
            revents_(0),
            index_(-1),
            events_handling_(false)
    {    }

        int fd() const { return fd_; }
        int events() const { return events_; }
        int index() const { return index_; }
        void set_index(int index) { index_ = index; }
        bool is_nonevent() const { return events_ == kNoneEvent; }
        void set_revent(int revents) { revents_ = revents; }

        void set_read_callback(ReadCallback read_callback){
            read_callback_ = std::move(read_callback);
        }

        void set_write_callback(WriteCallback write_callback){
            write_callback_ = std::move(write_callback);
        }

        void set_close_callback(CloseCallback close_callback){
            close_callback_ = std::move(close_callback);
        }

        void enable_reading() { events_ |= kReadEvent; update(); }
        void disable_reading() { events_ &= ~kReadEvent; update(); }
        void enable_writing() { events_ |= kWriteEvent; update(); }
        void disable_writing() { events_ &= ~kWriteEvent; update(); }
        void disable_all(){ disable_reading(); disable_writing(); }
        bool is_writing() const { return events_ & kWriteEvent; }
        bool is_reading() const { return events_ & kReadEvent; }
        void update();

        void remove();

        void handle_event(){
            std::cout << "channel call back" << std::endl;
            printf("revents_ %d\n", revents_);
            events_handling_ = true;
            if((revents_ & POLLHUP) && !(revents_ & POLLIN)){
                if(close_callback_){
                    printf("close_callback_\n");
                    close_callback_();
                }
            }
            if(revents_ & POLLNVAL){

            }
            if(revents_ & (POLLIN | POLLPRI | POLLRDHUP)){
                printf("read callback\n");
                if(read_callback_){
                    printf("do read callback\n");
                    read_callback_();
                    //open write callback
                    //enable_writing();
                }
            }
            if(revents_ & POLLOUT){
                if(write_callback_){
                    printf("write callback\n");
                    if (write_callback_) {
                        write_callback_();
                    }
                    printf("after write callback\n");
                }
            }
            events_handling_ = false;
        }

private:
        EventLoop *loop_;
        int fd_;
        int events_;
        int revents_;
        int index_;
        bool events_handling_;
        ReadCallback read_callback_;
        WriteCallback write_callback_;
        CloseCallback close_callback_;
};

#endif
