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
    int _socketTimeout; //milliseconds
    std::function<void(TPayload &payload)> _onMessage;
    std::unique_ptr<std::thread> _eventListenerThread;
    std::unique_ptr<zmq::socket_t> _socketSUB;
    std::atomic<bool> _isRunning;

    void RunReceive() {
        while (_isRunning) {
            zmq::multipart_t msg;
            if (msg.recv(*_socketSUB)) {
                std::string payload = std::string(static_cast<char *>(msg.at(1).data()), msg.at(1).size());
                Focus::Event event;
                if (!event.ParseFromString(payload))
                    continue;
                _onMessage(event);
            }
        }
    }

    void RunReceiveEnvelope() {
        while (_isRunning) {
            zmq::multipart_t msg;
            if (msg.recv(*_socketSUB)) {
                std::string payload = std::string(static_cast<char *>(msg.at(1).data()), msg.at(1).size());
                Focus::Envelope envelope;
                if (!envelope.ParseFromString(payload))
                    continue;
                _onMessage(envelope);
            }
        }
    }

    void RunReceiveMessage() {
        while (_isRunning) {
            zmq::multipart_t msg;
            if (msg.recv(*_socketSUB)) {
                std::string payload = std::string(static_cast<char *>(msg.at(1).data()), msg.at(1).size());
                _onMessage(payload);
            }
        }
    }

public:
    FocusEventListener() : _socketTimeout(1000),
                           _onMessage(),
                           _eventListenerThread(),
                           _socketSUB(std::make_unique<zmq::socket_t>(*FocusSocket::Context, ZMQ_SUB)),
                           _isRunning(false) {
        _socketSUB->connect("inproc:///tmp/EventEmitter");
        _socketSUB->setsockopt(ZMQ_RCVTIMEO, &_socketTimeout, sizeof(_socketTimeout));
    }

    virtual ~FocusEventListener() {
        if (_isRunning) {
            _isRunning = false;
            _eventListenerThread->detach();
        }
        _socketSUB->close();
    }

    void Register(const std::string &payloadType, const std::function<void(TPayload &)> onMessage) {
        _socketSUB->setsockopt(ZMQ_SUBSCRIBE, payloadType.c_str(), payloadType.size());
        _onMessage = onMessage;
        _isRunning = true;
        _eventListenerThread = std::make_unique<std::thread>(std::bind(&FocusEventListener::RunReceive, this));
    }

    void RegisterEnvelope(const std::string &payloadType, const std::function<void(TPayload &)> onMessage) {
        _socketSUB->setsockopt(ZMQ_SUBSCRIBE, payloadType.c_str(), payloadType.size());
        _onMessage = onMessage;
        _isRunning = true;
        _eventListenerThread = std::make_unique<std::thread>(std::bind(&FocusEventListener::RunReceiveEnvelope, this));

    }

    void RegisterMessage(const std::string &payloadType, const std::function<void(TPayload &)> onMessage) {
        _socketSUB->setsockopt(ZMQ_SUBSCRIBE, payloadType.c_str(), payloadType.size());
        _onMessage = onMessage;
        _isRunning = true;
        _eventListenerThread = std::make_unique<std::thread>(std::bind(&FocusEventListener::RunReceiveMessage, this));
    }
};


#endif //FOCUS_CLIENT_FOCUSEVENTLISTENER_HPP