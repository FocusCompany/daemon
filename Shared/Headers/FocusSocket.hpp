//
// Created by Etienne Pasteur on 22/01/2018.
//

#ifndef DAEMON_FOCUSSOCKET_HPP
#define DAEMON_FOCUSSOCKET_HPP

#include <memory>
#include <zmq_addon.hpp>

class FocusSocket {
protected:
    std::unique_ptr<zmq::socket_t> _socket;

public:
    static zmq::context_t *Context;

    FocusSocket();

    bool Send(const std::string &deviceId, const std::string &payload) const;

    std::string Receive() const;

    void Connect(const std::string &address) const;

    void Disconnect() const;
};


#endif //DAEMON_FOCUSSOCKET_HPP
