//
// Created by Etienne Pasteur on 17/10/2017.
//

#ifndef FOCUS_CLIENT_FOCUSEVENTEMITTER_HPP
#define FOCUS_CLIENT_FOCUSEVENTEMITTER_HPP

#include <string>
#include <FocusEvent.pb.h>
#include <FocusSocket.hpp>

class FocusEventEmitter {
private:
    std::shared_ptr<zmq::socket_t> _socketPUB = std::make_shared<zmq::socket_t>(*FocusSocket::Context, ZMQ_PUB);

public:
    FocusEventEmitter();

    void Emit(const std::string &dest, const Focus::Event &payload) const;

    void RouteToModules(const Focus::Event &payload) const;
};


#endif //FOCUS_CLIENT_FOCUSEVENTEMITTER_HPP