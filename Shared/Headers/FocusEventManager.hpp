//
// Created by Etienne Pasteur on 17/10/2017.
//

#ifndef FOCUS_CLIENT_FOCUSEVENTMANAGER_HPP
#define FOCUS_CLIENT_FOCUSEVENTMANAGER_HPP

#include <thread>
#include <FocusSocket.hpp>

class FocusEventManager {
private:
    std::unique_ptr<zmq::socket_t> _socketPUB;
    std::unique_ptr<zmq::socket_t> _socketSUB;
    std::atomic<bool> _isRunning;
    std::unique_ptr<std::thread> _eventManagerThread;

    void RunReceive() const;

public:
    FocusEventManager();

    virtual ~FocusEventManager();

    void Run();
};

#endif //FOCUS_CLIENT_FOCUSEVENTMANAGER_HPP
