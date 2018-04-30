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
#include <atomic>
#include <iostream>

template<class TPayload>
class FocusEventListener {
private:
    int _socketTimeout = 1000; //milliseconds
    std::function<void(TPayload &payload)> _onMessage;
    std::unique_ptr<std::thread> _eventListenerThread;
    std::unique_ptr<zmq::socket_t> _socketSUB = std::make_unique<zmq::socket_t>(*FocusSocket::Context, ZMQ_SUB);
    std::atomic<bool> _isRunning;

    void RunReceive(zmq::socket_t *socketSUB, const std::function<void(TPayload &)> onMessage) {
        while (_isRunning) {
            zmq::message_t msg;
            if (socketSUB->recv(&msg)) {
                if (!socketSUB->recv(&msg))
                    continue;
                std::string payload = std::string(static_cast<char *>(msg.data()), msg.size());
                Focus::Event event;
                if (!event.ParseFromString(payload))
                    continue;
                onMessage(event);
            }
        }
    }

    void RunReceiveEnvelope(zmq::socket_t *socketSUB, const std::function<void(TPayload &)> onMessage) {
        while (_isRunning) {
            zmq::message_t msg;
            if (socketSUB->recv(&msg)) {
                if (!socketSUB->recv(&msg))
                    continue;
                std::string payload = std::string(static_cast<char *>(msg.data()), msg.size());
                Focus::Envelope envelope;
                if (!envelope.ParseFromString(payload))
                    continue;
                onMessage(envelope);
            }
        }
    }

    void RunReceiveMessage(zmq::socket_t *socketSUB, const std::function<void(TPayload &)> onMessage) {
        while (_isRunning) {
            zmq::message_t msg;
            if (socketSUB->recv(&msg)) {
                if (!socketSUB->recv(&msg))
                    continue;
                std::string payload = std::string(static_cast<char *>(msg.data()), msg.size());
                onMessage(payload);
            }
        }
    }

public:
    FocusEventListener() {
        _socketSUB->connect("inproc:///tmp/EventEmitter");
        _socketSUB->setsockopt(ZMQ_RCVTIMEO, &_socketTimeout, sizeof(_socketTimeout));
        _isRunning = true;
    }

    virtual ~FocusEventListener() {
        _isRunning = false;
        _eventListenerThread->join();
        _socketSUB->close();
    }

    void Register(const std::string &payloadType, const std::function<void(TPayload &)> onMessage) {
        _socketSUB->setsockopt(ZMQ_SUBSCRIBE, payloadType.c_str(), payloadType.size());
        _onMessage = onMessage;
        _eventListenerThread = std::make_unique<std::thread>(&FocusEventListener::RunReceive, this, _socketSUB.get(), _onMessage);
    }

    void RegisterEnvelope(const std::string &payloadType, const std::function<void(TPayload &)> onMessage) {
        _socketSUB->setsockopt(ZMQ_SUBSCRIBE, payloadType.c_str(), payloadType.size());
        _onMessage = onMessage;
        _eventListenerThread = std::make_unique<std::thread>(&FocusEventListener::RunReceiveEnvelope, this, _socketSUB.get(), _onMessage);
    }

    void RegisterMessage(const std::string &payloadType, const std::function<void(TPayload &)> onMessage) {
        _socketSUB->setsockopt(ZMQ_SUBSCRIBE, payloadType.c_str(), payloadType.size());
        _onMessage = onMessage;
        _eventListenerThread = std::make_unique<std::thread>(&FocusEventListener::RunReceiveMessage, this, _socketSUB.get(), _onMessage);
    }
};


#endif //FOCUS_CLIENT_FOCUSEVENTLISTENER_HPP