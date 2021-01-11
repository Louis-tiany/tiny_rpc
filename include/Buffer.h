/*
    * File     : include/Buffer.h
    * Author   : *
    * Mail     : *
    * Creation : Sat 09 Jan 2021 01:08:11 PM CST
*/

#ifndef BUFFER_H
#define BUFFER_H
#include <algorithm>
#include <bits/stdint-intn.h>
#include <string>
#include <vector>
#include <string.h>
#include "Socket.h"

class Buffer{
public:
    static const std::size_t kCheapPrepend = 8;
    static const std::size_t kInitialSize = 1024;

    explicit Buffer(size_t initial_size = kInitialSize) : 
        buffer_(kCheapPrepend + initial_size),
        reader_index_(kCheapPrepend),
        writer_index_(kCheapPrepend)
    {  }
        

    void swap(Buffer &rhs){
        buffer_.swap(rhs.buffer_);
        std::swap(reader_index_, rhs.reader_index_);
        std::swap(writer_index_, rhs.writer_index_);
    }

    size_t readable_bytes() const {
        return writer_index_ - reader_index_;
    }

    size_t writable_bytes() const {
        return buffer_.size() - writer_index_;
    }

    size_t prependable_bytes() const {
        return reader_index_;
    }

    const char* peek() const {
        return begin() + reader_index_;
    }


    const char* find_crlf() const {
        const char *crlf = std::search(peek(), begin_write(), kCRLF, kCRLF + 2);
        return crlf == begin_write() ? nullptr : crlf;
    }

    const char* find_crlf(const char *start) const {
        const char *crlf = std::search(start, begin_write(), kCRLF, kCRLF + 2);
        return crlf == begin_write() ? nullptr : crlf;
    }

    const char* find_eol() const {
        const void *eol = memchr(peek(), '\n', readable_bytes());
        return static_cast<const char *>(eol);
    }

    const char* find_eol(const char *start) const {
        const void *eol = memchr(start, '\n', begin_write() - start);
        return static_cast<const char *>(eol);
    }

    void retrieve(size_t len){
        if (len < readable_bytes()) {
            reader_index_ += len;
        }
        else {
            retrieve_all();
        }
    }

    void retrieve_until(const char *end){
        retrieve(end - peek());
    }

    void retrieve_int64(){
        retrieve(sizeof(int64_t));
    }

    void retrieve_all(){
        reader_index_ = kCheapPrepend;
        writer_index_ = kCheapPrepend;
    }

    std::string retrieve_all_as_string(){
        return retrieve_all_as_string(readable_bytes());
    }

    std::string retrieve_all_as_string(size_t len){
        std::string result(peek(), len);
        retrieve(len);
        return result;
    }

    void append(const std::string &s){
        append(s.c_str(), s.size());
    }

    void append(const char *data, size_t len){
        ensure_writable_bytes(len);
        std::copy(data, data + len, begin_write());
        has_writen(len);
    }

    void append(const void *data, size_t len){
        append(static_cast<const char*>(data), len);
    }

    void ensure_writable_bytes(size_t len){
        if (writable_bytes() < len) {
            make_space(len);
        }
    }

    void has_writen(size_t len){
        writer_index_ += len;
    }

    void unwrite(size_t len){
        writer_index_ -= len;
    }

    void append_int64(int64_t x){
        int64_t network64 = Socket::host_to_network64(x);
        append(&network64, sizeof(int64_t));
    }

    void append_int32(int32_t x){
        int32_t network32 = Socket::host_to_network32(x);
        append(&network32, sizeof(int32_t));
    }

    void append_int16(int16_t x){
        int16_t network16 = Socket::host_to_network16(x);
        append(&network16, sizeof(int16_t));
    }

    void append_int8(int8_t x){
        append(&x, sizeof(int8_t));
    }

    
    int64_t read_int64(){
        int64_t result = peek_int64();
        return result;
    }

    int32_t read_int32(){
        int32_t result = peek_int32();
        return result;
    }

    int16_t read_int16(){
        int16_t result = peek_int16();
        return result;
    }

    int8_t read_int8(){
        int8_t result = peek_int8();
        return result;
    }

    int64_t peek_int64() const {
        int64_t network64 = 0;
        ::memcpy(&network64, peek(), sizeof(int64_t));
        return Socket::network_to_host64(network64);
    }

    int32_t peek_int32() const {
        int32_t network32 = 0;
        ::memcpy(&network32, peek(), sizeof(int32_t));
        return Socket::network_to_host32(network32);
    }

    int16_t peek_int16() const {
        int16_t network16 = 0;
        ::memcpy(&network16, peek(), sizeof(int16_t));
        return Socket::network_to_host16(network16);
    }

    int8_t peek_int8() const {
        int8_t network8 = *peek();
        return network8;
    }

    void prepend(const void *data, size_t len){
        reader_index_ -= len;
        const char *d = static_cast<const char *>(data);
        std::copy(d, d + len, begin() + reader_index_);
    }

    void prepend_int64(int64_t x){
        int64_t network64 = Socket::host_to_network64(x);
        prepend(&network64, sizeof(int64_t));
    }

    void prepend_int32(int32_t x){
        int32_t network32 = Socket::host_to_network32(x);
        prepend(&network32, sizeof(int32_t));
    }

    void prepend_int16(int16_t x){
        int16_t network16 = Socket::host_to_network16(x);
        prepend(&network16, sizeof(int16_t));
    }

    void prepend_int8(int8_t x){
        prepend(&x, sizeof(int8_t));
    }


    void shrink(size_t reserve){
        Buffer other;
        other.ensure_writable_bytes(readable_bytes() + reserve);
        swap(other);
    }

    size_t internal_capacity() const {
        return buffer_.capacity();
    }

    ssize_t read_fd(int fd, int *saved_error);

    char *begin() {
        return &*buffer_.begin();
    }

    const char *begin() const {
        return &*buffer_.begin();
    }

    char *begin_write(){
        return begin() + writer_index_;
    }

    const char* begin_write() const {
        return begin() + writer_index_;
    }
private:
    void make_space(size_t len){
        if(writable_bytes() + prependable_bytes() < len + kCheapPrepend){
            buffer_.resize(writer_index_ + len);
        }
        else{
            size_t readable = readable_bytes();
            std::copy(begin() + reader_index_, begin() + writer_index_, begin() + kCheapPrepend);
            reader_index_ = kCheapPrepend;
            writer_index_ = reader_index_ + readable;
        }
    }




private:
    std::vector<char> buffer_;
    size_t reader_index_;
    size_t writer_index_;

    static const char kCRLF[];
};

#endif
