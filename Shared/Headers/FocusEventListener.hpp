//
// Created by Etienne Pasteur on 17/10/2017.
//

#ifndef FOCUS_CLIENT_FOCUSEVENTLISTENER_HPP
#define FOCUS_CLIENT_FOCUSEVENTLISTENER_HPP

#include <string>
#include <functional>
#include <thread>
#include <FocusSocket.hpp>
#include <FocusEvent.pb.h>
#include <FocusEnvelope.pb.h>

template<class TPayload>
class FocusEventListener {
private:
    std::function<void(TPayload &payload)> _onMessage;
    std::unique_ptr<std::thread> _eventListenerThread;
    std::unique_ptr<zmq::socket_t> _socketSUB = std::make_unique<zmq::socket_t>(*FocusSocket::Context, ZMQ_SUB);

    static void RunReceive(zmq::socket_t *socketSUB, const std::function<void(TPayload &)> onMessage) {
        while (true) {
            zmq::message_t msg;
            socketSUB->recv(&msg);
            socketSUB->recv(&msg);
            std::string payload = std::string(static_cast<char*>(msg.data()), msg.size());
            Focus::Event event;
            if (!event.ParseFromString(payload))
                continue;
            onMessage(event);
        }
    }

    static void RunReceiveEnvelope(zmq::socket_t *socketSUB, const std::function<void(TPayload &)> onMessage) {
        while (true) {
            zmq::message_t msg;
            socketSUB->recv(&msg);
            socketSUB->recv(&msg);
            std::string payload = std::string(static_cast<char*>(msg.data()), msg.size());
            Focus::Envelope envelope;
            if (!envelope.ParseFromString(payload))
                continue;
            onMessage(envelope);
        }
    }

    static void RunReceiveMessage(zmq::socket_t *socketSUB, const std::function<void(TPayload &)> onMessage) {
        while (true) {
            zmq::message_t msg;
            socketSUB->recv(&msg);
            socketSUB->recv(&msg);
            std::string payload = std::string(static_cast<char*>(msg.data()), msg.size());
            onMessage(payload);
        }
    }

public:
    FocusEventListener() {
        _socketSUB->connect("inproc:///tmp/EventEmitter");
    }

    void Register(const std::string &payloadType, const std::function<void(TPayload &)> onMessage) {
        _socketSUB->setsockopt(ZMQ_SUBSCRIBE, payloadType.c_str(), payloadType.size());
        _onMessage = onMessage;
        _eventListenerThread = std::make_unique<std::thread>(RunReceive, _socketSUB.get(), _onMessage);
    }

    void RegisterEnvelope(const std::string &payloadType, const std::function<void(TPayload &)> onMessage) {
        _socketSUB->setsockopt(ZMQ_SUBSCRIBE, payloadType.c_str(), payloadType.size());
        _onMessage = onMessage;
        _eventListenerThread = std::make_unique<std::thread>(RunReceiveEnvelope, _socketSUB.get(), _onMessage);
    }

    void RegisterMessage(const std::string &payloadType, const std::function<void(TPayload &)> onMessage) {
        _socketSUB->setsockopt(ZMQ_SUBSCRIBE, payloadType.c_str(), payloadType.size());
        _onMessage = onMessage;
        _eventListenerThread = std::make_unique<std::thread>(RunReceiveMessage, _socketSUB.get(), _onMessage);
    }
};


#endif //FOCUS_CLIENT_FOCUSEVENTLISTENER_HPP