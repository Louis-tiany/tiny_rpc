/*
	* File     : CPLuginEnumerator.h
	* Author   : *
	* Mail     : *
	* Creation : Tue 08 Dec 2020 03:30:48 PM CST
*/

#ifndef _CPLUGINENUMERATOR_H
#define _CPLUGINENUMERATOR_H
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <string.h>
#include <dirent.h>
class  CPLuginEnumerator{
    public:
        CPLuginEnumerator() {  }
        virtual ~CPLuginEnumerator() {  }

        bool get_plugin_name(std::vector<std::string> &plugin_name){
            DIR *dir=opendir("./plugin");
            if(dir==nullptr){
                return false;
            }
            while(true){
                struct dirent *pentry=readdir(dir);
                if(pentry==nullptr){
                    break;
                }
                if(strcmp(pentry->d_name,".")==0){
                    continue;
                }
                if(strcmp(pentry->d_name,"..")==0){
                    continue;
                }

                std::string prefix="./plugin/";
                plugin_name.emplace_back(prefix+pentry->d_name);
            }
            return true;
        }
};



#endif
