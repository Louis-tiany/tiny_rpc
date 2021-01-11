/*
	* File     : test/proto_rpc/dispatcher.h
	* Author   : *
	* Mail     : *
	* Creation : Sun 10 Jan 2021 02:29:25 PM CST
*/

#ifndef DISPATCHER_H
#define DISPATCHER_H

#include <functional>
#include <google/protobuf/message.h>
#include <map>
#include <memory>
#include <type_traits>
#include "../../include/TcpConnection.h"
#include "../../include/TcpServer.h"

using MessagePtr = std::shared_ptr<google::protobuf::Message>;

class Callback{
public:
    virtual ~Callback() = default;
    virtual void on_message(const TcpConnectionPrt&, const MessagePtr&) const = 0;
};



template<class T>
class CallbackT : public Callback{
public:
    using ProtobufMessageTCallback = std::function<void (const TcpConnectionPrt&, const std::shared_ptr<T>& message)>;

    CallbackT(const ProtobufMessageTCallback &callback) :
        callback_(callback)
    {  }

    void on_message(const TcpConnectionPrt& conn, const MessagePtr& message) const override {
        std::shared_ptr<T> concrete = std::static_pointer_cast<T>(message);
        callback_(conn, concrete);
    }
private:
    ProtobufMessageTCallback callback_;
};

class ProtobufDispather{
public:
    using ProtobufMessageCallback = std::function<void (const TcpConnectionPrt&, const MessagePtr& message)>;
    explicit ProtobufDispather(const ProtobufMessageCallback &default_cb) :
        default_callback_(default_cb)
    {  }

    void on_protobuf_message(const TcpConnectionPrt &conn, const MessagePtr &message){
        CallbackMap::const_iterator it = callback_map_.find(message->GetDescriptor());
        if (it != callback_map_.end()){
            it->second->on_message(conn, message);
        }
        else {
            default_callback_(conn, message);
        }
    }

    template<class T>
    void register_message_callback(const typename CallbackT<T>::ProtobufMessageTCallback &callback){
        std::shared_ptr<CallbackT<T>> pd(new CallbackT<T>(callback));
        callback_map_[T::descriptor()] = pd;
    }

        

private:
    using CallbackMap = std::map<const google::protobuf::Descriptor *, std::shared_ptr<Callback>>;
    CallbackMap callback_map_;
    ProtobufMessageCallback default_callback_;
};




#endif
