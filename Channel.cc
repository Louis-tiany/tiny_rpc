/*
	* File     : Channel.cc
	* Author   : *
	* Mail     : *
	* Creation : Fri 25 Dec 2020 07:56:44 PM CST
*/

#include <iostream>
#include "Channel.h"
#include "EventLoop.h"
const int Channel::kNoneEvent = 0;
const int Channel::kReadEvent = POLLIN | POLLPRI;
const int Channel::kWriteEvent = POLLOUT;
void Channel::update(){
    loop_->update_channel(this);
}

void Channel::remove(){
    loop_->remove_channel(this);
}

