//
// Created by Etienne Pasteur on 17/10/2017.
//

#include <FocusEventListener.hpp>
#include <nanomsg/nn.h>
#include <nanomsg/pubsub.h>

FocusEventListener::FocusEventListener() {
	_socketSUB = nn_socket(AF_SP, NN_SUB);
	nn_connect(_socketSUB, "ipc:///tmp/EventEmitter");
}

void FocusEventListener::RunReceive(int socketSUB, std::function<void(std::string clientId, std::string payload)>* onMessage, bool shouldUnpack) {
	while (true) {
		char *buf = NULL;
		int bytes = nn_recv(socketSUB, &buf, NN_MSG, 0);
		std::string recv = std::string(buf);
		nn_freemsg(buf);
		std::string clientId = recv.substr(0, recv.find_first_of("|"));
		std::string payload = recv.substr(recv.find_first_of("|") + 1);
		(*onMessage)(clientId,payload);
	}
}

void FocusEventListener::Register(std::string payloadType, std::function<void(std::string clientId, std::string payload)> onMessage) {
	nn_setsockopt(_socketSUB, NN_SUB, NN_SUB_SUBSCRIBE, payloadType.c_str(), payloadType.size());
	_onMessage = onMessage;
	_eventListenerThread = std::make_unique<std::thread>(RunReceive, _socketSUB, &_onMessage, true);
}

void FocusEventListener::RegisterNoUnpack(std::string payloadType, std::function<void(std::string clientId, std::string payload)> onMessage) {
	nn_setsockopt(_socketSUB, NN_SUB, NN_SUB_SUBSCRIBE, payloadType.c_str(), payloadType.size());
	_onMessage = onMessage;
	_eventListenerThread = std::make_unique<std::thread>(RunReceive, _socketSUB, &_onMessage, false);
}

