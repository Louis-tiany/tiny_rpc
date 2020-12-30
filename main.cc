/*
	* File     : main.cc
	* Author   : *
	* Mail     : *
	* Creation : Thu 17 Dec 2020 10:18:22 AM CST
*/

#include <iostream>
#include <string>
#include <string.h>



char* text_ = "GET /test HTTP/1.1\r\n\
Host: 59.110.63.1:8080\r\n\
Connection: keep-alive\r\n\
Cache-Control: max-age=0\r\n\
Upgrade-Insecure-Requests: 1\r\n\
User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/87.0.4280.88 Safari/537.36\r\n\
Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,image/apng,*/*;q=0.8,application/signed-exc9ange;v=b3;q=0.9\r\n\
Accept-Encoding: gzip, deflate\r\n\
Accept-Language: zh-CN,zh-TW;q=0.9,zh;q=0.8\r\n\
\r\n\
request body";


char *parse_request_head(char *request_head){
    if ( !request_head || strcmp(request_head,"\r\n") == 0 ){
        return nullptr;
    }
    
    char *key = request_head;
    char *val = strpbrk(request_head,":");
    if (!val) {
        return nullptr;
    }

    *val++ = '\0';
    char *next_line = strpbrk(val,"\r\n");
    *next_line = '\0';
    next_line +=2;
    std::cout << "key:" << key << std::endl;
    std::cout << "val:" << val << std::endl;
    return next_line;
}

int main(int argc, char *argv[])
{
    char text[1024];
    char *method;
    strcpy(text,text_);
    char *url = strpbrk(text, " ");
    *url = '\0';
    url++;
    method = text;

    char *version = strpbrk(url," ");
    *version++ = '\0';
    
    char *request_head = strpbrk(version,"\r\n");
    *request_head++ = '\0';
    request_head++;

    while (request_head) {
        request_head=parse_request_head(request_head);
    }

    


    std::cout << "===============================" << std::endl;
    std::cout << "method:" << method << std::endl;
    std::cout << "url:" << url << std::endl;
    std::cout << "version:" << version << std::endl;


    return 0;
}
