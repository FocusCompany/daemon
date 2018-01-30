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

void FocusEventEmitter::EmitEnvelope(const std::string &dest, const Focus::Envelope &envelope) const {
    zmq::multipart_t msg;
    msg.addstr(dest);
    std::string temp = envelope.SerializeAsString();
    msg.addstr(temp);
    msg.send(*_socketPUB);
}

void FocusEventEmitter::EmitMessage(const std::string &dest, const std::string &message) const {
    zmq::multipart_t msg;
    msg.addstr(dest);
    msg.addstr(message);
    msg.send(*_socketPUB);
}