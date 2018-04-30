//
// Created by Etienne Pasteur on 17/10/2017.
//

#include <FocusEventManager.hpp>
#include <iostream>
#include <spdlog/spdlog.h>

FocusEventManager::FocusEventManager() {
    _isRunning = true;
    _socketPUB = std::make_unique<zmq::socket_t>(*FocusSocket::Context, ZMQ_PUB);
    _socketSUB = std::make_unique<zmq::socket_t>(*FocusSocket::Context, ZMQ_SUB);
}

void FocusEventManager::Run() {
    spdlog::get("logger")->info("FocusEventManager is running");

    _socketPUB->bind("inproc:///tmp/EventEmitter");
    _socketSUB->bind("inproc:///tmp/EventListener");
    _socketSUB->setsockopt(ZMQ_SUBSCRIBE, "", 0);

    _eventManagerThread = std::make_unique<std::thread>(std::bind(&FocusEventManager::RunReceive, this));
}

void FocusEventManager::RunReceive() const {
    while (_isRunning) {
        zmq::multipart_t rep;
        zmq::message_t msg;
        _socketSUB->recv(&msg);
        std::string ret = std::string(static_cast<char*>(msg.data()), msg.size());
        rep.addstr(ret);
        zmq::message_t msg2;
        _socketSUB->recv(&msg2);
        ret = std::string(static_cast<char*>(msg2.data()), msg2.size());
        rep.addstr(ret);
        rep.send(*_socketPUB, 0);
    }
}

FocusEventManager::~FocusEventManager() {
    _isRunning = false;
    _eventManagerThread->join();
    spdlog::get("logger")->info("FocusEventManager is shutting down");
}
