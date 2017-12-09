#include "FocusEventEmitter.hpp"
#include <nanomsg/nn.h>
#include <nanomsg/pubsub.h>

FocusEventEmitter::FocusEventEmitter() {
    _socketPUB = nn_socket(AF_SP, NN_PUB);
    nn_connect(_socketPUB, "ipc:///tmp/EventListener");
}

void FocusEventEmitter::Emit(const std::string &dest, const Focus::Event &payload) const{
    std::string toSend = dest + "|" + payload.SerializeAsString();
    nn_send(_socketPUB, toSend.c_str(), toSend.size() + 1, 0);
}

void FocusEventEmitter::RouteToModules(const Focus::Event &payload) const{
    Emit(payload.payloadtype(), payload);
}
