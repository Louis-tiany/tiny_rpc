/*
	* File     : Serilazation.cc
	* Author   : *
	* Mail     : *
	* Creation : Wed 30 Dec 2020 09:42:18 AM CST
*/


#include <iostream>
#include <cstdlib>
#include <string>
#include <unistd.h>
#include <sstream>
#include <string.h>
class A{

public:
    A() {  }
    A(int index, int val, std::string name):
        index_(index),
        val_(val),
        buf_(new char[sizeof(A)])
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
        ss << index_ << "," << val_;
        ss >> buf_;
        printf("%s\n", buf_);
        return buf_;
    }

    static A* deserilaze(char *instance){
        std::stringstream ss(instance);
        A *a = new A();

        printf("%d\n", std::stoi(instance++));
        printf("%d\n", std::stoi(++instance));

        ss >> a->index_;
        ss >> a->val_;
        return a;
    }



private:
    int index_;
    int val_; 
    char *buf_;
};



int main(int argc, char *argv[])
{
    A a(1, 22, "a");
    char *instance = a.serilaze();

    A *b = A::deserilaze(instance);

    
    return 0;
}


