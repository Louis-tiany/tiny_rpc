/*
	* File     : Serilazer.h
	* Author   : *
	* Mail     : *
	* Creation : Tue 15 Dec 2020 02:54:37 PM CST
*/

#ifndef _SERILAZER_H
#define _SERILAZER_H
#include <iostream>
#include <string>
#include <unistd.h>
#include <sstream>
#include <string.h>
class A{

public:
    A() {  }
    A(int index, int val):
        index_(index),
        val_(val),
        buf_(new char[64])
    { 
        memset(buf_, '\0', sizeof(buf_));
    }
    ~A(){
        if(buf_){
            delete[]  buf_;
        }
    }

    char* serilaze(){
        std::stringstream ss;
        ss << index_ << ","<< val_;
        ss >> buf_;
        std::cout << buf_ << std::endl;
        return buf_;
    }
    static A* deserilaze(char *instance){
        std::stringstream ss(instance);
        A *a = new A();

        int index = std::stoi(instance++);
        int val =std::stoi(++instance);

        a->index_ = index;
        a->val_ = val;
        return a;
    }

public:
    int index_;
    int val_; 
    char *buf_;
};


#endif
