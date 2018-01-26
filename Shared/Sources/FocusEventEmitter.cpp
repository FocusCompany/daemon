//
// Created by Etienne Pasteur on 17/10/2017.
//

#include "FocusEventEmitter.hpp"

FocusEventEmitter::FocusEventEmitter() {
    _socketPUB->connect("inproc:///tmp/EventListener");
}

void FocusEventEmitter::Emit(const std::string &dest, const Focus::Event &payload) const{
    zmq::multipart_t msg;
    msg.addstr(dest);
    std::string temp = payload.SerializeAsString();
    msg.addstr(temp);
    msg.send(*_socketPUB);
}

void FocusEventEmitter::RouteToModules(const Focus::Event &payload) const{
    Emit(payload.payloadtype(), payload);
}
