#include "FocusEventEmitter.hpp"
#include <nanomsg/nn.h>
#include <nanomsg/pubsub.h>

FocusEventEmitter::FocusEventEmitter() {
	_socketPUB = nn_socket(AF_SP, NN_PUB);
	nn_connect(_socketPUB, "ipc:///tmp/EventListener");
}

void FocusEventEmitter::Emit(std::string destinator, std::string& payload) {
	std::string toSend = destinator + "|" + payload;
	nn_send(_socketPUB, toSend.c_str(), toSend.size() + 1, 0);
}

void FocusEventEmitter::RouteToModules(std::string& payload){
	//nn_send(_socketPUB, payload.c_str(), strlen(payload.c_str()) + 1, 0);
}
