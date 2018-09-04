//
// Created by Etienne Pasteur on 17/10/2017.
//

#include <FocusEventManager.hpp>
#include <iostream>

FocusEventManager::FocusEventManager() : _socketPUB(std::make_unique<zmq::socket_t>(*FocusSocket::Context, ZMQ_PUB)),
                                         _socketSUB(std::make_unique<zmq::socket_t>(*FocusSocket::Context, ZMQ_SUB)),
                                         _isRunning(false),
                                         _sigReceived(false),
                                         _eventManagerThread() {
    int _socketTimeout = 1000; //milliseconds
    _socketSUB->setsockopt(ZMQ_RCVTIMEO, &_socketTimeout, sizeof(_socketTimeout));
}

void FocusEventManager::Run(std::atomic<bool> &sigReceived) {
    _socketPUB->bind("inproc:///tmp/EventEmitter");
    _socketSUB->bind("inproc:///tmp/EventListener");
    _socketSUB->setsockopt(ZMQ_SUBSCRIBE, "", 0);
    _sigReceived = sigReceived.load();
    _isRunning = true;
    _eventManagerThread = std::make_unique<std::thread>(std::bind(&FocusEventManager::RunReceive, this));
}

void FocusEventManager::RunReceive() const {
    while (_isRunning && !_sigReceived) {
        zmq::multipart_t rep;
        if (rep.recv(*_socketSUB)) {
            rep.send(*_socketPUB);
        }
    }
}

FocusEventManager::~FocusEventManager() {
    if (_isRunning) {
        _isRunning = false;
        _eventManagerThread->detach();
    }
    _socketSUB->close();
    _socketPUB->close();
}
