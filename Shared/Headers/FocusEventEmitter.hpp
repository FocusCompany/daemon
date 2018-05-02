//
// Created by Etienne Pasteur on 17/10/2017.
//

#ifndef FOCUS_CLIENT_FOCUSEVENTEMITTER_HPP
#define FOCUS_CLIENT_FOCUSEVENTEMITTER_HPP

#include <string>
#include <FocusEvent.pb.h>
#include <FocusSocket.hpp>
#include <FocusEnvelope.pb.h>

class FocusEventEmitter {
private:
    std::unique_ptr<zmq::socket_t> _socketPUB = std::make_unique<zmq::socket_t>(*FocusSocket::Context, ZMQ_PUB);

public:
    FocusEventEmitter();

    virtual ~FocusEventEmitter();

    void Emit(const std::string &dest, const Focus::Event &payload) const;

    void EmitEnvelope(const std::string &dest, const Focus::Envelope &envelope) const;

    void EmitMessage(const std::string &dest, const std::string &message) const;
};


#endif //FOCUS_CLIENT_FOCUSEVENTEMITTER_HPP