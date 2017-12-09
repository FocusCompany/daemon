#include "FocusEventEmitter.hpp"
#include <nanomsg/nn.h>
#include <nanomsg/pubsub.h>

FocusEventEmitter::FocusEventEmitter() {
    _socketPUB = nn_socket(AF_SP, NN_PUB);
    nn_connect(_socketPUB, "ipc:///tmp/EventListener");
}

void FocusEventEmitter::Emit(std::string dest, Focus::Event &payload) {
    std::string toSend = dest + "|" + payload.SerializeAsString();
    nn_send(_socketPUB, toSend.c_str(), toSend.size() + 1, 0);
}

void FocusEventEmitter::RouteToModules(Focus::Event &payload) {
    Emit(payload.payloadtype(), payload);
}
