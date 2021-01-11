/*
    * File     : src/Buffer.cc
    * Author   : *
    * Mail     : *
    * Creation : Sat 09 Jan 2021 01:08:24 PM CST
*/

#include <bits/types/struct_iovec.h>
#include <iostream>
#include "../include/Buffer.h"

const char Buffer::kCRLF[] = "\r\n";


ssize_t Buffer::read_fd(int fd, int *saved_error){
    char extrabuf[65536];
    struct iovec vec[2];
    const size_t writable = writable_bytes();

    vec[0].iov_base = begin() + writer_index_;
    vec[0].iov_len = writable;
    vec[1].iov_base = extrabuf;
    vec[1].iov_len = sizeof(extrabuf);
    const int iovcnt = (writable < sizeof extrabuf) ? 2 : 1;
    const ssize_t n = Socket::readv(fd, vec, iovcnt);
    if(n < 0){
        *saved_error = errno;
    }
    else if(static_cast<size_t>(n) <= writable){
        writer_index_ += n;
    }
    else{
        writer_index_ = buffer_.size();
        append(extrabuf, n - writable);
    }
    return n;
}
